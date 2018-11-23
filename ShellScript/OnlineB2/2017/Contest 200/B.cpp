#include <stdio.h>
int main(void)
{
    int A[3];
    while(scanf("%d %d %d",&A[0],&A[1],&A[2])!=EOF)
    {
        int i,j,k,total=0,minm[3];
        total=A[0]+A[1]+A[2];
        int d=0;
        minm[0]=A[0]<A[1] ? A[0]:A[1];
        minm[1]=A[1]<A[2] ? A[1]:A[2];
        minm[2]=A[2]<A[0] ? A[2]:A[0];
        for(i=0;i<=minm[0];i++)
        {
            for(j=0;j<=minm[1];j++)
            {
                for(k=0;k<=minm[2];k++)
                {
                    if((i+j+k)*2 > total)
                    {
                        break;
                    }
                    else
                    {
                        if((k+i)==A[0] && (i+j)==A[1] && (j+k)==A[2])
                        {
                            printf("%d %d %d\n",i,j,k);
                            d=1;
                            goto label;
                        }
                    }
                }
            }
        }
        if(d==0) printf("Impossible\n");
        label:
            ;
    }
    return 0;
}
