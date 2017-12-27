#include <bits/stdc++.h>
#define ll long long
#define ft first
#define sd second
#define mp make_pair
#define SZ(a) (int)a.size()
using namespace std;
struct Centroids
{
    vector < vector< int > > ct;//sons in centroid tree
    vector < int > ch;//level of centroid
    vector < int > pr;//parent in centroid tree
    unsigned int N;//size
    private: 
    vector <bool> vis;//lately visited
    vector <int> st;//subtree size
    public:Centroids(vector <vector <int> > &Tree) // constructor
    {
        //initialize
        N=Tree.size();
        ct.resize(N);    
        ch.resize(N);
        pr.resize(N);
        vis.resize(N);
        st.resize(N);
        for(int i=0;i<(int)N;i++)
        {
            ch[i]=-1;
            st[i]=0;
            vis[i]=0;
        }
        
        //fill everything
        MakeCentroid(0,-1,Tree);
        
        //get rid of trash
        vis.clear();
        st.clear();
    }
    
    private: 
    int dfs1(int v, vector <int> & trash, vector <vector <int> > &Tree)//count subtrees size
    {
        trash.push_back(v);
        st[v]=1;//subtree size = 1
        vis[v]=1;
        for(int i=0;i<SZ(Tree[v]);i++)
        {
            if(ch[Tree[v][i]]==-1&&!vis[Tree[v][i]])//node is child if not already a centroid and not yet visited
            {
                st[v]+=dfs1(Tree[v][i],trash,Tree);//subtree size += sizes of subtrees of chilren
            }
        }
        return st[v];
    }
    int findcntr(int v,int n,vector <vector <int> >  &Tree)//finds centroid by going dfs-like to son with max st - if max st < N/2 then v is centroid
    {
        int l=-1,m=0;//maximum of st of children
        for(int i=0;i<SZ(Tree[v]);i++)
        {
            if(ch[Tree[v][i]]==-1&&st[Tree[v][i]]<st[v])//node is child if not already a centroid and (not a parent <=> lower st)
            {
                if(st[Tree[v][i]]>m)
                {
                    l=Tree[v][i];
                    m=st[l];
                }
            }
        }
        if(m*2>=n)// we search deeper
        {
            return findcntr(l,n,Tree);
        }
        return v;
    }
    void MakeCentroid(int v,int par,vector <vector <int> > &Tree,int h=0)//finds centroid, updates centroid tree and divides the tree - then recursion
    {
        vector <int> trash;//vector for clearing viarables
        
        int n=dfs1(v, trash,Tree);// count subtrees sizes
        
        int nc=findcntr(v,n,Tree);// find centroid
        
        ch[nc]=h;//fill ch of new centroid
        //clear viarables
        for(int i=0;i<SZ(trash);i++)
        {
            st[trash[i]]=0;
            vis[trash[i]]=false;
        }
        trash.clear();
        
        //update centroid tree
        pr[nc]=par;
        ct[pr[nc]].push_back(nc);//push nc as son to parent
        
        //make recursion
        for(int i=0;i<SZ(Tree[nc]);i++)
        {
            if(ch[Tree[nc][i]]==-1)
            {
                MakeCentroid(Tree[nc][i],nc,Tree,h+1);//make next level centroids
            }
        }
        
    }
};
int main()
{
    int n;
    vector <vector< int> >Tree;
    scanf("%d",&n);
    Tree.resize(n);
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        Tree[a-1].push_back(b-1);
        Tree[b-1].push_back(a-1);
    }
    Centroids Cn(Tree);
    return 0;
}
