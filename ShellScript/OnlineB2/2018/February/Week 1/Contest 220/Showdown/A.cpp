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
    long long int n,m,a;
    while(cin>>n>>m>>a)
    {
        long long int r1,r2;
        r1=(n/a);
        if(a*r1<n) r1++;
        r2=(m/a);
        if(a*r2<m) r2++;
        cout<<r1*r2<<endl;
    }
    return 0;
}
