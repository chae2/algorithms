#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using ull = unsigned long long;

int MAX_PAGE = 500;
int DP[MAX_PAGE+1];
int T,K;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>T;
    while (T--) {
        
    }

}

// int main() {
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     cin>>T;
//     while (T--) {
//         cin>>K;
//         int C[501];
//         ll sum[501];
//         sum[0]=0;
//         ll dp[501][501];
//         ll opt[501][501];
//
//         for (int i=1;i<=K;i++) {
//             cin>>C[i]; sum[i]=sum[i-1]+C[i];
//         }
//         for (int i=1;i<=K;i++) {
//             dp[i-1][i]=0; opt[i-1][i]=i;
//         }
//         for (int d=2;d<=K;d++) {
//             for (int i=0; i+d<=K; i++) {
//                 int j=i+d;
//                 dp[i][j] = 2e9;
//                 for (int a=opt[i][j-1]; a<=opt[i+1][j]; a++) {
//                     int v=dp[i][a] + dp[a][j] +sum[j]-sum[i];
//                     if (dp[i][j]>v) {
//                         dp[i][j]=v; opt[i][j]=a;
//                     }
//                 }
//             }
//         }
//         cout<<dp[0][K]<<"\n";
//     }
// }