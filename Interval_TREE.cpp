#include <cstdio>
#include <vector>
#define inf 9223372036854775807

using namespace std;
inline int numb_of(int a1,int b1,int a2,int b2);

struct verticle
{
    long long maxim;
    long long minim;
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
        if(tree[v].modif!=0)//pushing modifier
        {
            tree[v].sum+=tree[v].modif*(long long)(tree[v].P-tree[v].L+1);
            tree[v].maxim+=tree[v].modif;
            tree[v].minim+=tree[v].modif;
            if(v<tree.size()/2)
            {
                tree[v*2].modif+=tree[v].modif;
                tree[v*2+1].modif+=tree[v].modif;
            }
            tree[v].modif=0;
        }
        if(nr==0)
        {
            return 0;
        }
        if(nr==tree[v].P-tree[v].L+1)
        {
            return tree[v].sum;
        }
        long long sumary= SUM(a,b,v*2)+SUM(a,b,v*2+1);
        tree[v].maxim=max(tree[v*2+1].maxim,tree[v*2].maxim);
        tree[v].minim=min(tree[v*2+1].minim,tree[v*2].minim);
        return sumary;
    }

    long long MAX(int a,int b,int v=1)///recursively counting maximum
    {
        int nr=numb_of(a,b,tree[v].L,tree[v].P);

        if(tree[v].modif!=0)//pushing modifier
        {
            tree[v].sum+=tree[v].modif*(long long)(tree[v].P-tree[v].L+1);
            tree[v].maxim+=tree[v].modif;
            tree[v].minim+=tree[v].modif;
            if(v<tree.size()/2)
            {
                tree[v*2].modif+=tree[v].modif;
                tree[v*2+1].modif+=tree[v].modif;
            }
            tree[v].modif=0;
        }
        if(nr==0)
        {
            return -inf-1;
        }
        if(nr==tree[v].P-tree[v].L+1)
        {
            return tree[v].maxim;
        }
        long long sumary= max(MAX(a,b,v*2),MAX(a,b,v*2+1));
        tree[v].maxim=max(tree[v*2+1].maxim,tree[v*2].maxim);
        tree[v].minim=min(tree[v*2+1].minim,tree[v*2].minim);
        return sumary;

    }

    long long MIN(int a,int b,int v=1)///recursively counting minimum
    {
        int nr=numb_of(a,b,tree[v].L,tree[v].P);

        if(tree[v].modif!=0)//pushing modifier
        {
            tree[v].sum+=tree[v].modif*(long long)(tree[v].P-tree[v].L+1);
            tree[v].maxim+=tree[v].modif;
            tree[v].minim+=tree[v].modif;
            if(v<tree.size()/2)
            {
                tree[v*2].modif+=tree[v].modif;
                tree[v*2+1].modif+=tree[v].modif;
            }
            tree[v].modif=0;
        }
        if(nr==0)
        {
            return inf;
        }
        if(nr==tree[v].P-tree[v].L+1)
        {
            return tree[v].minim;
        }
        long long sumary= min(MIN(a,b,v*2),MIN(a,b,v*2+1));
        tree[v].maxim=max(tree[v*2+1].maxim,tree[v*2].maxim);
        tree[v].minim=min(tree[v*2+1].minim,tree[v*2].minim);
        return sumary;

    }

    void ADD(int a,int b,int c,int v=1)///recursively adding
    {
        if(tree[v].modif!=0)//pushing modifier
        {
            tree[v].sum+=tree[v].modif*(long long)(tree[v].P-tree[v].L+1);
            tree[v].maxim+=tree[v].modif;
            tree[v].minim+=tree[v].modif;
            if(v<tree.size()/2)
            {
                tree[v*2].modif+=tree[v].modif;
                tree[v*2+1].modif+=tree[v].modif;
            }
            tree[v].modif=0;
        }
        int nr=numb_of(a,b,tree[v].L,tree[v].P);
        if(nr==0)
        {
            return;

        }
        if(nr==tree[v].P-tree[v].L+1)
        {
            tree[v].sum+=(long long)c*nr;
            tree[v].maxim+=(long long)c;
            tree[v].minim+=(long long)c;
            if(v<tree.size()/2)
            {
                tree[v*2+1].modif+=(long long)c;
                tree[v*2].modif+=(long long)c;
            }

            return;
        }
        tree[v].sum+=(long long)c*nr;
        ADD(a,b,c,(v*2));
        ADD(a,b,c,(v*2)+1);
        tree[v].maxim=max(tree[v*2+1].maxim,tree[v*2].maxim);
        tree[v].minim=min(tree[v*2+1].minim,tree[v*2].minim);
        return;
    }

};
inline int numb_of(int a1,int b1,int a2,int b2)///number of common points
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
        int a,b,c;
        scanf("%d ",&a);
        if(a==3)
        {
            ///MIN
            scanf("%d %d",&a,&b);
            printf("%lld\n",pp.MIN(a,b));

        }
        else if(a==2)
        {
            ///MAX
            scanf("%d %d",&a,&b);
            printf("%lld\n",pp.MAX(a,b));
        }
        else if(a==1)
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
