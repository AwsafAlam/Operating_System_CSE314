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

bool **bitmask;
int **level;
long long int n,m,x,y,a,b;


int bfs(long long int x,long long int y)
{
    if((x==n && y==m)||(x==n && y==1)||(x==1 && y==1)||(x==1 && y==m)) return 0;
    vector <long long int> A;
    A.pb(x);
    A.pb(y);
    while(A.size()!=0)
    {
        long long int tx,ty;
        tx=A[0];
        ty=A[1];
        A.erase(A.begin());
        A.erase(A.begin());

        if(tx+a<=n && ty+b<=m && bitmask[tx+a][ty+b])
        {
            long long int t1,t2;
            t1=tx+a;
            t2=ty+b;

            A.pb(tx+a);
            A.pb(ty+b);

            bitmask[tx+a][ty+b]=0;
            level[tx+a][ty+b]=level[tx][ty]+1;

            if((t1==n && t2==m)||(t1==n && t2==1)||(t1==1 && t2==1)||(t1==1 && t2==m)) return level[t1][t2];
        }
        if(tx+a<=n && ty-b>=1 && bitmask[tx+a][ty-b])
        {
            long long int t1,t2;
            t1=tx+a;
            t2=ty-b;

            A.pb(tx+a);
            A.pb(ty-b);
            bitmask[tx+a][ty-b]=0;
            level[tx+a][ty-b]=level[tx][ty]+1;

            //if((t1==n && t2==1)) return level[t1][t2];
            if((t1==n && t2==m)||(t1==n && t2==1)||(t1==1 && t2==1)||(t1==1 && t2==m)) return level[t1][t2];
        }
        if(tx-a>=1 && ty-b>=1 && bitmask[tx-a][ty-b])
        {
            long long int t1,t2;
            t1=tx-a;
            t2=ty-b;

            A.pb(tx-a);
            A.pb(ty-b);
            bitmask[tx-a][ty-b]=0;
            level[tx-a][ty-b]=level[tx][ty]+1;

            //if((t1==1 && t2==1)) return level[t1][t2];
            if((t1==n && t2==m)||(t1==n && t2==1)||(t1==1 && t2==1)||(t1==1 && t2==m)) return level[t1][t2];
        }
        if(tx-a>=1 && ty+b<=m && bitmask[tx-a][ty+b])
        {
            long long int t1,t2;
            t1=tx-a;
            t2=ty+b;

            A.pb(tx-a);
            A.pb(ty+b);
            bitmask[tx-a][ty+b]=0;
            level[tx-a][ty+b]=level[tx][ty]+1;

            //if((t1==1 && t2==m)) return level[t1][t2];
            if((t1==n && t2==m)||(t1==n && t2==1)||(t1==1 && t2==1)||(t1==1 && t2==m)) return level[t1][t2];
        }
    }
    return -1;
}

int main()
{
    while(cin>>n>>m>>x>>y>>a>>b)
    {
        long long int i,j;
        bitmask=(bool**)malloc(sizeof(bool*)*(n+1));
        level=(int**)malloc(sizeof(int*)*(n+1));
        for(i=0;i<=n;i++)
        {
            *(bitmask+i)=(bool*)malloc(sizeof(bool)*(m+1));
            *(level+i)=(int*)malloc(sizeof(int)*(m+1));
            for(j=0;j<=m;j++)
            {
                bitmask[i][j]=1;
                level[i][j]=0;
            }
        }

        int result=0;
        bitmask[x][y]=1;

        result=bfs(x,y);

        if(result==-1) cout<<"Poor Inna and pony!"<<endl;
        else cout<<result<<endl;

        free(bitmask);
        free(level);
    }
    return 0;
}
