#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <iomanip>
#include <queue>
using namespace std;
typedef long long ll;
using i128 = __int128_t;
using ld = long double;
int N;

struct Pt {ll x,y;};

ld triangle_area(int i, int j, int k, const vector<Pt>& P) {
    // 신발끈 공식, 1/2은 안 곱함 (비교용)
    __int128 x1 = P[i].x*P[j].y;
    __int128 x2 = P[j].x*P[k].y;
    __int128 x3 = P[k].x*P[i].y;
    __int128 y1 = P[j].x*P[i].y;
    __int128 y2 = P[k].x*P[j].y;
    __int128 y3 = P[i].x*P[k].y;

    __int128 z = x1+x2+x3-y1-y2-y3;

    // if (z<0) z=-z;
    return (ld) z;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin>>N;
    vector<Pt> P(N);
    for (auto& p : P) cin>>p.x>>p.y;
    // 0 - i - i+1
    ld S = 0;
    for (int i=1;i<N-1;i++) {
        S += triangle_area(0,i,i+1,P);
    }
    S/=2.0L;
    cout<<fixed<<setprecision(1)<<abs(S)<<"\n";
}

// #include <bits/stdc++.h>
// using namespace std;
// using i128 = __int128_t;
//
// int main() {
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     int N; cin >> N;
//
//     long long x0, y0, x, y, px, py;
//     cin >> x0 >> y0;               // 첫 점
//     px = x0; py = y0;
//
//     i128 S = 0;
//     for (int i = 1; i < N; ++i) {  // 중간 점들
//         cin >> x >> y;
//         S += (i128)px * y - (i128)x * py;
//         px = x; py = y;
//     }
//     S += (i128)px * y0 - (i128)x0 * py; // 마지막-첫 점 닫기
//
//     if (S < 0) S = -S;
//     long double area = (long double)S / 2.0L;
//     cout << fixed << setprecision(1) << area << '\n';
// }
