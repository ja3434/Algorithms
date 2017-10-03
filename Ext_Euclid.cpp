#include <bits/stdc++.h>

bool EEuk(int a,int b,int &x,int &y)// =( GCD(a,b)==1 )
{
	
	int c=a%b;
	if(c==0)//if NWD(a,b) > 1
		return 0;
	if(c==1)
	{
		x=1;
		y=-a/b;
		return 1;
	}
	else
	{
		bool gh=EEuk(b,c,x,y);
		if(gh)
		{
			c=y;
			y=-a/b*y+x;
			x=c;
			return 1;
		}
		else
		{
			return 0;
		}
	}	
	
}
int main()
{
	int a,b;
	scanf("%d %d", &a, &b);
	int x=1,y=0;
	bool gh=EEuk(a,b,x,y);
	if(gh)
	{
		long long h=(a+y)%a;//y<0
		printf("(%d * %d) mod %d = 1",b,h,a);//(b*h) mod a = 1
	}
	else 
		printf("GCD(%d,%d)!=1",a,b);
	return 0;
}
