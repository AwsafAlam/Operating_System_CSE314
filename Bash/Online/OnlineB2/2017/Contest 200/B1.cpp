#include <stdio.h>
int main(void)
{
    int A[3];
    while(scanf("%d %d %d",&A[0],&A[1],&A[2])!=EOF)
    {
        int temp[3];
        temp[0]=A[0];
        temp[1]=A[1];
        temp[2]=A[2];
        int i,j;
        int p=1;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3-i;j++)
            {
                if(temp[j]<temp[j+1])
                {
                    int t=temp[j];
                    temp[j]=temp[j+1];
                    temp[j+1]=t;
                }
            }
        }
        int tm[3],result[3]={0};
        tm[0]=temp[0];
        tm[1]=temp[1];
        tm[2]=temp[2];
        float r1;
        r1=temp[1]/temp[2];
        while(tm[0]>0)
        {
            int tag=0;
            if(r1>=1)
            {
                if(tm[1]>0)
                {
                    result[0]++;
                    tm[0]--;
                    tm[1]--;
                    tag=1;
                }
                r1-=1;
            }
            if(tm[0]>0 && r1<1)
            {
                if(tm[2]>0)
                {
                    result[2]++;
                    tm[0]--;
                    tm[2]--;
                    tag=1;
                }
                r1+=1;
            }
            if(tag==0)
            {
                p=0;
                break;
            }
        }
        if(tm[1]!=tm[2])
        {
            p=0;
        }
        else
        {
            result[1]=tm[1];
        }
        int B[3]={0};
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(A[i]==temp[j])
                {
                    if(B[j]==0)
                    {
                        A[i]=j;
                        B[j]=1;
                        break;
                    }
                }
            }
        }

        int t_result[3];
        t_result[0]=result[0];
        t_result[1]=result[1];
        t_result[2]=result[2];
        if(A[0]==0 && A[1]==2)
        {
            t_result[0]=result[2];
            t_result[2]=result[0];
        }
        else if(A[0]==1 && A[1]==0)
        {
            t_result[1]=result[2];
            t_result[2]=result[1];
        }
        else if(A[0]==1 && A[1]==2)
        {
            t_result[0]=result[1];
            t_result[1]=result[2];
            t_result[2]=result[0];
        }
        else if(A[0]==2 && A[1]==0)
        {
            t_result[0]=result[2];
            t_result[1]=result[0];
            t_result[2]=result[1];
        }
        else if(A[0]==2 && A[1]==1)
        {
            t_result[0]=result[1];
            t_result[1]=result[0];
        }
        if(p==1) printf("%d %d %d\n",t_result[0],t_result[1],t_result[2]);
        else printf("Impossible\n");
    }
    return 0;
}
