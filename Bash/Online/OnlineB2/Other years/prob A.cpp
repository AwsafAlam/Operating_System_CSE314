#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    long long int x,y;
    while(scanf("%I64d %I64d",&x,&y)!=EOF)
    {
        long long int x1,y1;
        if(x>0) x1=x+abs(y);
        else x1=x-abs(y);
        if(y>0) y1=y+abs(x);
        else y1=y-abs(x);
        if(x1<0) printf("%I64d 0 0 %I64d\n",x1,y1);
        else printf("0 %I64d %I64d 0\n",y1,x1);
    }
    return 0;
}
