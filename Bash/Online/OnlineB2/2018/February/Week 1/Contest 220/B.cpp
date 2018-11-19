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
    char *str;
    str=(char*)malloc(sizeof(char)*2000000);
    while(cin>>str)
    {
        long long int len=strlen(str);
        long long int result=1;
        long long int i,temp=0;

        for(i=1;i<len;i++)
        {
            if(((str[i]-'0')+(str[i-1]-'0'))==9)
            {
                temp++;
            }
            else
            {
                if(temp && temp%2==0) result*=(1+(temp/2));
                temp=0;
            }
        }
        if(temp && temp%2==0) result*=(1+(temp/2));
        cout<<result<<endl;
    }
    return 0;
}
