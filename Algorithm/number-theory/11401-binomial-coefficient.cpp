#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

ll MOD = 1000000007; // 소수, 페르마 사용 가능.

ll modpow(ll a, ll e, ll p) {
    ll res=1;
    while (e>0) {
        if (e&1) res= (__int128)res*a%p;
        a=(__int128)a*a%p;
        e>>=1;
    }
    return res;
}

ll fact(ll a, ll m){
    ll r=1%m;
    for (ll i=a;i>0;i--){
        r = (__int128)r*(i%m) %m;
    }
    return r;
}

ll inv_fact(ll a, ll m) {
    ll f = fact(a,m);
    return modpow(f,m-2,m);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll N, K;
    cin>>N>>K;
    ll ans = (__int128)fact(N,MOD)*inv_fact(K,MOD) % MOD;
    ans = (__int128)ans*inv_fact(N-K,MOD) % MOD;
    cout<<ans;
}
