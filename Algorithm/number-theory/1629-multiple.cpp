#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

ll MOD = 1000000007;

ll daq_pow(ll a, ll b, ll m) {
    a %= m;
    ll r = 1%m;
    while (b) {
        if (b&1) r=(r*a)%m; // b가 짝수면
        a=(a*a)%m; // a^2
        b>>=1;     // b를 2로 나눈다
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll a,b,c;
    cin>>a>>b>>c;
    cout<<daq_pow(a,b,c);
}