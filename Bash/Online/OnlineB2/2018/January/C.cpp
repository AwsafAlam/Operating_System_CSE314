#include <bits/stdc++.h>
using namespace std;
vector<long long int> f;
long long int freq(long long int temp)
{
    if(temp==1) return 1;
    else
    {
        long long int t= temp/2;
        if(2*t<temp) t++;
        return 1+freq(t);
    }
}

bool myfunction(int a,int b)
{
    return a>b;
}

int main(void)
{
    long long int n;
    cin>>n;
    vector<long long int> A(n);
    vector<long long int> sum(n+1);
    f.push_back(0);
    for(int i=0;i<n;i++)
    {
        cin>>A[i];
        int temp=i+1;
    }
    sort(A.begin(),A.end(),myfunction);
    sum[0]=0;
    for(int i=0;i<n;i++)
    {
        sum[i+1]=sum[i]+A[i];
    }
    long long int fr=freq(n);
    cout<<n <<": "<<fr<<"Sum= "<<sum[n]<<endl;
    long long int score=sum[n]*(fr-1);
    cout<<"score="<<score<<endl;
    int LN=n-1;
    while(LN)
    {
        score+=sum[LN];
        LN--;
    }
    cout<<score<<endl;
    return 0;
}
