#define FOR(i,n) for(i=0;i<n;i++)
#define PB push_back
#define SORT(A) sort(A.begin(),A.end())
#define DEL(A,i) A.erase(A.begin()+i);


#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;
int main(void)
{
    //ios::sync_with_stdio(0);
    long long int n,t,c;
    while(cin>>n>>t>>c)
    {
        vector<long long int> A(n+1);
        //vector<int> S(n+1);
        vector<long long int> CS(n+1);
        A[0]=0;
        //S[0]=0;
        CS[0]=0;
        long long int result=0;
        for(long long int i=1;i<=n;i++)
        {
            long long int num;
            cin>>num;
            if(num<=t)
            {
                //S[i]=1;
                CS[i]=CS[i-1]+1;
            }
            else
            {
                if(CS[i-1]-c+1 >0) result+=(CS[i-1]-c)+1;
                //cout<<CS[i-1]<<"   "<<endl;
                //S[i]=0;
                CS[i]=0;
            }
        }
        if(CS[n]-c+1 >0) result+=(CS[n]-c)+1;
        cout<<result<<endl;
    }
    return 0;
}

