#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define must ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const int N=2e5+12;
int arr[N];
vector<int>vt[N];
int dp[N];
int ans[N];
void dfs1(int node,int par)
{
    ans[node]=dp[node];
    for(auto it:vt[node])
    {
        if(it!=par)
        {
            dp[node]-=max(dp[it],0LL);
            dp[it]+=(max(0LL,dp[node]));
            dfs1(it,par);
            dp[it]-=(max(0LL,dp[node]));
            dp[node]+=(max(0LL,dp[it]));
        }
    }
}
void dfs(int node,int par)
{
    dp[node]=arr[node];
    for(auto it:vt[node])
    {
        if(it!=par)
        {
            dfs(it,node);
            dp[node]+=max(0LL,dp[it]);
        }
    }
}
signed main()
{
    must;
    int t=1;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1; i<=n; i++)
        {
            cin>>arr[i];
            if(arr[i]==0)arr[i]=-1;
        }
        for(int i=1; i<n; i++)
        {
            int x,y;
            cin>>x>>y;
            vt[x].push_back(y);
            vt[y].push_back(x);
        }
        dfs(1,-1);
        dfs1(1,-1);
        for(int i=1; i<=n; i++)
        {
            cout<<ans[i]<<" ";
        }
        cout<<endl;
    }
}
//https://codeforces.com/contest/1324/problem/F
