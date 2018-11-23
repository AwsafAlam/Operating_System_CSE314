#define SORT(A) sort(A.begin(),A.end());
#define MAX 500000
#define pb push_back

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
    char str[200];
    while(cin>>str)
    {
        char result[200];
        int len=strlen(str);
        int i,len_result=0;
        for(i=0;i<len;i++)
        {
            char ch=tolower(str[i]);
            if(ch!='a' && ch!='e' && ch!='i' && ch!='o' && ch!='u' && ch!='y')
            {
                result[len_result]='.';
                result[len_result+1]=ch;
                len_result+=2;
            }
        }
        result[len_result]='\0';
        cout<<result<<endl;
    }
    return 0;
}
