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
    int n,k;
    while(cin>>n>>k)
    {
        vector <int> A(n);
        int i,result;
        for(i=0;i<n;i++) cin>>A[i];
        result=k;
        if(A[k-1]>0)
        {
            for(i=k;i<n;i++)
            {
                if(A[i]==A[k-1]) result++;
                else break;
            }
        }
        else
        {
            for(i=k-1;i>=0;i--)
            {
                if(A[i]>0) break;
                result--;
            }
        }
        cout<<result<<endl;
        A.clear();
    }
    return 0;
}
