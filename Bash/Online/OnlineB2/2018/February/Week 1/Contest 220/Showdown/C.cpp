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
    int n,i;
    cin>>n;
    for(i=0;i<n;i++)
    {
        int p;
        char str[105];
        cin>>str;
        p=strlen(str);
        if(p<=10) cout<<str<<endl;
        else cout<<str[0]<<p-2<<str[p-1]<<endl;
    }
    return 0;
}
