#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
int power(long long n, long long k, const int mod)
{
    int ans = 1 % mod;
    n %= mod;
    if (n < 0) n += mod;
    while (k)
    {
        if (k & 1) ans = (long long) ans * n % mod;
        n = (long long) n * n % mod;
        k >>= 1;
    }
    return ans;
}

const int MOD1 = 127657753, MOD2 = 987654319;
const int p1 = 137, p2 = 277;
int ip1, ip2;
pair<int, int> pw[N], ipw[N];
void prec()
{
    pw[0] =  {1, 1};
    for (int i = 1; i < N; i++)
    {
        pw[i].first = 1LL * pw[i - 1].first * p1 % MOD1;
        pw[i].second = 1LL * pw[i - 1].second * p2 % MOD2;
    }
    ip1 = power(p1, MOD1 - 2, MOD1);
    ip2 = power(p2, MOD2 - 2, MOD2);
    ipw[0] =  {1, 1};
    for (int i = 1; i < N; i++)
    {
        ipw[i].first = 1LL * ipw[i - 1].first * ip1 % MOD1;
        ipw[i].second = 1LL * ipw[i - 1].second * ip2 % MOD2;
    }

}
struct Hashing
{
    int n;
    string s;
    vector<pair<int, int>> hs;
    Hashing() {}
    Hashing(string _s)
    {
        n = _s.size();
        s = _s;
        hs.emplace_back(0, 0);
        for (int i = 0; i < n; i++)
        {
            pair<int, int> p;
            p.first = (hs[i].first + 1LL * pw[i].first * s[i] % MOD1) % MOD1;
            p.second = (hs[i].second + 1LL * pw[i].second * s[i] % MOD2) % MOD2;
            hs.push_back(p);
        }
    }
    pair<int, int> get_hash(int l, int r)
    {
        assert(1 <= l && l <= r && r <= n);
        pair<int, int> ans;
        ans.first = (hs[r].first - hs[l - 1].first + MOD1) * 1LL * ipw[l - 1].first % MOD1;
        ans.second = (hs[r].second - hs[l - 1].second + MOD2) * 1LL * ipw[l - 1].second % MOD2;
        return ans;
    }
    pair<int, int> get_hash()
    {
        return get_hash(1, n);
    }
};
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    prec();
    int t;
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        if(s.size()%2==1)
        {
            cout<<0<<endl;
            continue;
        }
        int n=s.size();
        Hashing h(s);
        int cnt = 0;
        for (int i = 0; i<(n/2)-1; i ++)
        {
            int l1 = 0, r1 = i;       // T1
            int l2 = r1+1, r2 = l2 + i;      // T2
            int l3 = r2+1, r3 = i + n/2;  // T3
            int l4 = r3+1, r4 = n - 1;      // T3
            if (h.get_hash(l1+1, r1+1) == h.get_hash(l2+1, r2+1) &&h.get_hash(l3+1, r3+1) ==h.get_hash(l4+1, r4+1))
            {

                cnt++;
            }
        }
        if(h.get_hash(1, n/2) ==h.get_hash((n/2)+1, n))cnt++,cnt++;
        cout<<cnt<<"\n";
    }
}
//https://www.codechef.com/problems/BREAKSTRING
