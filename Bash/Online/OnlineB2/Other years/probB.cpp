#include <stdio.h>
#include <math.h>
int main(void)
{
    long long int m,R;
    while(scanf("%I64d %I64d",&m,&R)!=EOF)
    {
        double sum=0.0;
        int n;
        for(n=0;n<m;n++)
        {
          sum+=(2*R+R*n*sqrt(2));
        }
        double avg;
        avg=sum/m;
        printf("%llf\n",avg);
    }
    return 0;
}
