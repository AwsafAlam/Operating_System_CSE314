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
    long long int n;
    while(cin>>n)
    {
        int result=0;
        int carry[]={0,0,0,0};
        long long int i;
        vector <int> A(n);
        for(i=0;i<n;i++)
        {
            cin>>A[i];
        }
        SORT(A);
        for(i=n-1;i>=0;i--)
        {
            if(A[i]==4) result++;
            else if(A[i]==3)
            {
                result++;
                carry[1]++;
            }
            else if(A[i]==2)
            {
                if(carry[2]==0)
                {
                    result++;
                    carry[2]=2;
                }
                else
                {
                    carry[2]=0;
                }
            }
            else if(A[i]==1)
            {
                if(carry[1]) carry[1]--;
                else if(carry[2]) carry[2]--;
                else
                {
                    result++;
                    carry[1]=3;
                }
            }
        }
        cout<<result<<endl;
        A.clear();
    }
    return 0;
}
