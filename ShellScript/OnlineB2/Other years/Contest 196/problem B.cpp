#include <stdio.h>
int main(void)
{
    int a,b,c,d;
    while(scanf("%d %d %d %d",&a,&b,&c,&d)!=EOF)
    {
        /* EXPRESS a/b and c/d as minimum possible ratio*/
        int t;
        t= (a>b) ? b:a;
        int i,gcd=1;
        for(i=t;i>=1;i--)
        {
            if(a%i==0 && b%i==0)
            {
                gcd=i;
                break;
            }
        }
        a=a/gcd;
        b=b/gcd;
        t= (c>d) ? d:c;
        for(i=t;i>=1;i--)
        {
            if(c%i==0 && d%i==0)
            {
                gcd=i;
                break;
            }
        }
        c=c/gcd;
        d=d/gcd;

        //printf("a:b= %d : %d,c:d= %d : %d.....\n",a,b,c,d);
        /* Determine the minimum of a/c and b/d and fix a flag; */
        int flag=0;
        if((float)(a/c)>(float)(b/d)) flag=1;
        else flag=2;
        /* DETERMINE THE RESULT*/
        int r1,r2;
        if(flag==1)
        {
            r1=a*d-b*c;
            r2=d*a;
        }
        else if(flag==2)
        {
            r1=b*c-a*d;
            r2=c*b;
        }
        /*EXPRESS r1/r2 as minimum possible ratio.*/
        t= (r1>r2) ? r2:r1;
        for(i=t;i>=1;i--)
        {
            if(r1%i==0 && r2%i==0)
            {
                gcd=i;
                break;
            }
        }
        r1=r1/gcd;
        r2=r2/gcd;
        printf("%d/%d\n",r1,r2);
    }
    return 0;
}
