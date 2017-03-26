#include <cstdio>
#include <vector>

using namespace std;
int numb_of(int a1,int b1,int a2,int b2);
struct verticle
{
    long long sum;
    long long modif;
    int L,P;
};

struct Interval_tree
{
    vector <verticle> tree;
    Interval_tree(int N=0)///constructor
    {
        if(N>0)
        {
            int s=0,N2=N;
            while(N2)
            {
                N2=(N2>>1);
                s++;
            }

            if((1<<(s-1))==N)
                s--;
            s=(1<<(s+1));
            tree.resize(s);

            for(int i=s/2;i<s;i++)
            {
                tree[i].L=tree[i].P=i-s/2;
            }
            for(int i=s/2-1;i>0;i--)
            {
                tree[i].L=tree[2*i].L;
                tree[i].P=tree[2*i+1].P;
            }
        }
    }
    long long SUM (int a,int b,int v=1)///recursively counting sum
    {

        int nr=numb_of(a,b,tree[v].L,tree[v].P);
        if(nr==0)
        {
            return 0;
        }
        if(tree[v].modif!=0)
        {
            tree[v].sum+=tree[v].modif*(long long)(tree[v].P-tree[v].L+1);
            if(v<tree.size()/2)
            {
                tree[v*2].modif+=tree[v].modif;
                tree[v*2+1].modif+=tree[v].modif;
            }
            tree[v].modif=0;
        }
        if(nr==tree[v].P-tree[v].L+1)
        {
            return tree[v].sum;
        }
        return SUM(a,b,v*2)+SUM(a,b,v*2+1);
    }
    void ADD(int a,int b,int c,int v=1)///recursively adding
    {
        int nr=numb_of(a,b,tree[v].L,tree[v].P);
        if(nr==0)
        {
            return;
        }
        if(nr==tree[v].P-tree[v].L+1)
        {
            tree[v].modif+=(long long)c;
            return;
        }
        tree[v].sum+=(long long)c*nr;
        ADD(a,b,c,(v*2));
        ADD(a,b,c,(v*2)+1);
        return;

    }
};
int numb_of(int a1,int b1,int a2,int b2)///number of common points
{
    if(b1<a2||a1>b2)
        return 0;
    if(a1<=a2&&b1>=b2)
        return b2-a2+1;
    if(a1>a2)
    {
        if(b1<b2)
            return b1-a1+1;
        return b2-a1+1;
    }
    if(b1<b2)
        return b1-a2+1;
}

int main()
{
    ///initialize
    int N,M;
    scanf("%d %d",&N,&M);
    Interval_tree pp(N);

    ///operations
    for(int m=0;m<M;m++)
    {
        int a,b;
        int c;
        scanf("%d ",&a);
        if(a)
        {
            ///SUM
            scanf("%d %d",&a,&b);
            printf("%lld\n",pp.SUM(a,b));
        }
        else
        {
            ///ADD
            scanf("%d %d %d",&a,&b,&c);
            pp.ADD(a,b,c);

        }
    }
    return 0;
}
