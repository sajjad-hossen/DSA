#include<bits/stdc++.h>
using namespace std;
#define must ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long int
const int mod=998244353;
ll expo(ll a, ll b, ll mod)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)res = (res * a) % mod;
        a = (a * a) % mod;
        b = b >> 1;
    }
    return res;
}
ll mod_mul(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (((a * b) % m) + m) % m;
}
ll mminvprime(ll a, ll b)
{
    return expo(a, b - 2, b);
}
ll mod_div(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (mod_mul(a, mminvprime(b, m), m)+m) % m;
}
int main()
{
  string s;
  cin>>s;
  ll sz=s.size();
  ll val=stoi(s);
  ll a=expo(10,sz,mod);
  ll b=expo(a,val,mod);
  a=(a-1+mod)%mod;
  b=(b-1+mod)%mod;
  ll ans=mod_div(b,a,mod);
  ans=mod_mul(ans,val,mod);
  cout<<ans<<endl;
}
