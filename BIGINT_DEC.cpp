#include <cstdio>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <utility>
using namespace std;

class BIGINT
{
    public:
    vector <char> val;
    bool sgn;
    BIGINT()
    {
        val.clear();
        val.push_back(0);
        sgn=false;
    }

    void in()///just scanf bigint    !!!scans one aditional char (' ', '\n' etc.) !!!
    {
        val.clear();
        sgn=false;
        char a;
        scanf("%c",&a);
        if(a=='-')
        {
            sgn=true;
            scanf("%c",&a);
        }
        if(a>=48&&a<58)
        {
            while(a>=48&&a<58)
            {
                val.push_back(a-48);
                scanf("%c",&a);
            }

            for(int i=0;i<val.size()/2;i++)
            {
                a=val[val.size()-i-1];
                val[val.size()-i-1]=val[i];
                val[i]=a;
            }
        }
        else
        {
            printf("input error: try again ");
            in();
        }
    }

    void out() const///just printf bigint
    {
        if(sgn)
            printf("-");
        for(int i=val.size()-1;i>=0;i--)
        {
            printf("%c",(char)(val[i]+48));
        }
    }

    bool parity() const///true if bigint is even
    {
        if(val[0]%2)
            return false;
        else
            return true;
    }

    void convert(const long long l,int k)///convert from long long n * 10^k to bigint
    {
        long long n=l;
        if(n==0)
        {
            val.clear();
            val.push_back(0);
            sgn=false;
            return;
        }
        else
        {
            if(n<0)
            {
                n*=(-1);
                sgn=true;
            }
            else
                sgn=false;
            val.clear();

            val.resize(k);
            for(int i=0;i<val.size();i++)
                val[i]=0;
            while(n)
            {
                val.push_back(n%10);
                n/=10;
            }

        }
    }

    BIGINT abs() const
    {
        BIGINT ret=*this;
        ret.sgn=0;
        return ret;
    }

    ///booleans

        bool operator> (const BIGINT b) const
        {
            if(this->sgn==1&&b.sgn==0)
                return false;
            else if (this->sgn==0&&b.sgn==1)
                return true;
            else
            {
                bool ret=0;
                bool juz=0;
                if(this->val.size()>b.val.size())
                {
                    ret=1;
                    juz=1;
                }
                else if(this->val.size()<b.val.size())
                {
                    ret=0;
                    juz=1;
                }
                else
                {
                    for(int i=this->val.size()-1;!juz&&i>=0;i--)
                    {
                        if(this->val[i]>b.val[i])
                        {
                            juz=1;
                            ret=1;
                        }
                        else if(this->val[i]<b.val[i])
                        {
                            juz=1;
                            ret=0;
                        }
                    }
                    if(juz==0)
                        return false;

                }
                return (ret!=this->sgn);
            }
        }

        bool operator>= (const BIGINT b) const
        {
            if(this->sgn==1&&b.sgn==0)
                return false;
            else if (this->sgn==0&&b.sgn==1)
                return true;
            else
            {
                bool ret=0;
                bool juz=0;
                if(this->val.size()>b.val.size())
                {
                    ret=1;
                    juz=1;
                }
                else if(this->val.size()<b.val.size())
                {
                    ret=0;
                    juz=1;
                }
                else
                {
                    for(int i=this->val.size()-1;!juz&&i>=0;i--)
                    {
                        if(this->val[i]>b.val[i])
                        {
                            juz=1;
                            ret=1;
                        }
                        else if(this->val[i]<b.val[i])
                        {
                            juz=1;
                            ret=0;
                        }
                    }
                    if(juz==0)
                        return true;

                }
                return (ret!=this->sgn);
            }
        }

        bool operator== (const BIGINT b) const
        {
            if(this->sgn!=b.sgn)
                return false;
            else
            {
                if(this->val.size()!=b.val.size())
                    return false;
                else
                {
                    for(int i=0;i<this->val.size();i++)
                        if (this->val[i]!=b.val[i])
                            return false;
                }
            }
            return true;
        }

        bool operator< (const BIGINT b) const
        {
            return !(*this>=b);
        }
        bool operator<= (const BIGINT b) const
        {
            return !(*this>b);
        }
        bool operator!= (const BIGINT b) const
        {
            return !(*this==b);
        }


    ///arithmetic functions

        BIGINT operator<<(int n) const/// multiplying bigint * 10^n !!!!!not binary!!!!!
        {
            BIGINT ret;
            ret.sgn=this->sgn;
            ret.val.resize(this->val.size()+n);
            for(int i=0;i<n;i++)
                ret.val[i]=0;
            for(int i=0;i<this->val.size();i++)
                ret.val[i+n]=this->val[i];
            return ret;
        }

        BIGINT add_abs(const BIGINT b) const///add bigints w-out sign
        {
            BIGINT ret;
            ret.val.pop_back();
            ret.sgn=false;
            int siz=max(this->val.size(),b.val.size());
            bool poprz=0;
            for(int i=0;i<siz;i++)
            {
                if(i<this->val.size()&&i<b.val.size())
                {
                    char sum=poprz+this->val[i]+b.val[i];
                    if(sum>=10)
                    {
                        poprz=1;
                        ret.val.push_back(sum-10);
                    }
                    else
                    {
                        poprz=0;
                        ret.val.push_back(sum);
                    }

                }
                else if(i<this->val.size())
                {
                    char sum=poprz+this->val[i];
                    if(sum>=10)
                    {
                        poprz=1;
                        ret.val.push_back(sum-10);
                    }
                    else
                    {
                        poprz=0;
                        ret.val.push_back(sum);
                    }
                }
                else
                {
                    char sum=poprz+b.val[i];
                    if(sum>=10)
                    {
                        poprz=1;
                        ret.val.push_back((sum-10));
                    }
                    else
                    {
                        poprz=0;
                        ret.val.push_back((sum));
                    }
                }

            }
            if(poprz)
                ret.val.push_back(1);
            return ret;
        }

        BIGINT sub_abs(const BIGINT b) const///subtract bigints w-out input sign
        {
            BIGINT mini;
            BIGINT ret;
            mini.val.clear();
            int siz=max(this->val.size(),b.val.size());
            if(this->sgn==b.sgn)
            {
                if(this->sgn)
                {
                    if( *this <= b)
                    {
                        ret=*this;
                        mini=b;
                        ret.sgn=false;
                    }
                    else
                    {
                        ret=b;
                        mini=*this;
                        ret.sgn=true;
                    }

                }
                else
                {
                    if( *this >= b)
                    {
                        ret=*this;
                        mini=b;
                        ret.sgn=false;
                    }
                    else
                    {
                        ret=b;
                        mini=*this;
                        ret.sgn=true;
                    }


                }
            }
            else
            {
                if( this->abs() >= b.abs())
                {
                    ret=*this;
                    mini=b;
                    ret.sgn=false;
                }
                else
                {
                    ret=b;
                    mini=*this;
                    ret.sgn=true;
                }
            }

            bool poprz=0;
            int sizr=ret.val.size(),sizm=mini.val.size();
            for(int i=0;i<sizm||poprz;i++)
            {

                char sum=ret.val[i]-poprz;
                if(i<sizm)
                    sum-=mini.val[i];
                if(sum<0)
                {
                    poprz=1;
                    sum+=10;
                }
                else
                    poprz=0;
                ret.val[i]=sum;
            }
            while(ret.val[ret.val.size()-1]==0&&ret.val.size()>1)
                ret.val.pop_back();
            return ret;

        }

        BIGINT operator+ (const BIGINT b) const
        {
            if(this->sgn==b.sgn)
            {
                BIGINT ret=this->add_abs(b);

                if(this->sgn)
                    ret.sgn=!ret.sgn;

                return ret;
            }
            else
            {
                BIGINT ret=this->sub_abs(b);
                if(this->sgn)
                    ret.sgn=!ret.sgn;
                return ret;
            }
        }

        BIGINT operator- (const BIGINT b) const
        {
            if(this->sgn==b.sgn)
            {
                BIGINT ret=this->sub_abs(b);
                if(this->sgn)
                    ret.sgn=!ret.sgn;
                return ret;
            }
            else
            {
                BIGINT ret=this->add_abs(b);
                if(this->sgn)
                    ret.sgn=!ret.sgn;
                return ret;
            }
        }

        BIGINT operator* (const BIGINT b) const
        {
            BIGINT ret;
            if(b.val.size()==1)
            {
                if(b.val[0]==0)
                    return ret;
                if(b.val[0]==1)
                {
                    if(b.sgn)
                    {
                        ret=*this;
                        ret.sgn=!ret.sgn;
                        return ret;
                    }
                    return *this;
                }

            }
            if(this->val.size()==1)
            {
                if(this->val[0]==0)
                    return ret;
                if(this->val[0]==1)
                {
                    if(this->sgn)
                    {
                        ret=b;
                        ret.sgn=!ret.sgn;
                        return ret;
                    }
                    return b;
                }

            }
            ret.sgn=0;
            ret.val.resize(this->val.size());
            for(int i=0;i<this->val.size();i++)
            {
                if(this->val[i]>0)
                {
                    if(this->val[i]==1)
                    {
                        ret=ret.add_abs(b<<i);
                    }
                    else
                    {
                        char mult=this->val[i];
                        char p1=0;
                        bool p2=0;
                        for(int j=0;j<b.val.size()||p1||p2;j++)
                        {
                            if(j+i==ret.val.size())
                                ret.val.push_back(0);
                            if(j<b.val.size())//still multiplying
                            {
                                char sum=b.val[j]*mult;
                                sum+=p1;
                                p1=sum/10;
                                sum%=10;
                                char s=sum+p2+ret.val[j+i];
                                if(s>=10)
                                {
                                    p2=1;
                                    s-=10;
                                }
                                else
                                    p2=0;
                                ret.val[j+i]=s;

                            }
                            else//only previous bigger than 10, not multiplying
                            {

                                char sum=ret.val[j+i]+p1+p2;
                                p1=0;
                                if(sum>=10)
                                {
                                    p2=1;
                                    sum-=10;
                                }
                                else
                                    p2=0;
                                ret.val[j+i]=sum;

                            }




                        }

                    }

                }


            }
            ret.sgn=(this->sgn!=b.sgn);
            return ret;

        }

        BIGINT operator/ (const BIGINT b) const
        {
            if(b.val.size()==1)
            {
                if(b.val[0]==0)
                {
                     printf("ERROR: DIVIDE BY ZERO\n");
                     BIGINT ret;
                     return ret;
                }
                if(b.val[0]==1)
                {
                    if(b.sgn)
                    {
                        BIGINT ret=*this;
                        ret.sgn=!ret.sgn;
                        return ret;

                    }
                    return *this;
                }

            }
            BIGINT div,mod;
            mod.val.clear();
            mod.sgn=b.sgn;
            BIGINT one;
            one.val.resize(this->val.size());
            one.val[one.val.size()-1]=1;
            one.sgn=mod.sgn;
            for(int j=this->val.size()-1;j>=0;j--)
            {
                if(!(mod.val.size()==1&&mod.val[0]==0))
                mod.val.push_back(0);
                for(int i=mod.val.size()-2;i>=0;i--)
                {
                    mod.val[i+1]=mod.val[i];
                }
                mod.val[0]=this->val[j];
                if(mod.sgn)
                {
                    while(mod<=b)
                    {
                        mod=mod-b;
                        div=div.add_abs(one);

                    }

                }
                else
                {
                    while(mod>=b)
                    {
                        mod=mod-b;
                        div=div.add_abs(one);
                    }

                }

                one.val.pop_back();
                if(one.val.size()>0)
                    one.val[one.val.size()-1]=1;
            }
            if(div.val.size()==1&&div.val[0]==0)
            {
                div.sgn=0;
            }
            else
            {
                div.sgn=(this->sgn!=b.sgn);
            }
            return div;
        }

        BIGINT operator% (const BIGINT b) const
        {

            if(b.val.size()==1)
            {
                if(b.val[0]==0)
                {
                     printf("ERROR: DIVIDE BY ZERO\n");
                     BIGINT ret;
                     return ret;
                }
                if(b.val[0]==1)
                {
                    BIGINT ret;
                    return ret;
                }

            }
            BIGINT div,mod;
            mod.val.clear();
            mod.sgn=b.sgn;
            BIGINT one;
            one.val.resize(this->val.size());
            one.val[one.val.size()-1]=1;
            one.sgn=mod.sgn;
            for(int j=this->val.size()-1;j>=0;j--)
            {
                if(!(mod.val.size()==1&&mod.val[0]==0))
                mod.val.push_back(0);
                for(int i=mod.val.size()-2;i>=0;i--)
                {
                    mod.val[i+1]=mod.val[i];
                }
                mod.val[0]=this->val[j];
                if(mod.sgn)
                {
                    while(mod<=b)
                    {
                        mod=mod-b;
                        div=div.add_abs(one);

                    }

                }
                else
                {
                    while(mod>=b)
                    {
                        mod=mod-b;
                        div=div.add_abs(one);
                    }

                }

                one.val.pop_back();
                if(one.val.size()>0)
                    one.val[one.val.size()-1]=1;
            }
            if(div.val.size()==1&&div.val[0]==0)
            {
                mod.sgn=this->sgn;
                if(mod.val.size()==1&&mod.val[0]==0)
                    mod.sgn=0;
            }
            else
            {
                mod.sgn=this->sgn;
                if((mod.val.size()==1)
                    && (mod.val[0]==0))
                    mod.sgn=0;
            }
            return mod;
        }

        BIGINT operator^(long long c) const ///bigint to c'th power !!!!! not binary XOR !!!!!
        {
            BIGINT ret;
            ret.val[0]=1;
            BIGINT b;
            b=*this;
            while(c)
            {
                if(c&1)
                {
                    ret=ret*b;
                }
                b=b*b;
                c=(c>>1);
            }
            return ret;

        }

};



int main()
{
    BIGINT a,b;
    a.in();b.in();
    a=a*b;
    a.out();
    return 0;
}
