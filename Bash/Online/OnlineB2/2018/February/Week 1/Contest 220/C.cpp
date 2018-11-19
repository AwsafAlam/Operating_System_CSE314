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
    long long int n,m,x,y,a,b;
    while(cin>>n>>m>>x>>y>>a>>b)
    {
        long long int d1,d2,d3,d4;
        if((n-x)%a==0 && (m-y)%b==0)
        {
            d1=max((n-x)/a,(m-y)/b);
        }
        else d1=-1;
        if((n-x)%a==0 && (y-1)%b==0)
        {
            d2=max((n-x)/a,(y-1)/b);
        }
        else d2=-1;
        if((x-1)%a==0 && (y-1)%b==0)
        {
            d3=max((x-1)/a,(y-1)/b);
        }
        else d3=-1;
        if((x-1)%a==0 && (m-y)%b==0)
        {
            d4=max((x-1)/a,(m-y)/b);
        }
        else d4=-1;
        d1=min(d1,d2);
        d3=min(d3,d4);
        d1=min(d1,d3);
        cout<<d1<<endl;
    }
    return 0;
}
