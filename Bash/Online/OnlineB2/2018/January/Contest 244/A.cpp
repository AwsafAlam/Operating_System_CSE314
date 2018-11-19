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
    ios::sync_with_stdio(0);
    long int n;
    while(cin>>n)
    {
        int UR=0;
        int EM=0;
        vector<int> A(n);
        for(int i=0;i<n;i++)
        {
            cin>>A[i];
            if(A[i]==-1)
            {
                if(EM==0) UR++;
                else EM--;
            }
            else EM+=A[i];
        }
        cout<<UR<<endl;
    }
    return 0;
}

