#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 998244353

ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}

int main()
{
    ll n;cin>>n;
    // n %= MOD;

    ll nod = 0;
    ll x = n;
    while(x){
        nod++;
        x /= 10;
    }

    ll b = expo(10, nod, MOD);
    ll a = expo(b, n, MOD);
    cout<<a<<" "<<b<<" "<<nod<<endl;
    b = (b-1+MOD) % MOD;
    a = (a-1+MOD % MOD);
    ll ans = mod_div(a,b,MOD);
    ans = mod_mul(ans, n, MOD);
    cout<<ans;
}

