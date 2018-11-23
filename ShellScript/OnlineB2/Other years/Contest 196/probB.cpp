#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    long long int n,m;
    long long int *A;
    while(scanf("%I64d %I64d",&n,&m)!=EOF)
    {
        A=(long long int*) malloc(sizeof(long long int)*m);
        long long int i;
        for(i=0;i<m;i++)
        {
            scanf("%I64d",&A[i]);
        }
        long long int sum=A[0]-1;
        for(i=1;i<m;i++)
        {
            long long int ind;
            if(A[i]>=A[i-1]) ind=A[i]-A[i-1];
            else ind=n-(A[i-1]-A[i]);
            sum+=ind;
        }
        printf("%I64d\n",sum);
    }
    return 0;
}
