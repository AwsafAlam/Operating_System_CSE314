#include <stdio.h>
int main(void)
{
    long long int x,y,a,b;
    while(scanf("%I64d %I64d %I64d %I64d",&x,&y,&a,&b)!=EOF)
    {
        long long int lcm,small,maxm,i,result=0;
        maxm=(x>y) ? x : y;
         while(1)
         {
              if(maxm%x==0 && maxm%y==0)
                {
                lcm=maxm;
                break;
              }
              ++maxm;
         }
        if(a%lcm==0)
        {
            result=b/lcm-a/lcm+1;
        }
        else
        {
            result=b/lcm-a/lcm;
        }
    }
    return 0;
}
