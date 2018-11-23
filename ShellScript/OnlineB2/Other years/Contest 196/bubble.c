#include <stdio.h>
int main(void)
{
    int A[5]={3,7,6,3,9};
    int i,j;
    for(i=1;i<5;i++)
    {
        for(j=0;j<5-i;j++)
        {
            if(A[j]<A[j+1])
            {
                int temp;
                temp=A[j];
                A[j]=A[j+1];
                A[j+1]=temp;
            }
        }
    }
    for(i=0;i<5;i++)
    {
        printf("%d\t",A[i]);
    }
}
