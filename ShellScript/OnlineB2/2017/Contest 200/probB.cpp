#include <stdio.h>
int main(void)
{
    int A[3];
    while(scanf("%d %d %d",&A[0],&A[1],&A[2])!=EOF)
    {
        int i,j,k,maxm[3],total=0,order[3];
        maxm[0]=A[0];
        maxm[1]=A[1];
        maxm[2]=A[2];
        order[0]=0;
        order[1]=1;
        order[2]=2;
        int d=0;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3-i;j++)
            {
                if(maxm[j]<maxm[j+1])
                {
                    int temp;
                    temp=maxm[j];
                    maxm[j]=maxm[j+1];
                    maxm[j+1]=temp;
                }
            }
        }
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(maxm[j]==A[i])
                {
                    order[i]=j;
                }
            }
        }
        for(i=0;i<3;i++)
        {
            printf("%d %d\n\n",maxm[i],order[i]);
        }
        for(i=0;i<=maxm[0];i++)
        {
            for(j=0;j<=maxm[1];j++)
            {
                for(k=0;k<=maxm[2];k++)
                {
                    if((i+j+k)*2 > total)
                    {
                       break;
                    }
                    else
                    {
                        if((k+i)==A[order[0]] && (i+j)==A[order[1]] && (j+k)==A[order[2]])
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
