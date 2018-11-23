#define PB push_back
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#define sort(A) sort(A.begin(),A.end())


using namespace std;

int main(void)
{
    long long int w,m,k;
    while(cin>>w>>m>>k)
    {
        long long int temp,result=0,t;

        char str[50];
        sprintf(str,"%I64d",m);
        long long int len=strlen(str);
        temp=(pow(10,len)-m);
        w-=temp*len*k;
        if(w<0)
        {
            t=(abs(w)/(len*k));
            w+=len*k*t;
            temp-=t;
            if(w<0)
            {
                w=0;
                temp--;
            }
        }
        result+=temp;
        len++;
        while(w!=0)
        {
            temp=(pow(10,len)-pow(10,len-1));
            w-=temp*len*k;
            if(w<0)
            {
                t=(abs(w)/(len*k));
                w+=len*k*t;
                temp-=t;
                if(w<0)
                {
                    w=0;
                    temp--;
                }
            }
            result+=temp;
            len++;
        }
        cout<<result<<endl;
    }
    return 0;
}
