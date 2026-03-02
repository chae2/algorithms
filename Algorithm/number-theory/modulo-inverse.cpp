#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

ll MOD = 1000000007;

ll modpow(ll a, ll e, ll p) {
   ll res=1;
   while (e>0) {
      if (e&1) res=res*a%p;
      a=a*a%p;
      e>>=1;
   }
   return res;
}
ll modulo_EEA(ll a, ll m) { // Extended Euclidean Algorithm
   // q, r1, r2, r, s1, s2, s, t1, t2, t
   // 초기화
   ll r1=a, r2=m, s1=1, s2=0, t1=0, t2=1;
   ll q=r1/r2, r=r1%r2;
   ll s=s1-s2*q, t=t1-t2*q;
   while (r!=0) {
      r1=r2; r2=r; s1=s2; s2=s; t1=t2; t2=t; // 값 업데이트
      q=r1/r2;
      s=s1-s2*q;
      t=t1-t2*q;
      r=r1%r2;
   }
   return s2;
}

int main(){
   ios::sync_with_stdio(false); cin.tie(nullptr);
   // cout<<modpow(3,9,11)<<"\n";
   ll N, A;
   cin>>N>>A;
   ll add = modulo_add(A,N);
   if (gcd(A,N)==1) {
      ll mult = modulo_EEA(A,N);
      while (mult<0) mult+=N;
      cout<<add<<" "<<mult<<"\n";
   }
   else cout<<add<<" "<<-1<<"\n";
}
