#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{
    long int n,m;
    while(scanf("%ld %ld",&n,&m)!=EOF)
    {
        long int sz=pow(2,n);
        long int *A=(long int*)malloc(sizeof(long int)*sz);
        long int **B=(long int**)malloc(sizeof(long int*)*m);
        long int i;
        for(i=0;i<sz;i++)
        {
            scanf("%ld",&A[i]);
        }
        for(i=0;i<m;i++)
        {
            *(B+i)=(long int*)malloc(sizeof(long int)*2);
            scanf("%ld %ld",&B[i][0],&B[i][1]);
        }
        long int loop;
        for(loop=0;loop<m;loop++)
        {
            long int *A1=(long int*)malloc(sizeof(long int)*sz);
            for(i=0;i<sz;i++)
            {
                if(i!=B[loop][0]-1) A1[i]=A[i];
                else A1[i]=B[loop][1];
            }
            for(i=0;i<sz;i++)
            {
                A[i]=A1[i];
            }
            long int temp=sz;
            while(temp>1)
            {
                long int o1,r=0;
                for(o1=0;o1<temp-1;o1+=2)
                {
                   A1[r]=A1[o1]|A1[o1+1];
                   r++;
                }
                temp=temp/2;
                r=0;
                for(o1=0;o1<temp-1;o1+=2)
                {
                   A1[r++]=A1[o1]^A1[o1+1];
                }
                temp=temp/2;
            }
            printf("%ld\n",A1[0]);
            free(A1);
        }
    }
    return 0;
}
