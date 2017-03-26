#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#define x first
#define y second
#define ll long long
#define mp make_pair
using namespace std;

vector <pair<int,int> > hull;
vector <pair<int,int> >points;

pair <int,int> operator-(pair < int,int > a,pair <int,int> b)
{
    return mp((a.x-b.x),(a.y-b.y));
}
pair <int,int> operator+(pair < int,int > a,pair <int,int> b)
{
    return mp((a.x+b.x),(a.y+b.y));
}

bool check(pair<int,int> a , pair<int,int> b)///checking if on right or closer
{
    ll il;
    il=(ll)a.x*(ll)b.y-(ll)b.x*(ll)a.y;
    if(il<0)
        return true;
    if(il==0)
    {
        ll g,h;
        g=(ll)a.x*(ll)a.x+(ll)a.y*(ll)a.y;
        h=(ll)b.x*(ll)b.x+(ll)b.y*(ll)b.y;
        if(g<h)
            return true;

    }
    return false;
}
bool check2(pair<int,int> a , pair<int,int> b)///checking if on right
{
    ll il;
    il=(ll)a.x*(ll)b.y-(ll)b.x*(ll)a.y;
    if(il<=0)
    {
            return true;
    }
    return false;
}
bool check3(pair<int,int> a , pair<int,int> b)///checking if not on left
{
    ll il;
    il=(ll)a.x*(ll)b.y-(ll)b.x*(ll)a.y;
    if(il<0)
    {
            return true;
    }
    return false;
}
bool isin(pair<int,int> a,pair <int,int> first)
{
    if(a==first)
        return true;
    pair<int,int> g,h;
    if(a.y<first.y)
    {
        return false;
    }
    g=a-first;
    h=hull[hull.size()-2]-first;
    if(!check2(g,h))
    {
        return false;
    }
    h=hull[1]-first;
    if(check2(g,h))
    {
        if(!check3(g,h))
        {
            if((g.x==h.x&&g.y==h.y)||check(g,h))
            return true;
        }
        return false;
    }

    ///binary search
    int p=0,q=hull.size()-2;
    while(p!=q-1)
    {
        int d=(q+p)/2;
        h=hull[d]-first;
        if(check2(g,h))
        {
            q=d;
        }
        else
        {
            p=d;
        }
    }
    ///checking if inside
    g=a-hull[p];
    h=hull[q]-hull[p];
    if(g==h)
        return true;
    if(check3(g,h))
    {
        return false;
    }
    else
        return true;


}
int main()
{
    ///Input
    int N;
    scanf("%d ",&N);
    points.resize(N);
    int a,b;
    for(int i=0;i<N;i++)
    {

        scanf("%d %d",&a,&b);
        points[i]=mp(a,b);
    }
    ///finding first
    int mini=0;
    for(int i=1;i<N;i++)
    {
        if(points[mini].y>points[i].y || (points[mini].y==points[i].y && points[mini].x>points[i].x))
            mini=i;
    }

    pair<int,int> first=points[mini];
    points[mini]=points[points.size()-1];
    points.pop_back();
    ///angle sort
    for(int i=0;i<points.size();i++)
    {
        points[i]=points[i]-first;
    }
    sort(points.begin(),points.end(), check);

    for(int i=0;i<points.size();i++)
    {
        points[i]=points[i]+first;
    }
    points.push_back(first);
    ///Graham
    hull.push_back(first);
    hull.push_back(points[0]);
    for(int i=1;i<points.size();i++)
    {
        pair <int,int> g=points[i]-hull[hull.size()-2];
        pair <int,int> h=hull[hull.size()-1]-hull[hull.size()-2];
        int k=1;
        if(i==points.size()-1)
            k=2;
        while(hull.size()>k&&check2(g,h))
        {
            hull.pop_back();
            g=points[i]-hull[hull.size()-2];
            h=hull[hull.size()-1]-hull[hull.size()-2];
        }
        hull.push_back(points[i]);
    }
    ///OUTPUT
    printf("\n");
    for(int i=0;i<hull.size();i++)
        printf("%d %d\n",hull[i].x,hull[i].y);
    ///Is Inside?
    scanf("%d %d",&a,&b);
    if(isin(mp(a,b),first))
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;

}
