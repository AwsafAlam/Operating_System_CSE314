#include <stdio.h>
#include <string.h>
int main(void)
{
    char s[105];
    while(scanf("%s",s)!=EOF)
    {
        int len=strlen(s);
        int i,j;
        for(i=2;i<len;i+=2)
        {
            for(j=0;j<len-i;j+=2)
            {
                if(s[j]>s[j+2])
                {
                    char temp;
                    temp=s[j];
                    s[j]=s[j+2];
                    s[j+2]=temp;
                }
            }
        }
        printf("%s\n",s);
    }
    return 0;
}
