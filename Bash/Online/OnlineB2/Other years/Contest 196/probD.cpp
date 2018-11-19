#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{
    long int n,m;
    while(scanf("%ld %ld",&n,&m)!=EOF)
    {
        long int sz=pow(2,n);
        //printf("%d--->",sz);
        long int *A=(long int*)malloc(sizeof(long int)*sz);
        long int **B=(long int**)malloc(sizeof(long int*)*sz);
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
                printf("%ld...",A1[i]);
            }
        }
        /*
        while(1==1)
        {
            long int *TA1=(long int*)malloc(sizeof(long int)*sz);
            long int j=0;
            for(i=0;i<sz;i+=2)
            {
                TA1[j++]=A1[i]|A1[i+1];
            }

            if(TA1[0]==0) break;
        }
        for(i=0;i<sz/2;i++)
        {
            printf("---%ld",TA1[i]);
        }
        */
    }
    return 0;
}
