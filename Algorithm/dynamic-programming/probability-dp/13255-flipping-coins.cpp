// #include <algorithm>
// #include <iostream>
// #include <sstream>
// #include <bits/stdc++.h>
// #include <vector>
// using namespace std;
// typedef long long ll;
// using pii = pair<int,int>;
// using pil = pair<int,ll>;
// using ipii = pair<int,pii>;
// const int MAXN = 1000;
//
// long double memo[MAXN+2][MAXN+2];
// bool visited[MAXN+2][MAXN+2];
// ll C[MAXN+2][MAXN+2];
//
// void init_combination() {
//     for (int n=0; n<MAXN; n++) {
//         C[n][0] = C[n][n] = 1;
//         for (int k=1; k<n; k++) {
//             C[n][k] = C[n-1][k-1] + C[n-1][k];
//         }
//     }
// }
//
// int N, K; // K : 총 단계 수; N: 동전 수
// vector<int> A;
//
// long double xoxo(int idx, int f) {
//     if (idx> K) return f;
//
//     if (visited[idx][f]) return memo[idx][f];
//     visited[idx][f] = true;
//
//     const int k = A[idx], b = N-f;
//     ll sum=0;
//     vector<pil> ways;
//
//     for (int i=0; i<=k; i++) {
//         if (i>f || k-i>b) continue;
//         ll way = C[f][i] * C[b][k-i]; //combination(f,i)*combination(b,k-i);
//         int new_f = f+k-2*i; // f-i+(k-i);
//         ways.push_back({new_f, way});
//         sum += way;
//     }
//
//     long double res = 0;
//     for (auto& [new_f,w] : ways) {
//         res += ((long double) w/sum) * xoxo(idx+1, new_f);
//     }
//
//     return memo[idx][f] = res;
// }
//
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0); cout.tie(0);
//
//     cin>> N>>K;
//     A.assign(K+1, 0);
//     for (int i=1;i<=K; ++i) cin>>A[i];
//
//     init_combination();
//
//     int first_front = N-A[1];
//     if (N>1) {
//         long double ans = xoxo(2, first_front);
//         cout<<fixed<<setprecision(15)<<(double) ans;
//     }else {
//         cout<<first_front;
//     }
// }

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    long double h = 1.0;                 // h₀
    for (int i = 0; i < K; ++i) {
        int a;   cin >> a;
        long double p = (long double)a / N;
        h = h * (1 - 2 * p) + p;         // hᵢ
    }
    cout << fixed << setprecision(15) << (double)(N * h) << '\n';
    return 0;
}
