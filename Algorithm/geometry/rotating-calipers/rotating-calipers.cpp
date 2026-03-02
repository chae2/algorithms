#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using ull = unsigned long long;

int N, H;
ull max_len_square; // 가장 긴 두 점 거리 저장
int inf = 1<<30;

struct Pt {ll x,y;};
struct Node {double ang; ll dist; Pt p;}; // dist는 거리

using ppt = pair<Pt, Pt>;

static inline ull dist2(const Pt& a, const Pt& b){
    __int128 dx = a.x - b.x, dy = a.y - b.y;
    return (ull)(dx*dx + dy*dy);
}
ull triangle_area(int i, int j, int k, const vector<Pt>& P) {
    // 신발끈 공식, 1/2은 안 곱함 (비교용)
    __int128 x1 = P[i].x*P[j].y;
    __int128 x2 = P[j].x*P[k].y;
    __int128 x3 = P[k].x*P[i].y;
    __int128 y1 = P[j].x*P[i].y;
    __int128 y2 = P[k].x*P[j].y;
    __int128 y3 = P[i].x*P[k].y;

    __int128 z = x1+x2+x3-y1-y2-y3;

    if (z<0) z=-z;
    return (ull) z;
    //
    // return abs(x1+x2+x3-y1-y2-y3);
    // return abs(P[i].x*P[j].y+P[j].x*P[k].y+P[k].x*P[i].y
    //     -P[j].x*P[i].y-P[k].x*P[j].y-P[i].x*P[k].y);
}

void move(int l, int r, const vector<Pt>& P, ppt& ans) {
    int rr = (r+1)%H;
    ppt k = dist2(P[l],P[r])>dist2(P[l],P[rr]) ? ppt(P[l],P[r]) : ppt(P[l],P[rr]);
    ull len = dist2(P[l],P[r])>dist2(P[l],P[rr]) ? dist2(P[l],P[r]) : dist2(P[l],P[rr]);
    ans = len>max_len_square ? k : ans;
    max_len_square = len>max_len_square ? len : max_len_square;
}

// AB와 AC의 벡터 외적
bool counter_clockwise(const Pt& a, const Pt& b, const Pt& c) {
    __int128 x1 = b.x-a.x, y1 = b.y-a.y;
    __int128 x2 = c.x-a.x, y2 = c.y-a.y;
    __int128 z = x1*y2 - y1*x2;
    return z>0; // 0인 경우(collinear)도 배제.
}

vector<Pt> grahamScan(const vector<Pt>& P) {
    Pt std = P[0];
    auto angle_of = [std](const Pt& q)->double {
        return atan2((double)(q.y-std.y),(double)(q.x-std.x));
    };
    auto cmp = [](const Node& A, const Node& B) {
        if (A.ang != B.ang) return A.ang > B.ang;
        if (A.dist != B.dist) return A.dist > B.dist;
        if (A.p.x != B.p.x) return A.p.x > B.p.x;
        return A.p.y>B.p.y;
    };
    priority_queue<Node,vector<Node>,decltype(cmp)> pq(cmp);
    // 각도별 정렬
    // P[0]이 기준점이라 P[1]부터 실행
    for (int i=1; i<N; i++) {
        double ang = angle_of(P[i]);
        ll dist = hypot(P[i].x-std.x, P[i].y-std.y);
        pq.push(Node{ang, dist, P[i]});
    }

    vector<Pt> stk;
    stk.push_back(std);
    while (!pq.empty()) {
        Pt next = pq.top().p; pq.pop();
        while (stk.size()>=2) { // 2개가 쌓였을 때부터 prev now로 사용 가능
            Pt now = stk.back(), prev = stk[stk.size()-2];
            if (!counter_clockwise(prev, now, next)) stk.pop_back();
            else break;
        }
        if (stk.size()==1 && next.x==std.x && next.y==std.y) continue; // 기준점 중복 들어가는 것 회피
        stk.push_back(next); // hull에 추가
    }
    return stk;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--){
        cin>>N;
        vector<Pt> P(N);
        Pt std = {inf,inf};
        int i=0, piv=0;
        for (auto& p : P) {
            cin>>p.x>>p.y;
            // 기준 좌표 구하기; P[0]으로 정의
            if (p.y<std.y || (p.y==std.y && p.x<std.x)) {
                piv = i;
                std = {p.x,p.y};
            }
            i++;
        }
        swap(P[0],P[piv]);

        vector<Pt> vec = grahamScan(P);
        max_len_square=0;
        H = vec.size();
        ppt ans = {{0,0},{0,0}};
        if (H==2) {
            move(0,1,vec,ans);
            // max_len_square = dist2(vec[0],vec[1]);
        } else {
            int l=0, r=1;
            while (triangle_area(H-1,l,r,vec)<triangle_area(H-1,l,(r+1)%H,vec)) ++r; // r 초기화
            while (r<H) {
                // cout<<"("<<l<<", "<<l+1<<") - r: "<<r<<"\n";
                // max_len 정함
                // max_len_square = max(max_len_square, max(dist2(vec[l],vec[r]), dist2(vec[l],vec[(r+1)%H])));
                move(l,r,vec, ans);
                if (triangle_area(l,l+1,r,vec)<triangle_area(l,l+1,(r+1)%H,vec)) ++r;
                else ++l;
            }
        }
        Pt fst = ans.first, sec = ans.second;
        cout<<fst.x<<" "<<fst.y<<" "<<sec.x<<" "<<sec.y<<"\n";
    }
}

// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;
// using ull = unsigned long long;
//
// struct Pt { ll x, y; };
//
// static inline long long ccw(const Pt& a, const Pt& b, const Pt& c) {
//     __int128 x1 = b.x - a.x, y1 = b.y - a.y;
//     __int128 x2 = c.x - a.x, y2 = c.y - a.y;
//     __int128 z  = x1*y2 - y1*x2;
//     if (z > 0) return 1;
//     if (z < 0) return -1;
//     return 0;
// }
//
// static inline ull dist2(const Pt& a, const Pt& b){
//     __int128 dx = a.x - b.x, dy = a.y - b.y;
//     return (ull)(dx*dx + dy*dy);
// }
//
// // 신발끈 공식: 면적*2 (비교용)
// static inline ull area2(const Pt& a, const Pt& b, const Pt& c){
//     __int128 x1 = b.x - a.x, y1 = b.y - a.y;
//     __int128 x2 = c.x - a.x, y2 = c.y - a.y;
//     __int128 z  = x1*y2 - y1*x2;
//     if (z < 0) z = -z;
//     return (ull)z;
// }
//
// vector<Pt> grahamHull(vector<Pt> P){
//     int n = (int)P.size();
//     if (n <= 1) return P;
//
//     // pivot = (y 최소, tie면 x 최소) 를 P[0]에
//     int piv = 0;
//     for (int i=1;i<n;i++){
//         if (P[i].y < P[piv].y || (P[i].y==P[piv].y && P[i].x < P[piv].x))
//             piv = i;
//     }
//     swap(P[0], P[piv]);
//     Pt O = P[0];
//
//     struct Node { double ang; ull r2; Pt p; };
//     vector<Node> A; A.reserve(n-1);
//     for (int i=1;i<n;i++){
//         double ang = atan2((double)(P[i].y - O.y), (double)(P[i].x - O.x));
//         A.push_back({ang, dist2(O,P[i]), P[i]});
//     }
//     stable_sort(A.begin(), A.end(), [](const Node& a, const Node& b){
//         if (a.ang != b.ang) return a.ang < b.ang;
//         if (a.r2  != b.r2 ) return a.r2  < b.r2; // 가까운 먼저
//         if (a.p.x != b.p.x) return a.p.x < b.p.x;
//         return a.p.y < b.p.y;
//     });
//
//     vector<Pt> stk;
//     stk.push_back(O);
//     for (auto &nd : A){
//         Pt p = nd.p;
//         // 외곽만 남기기: ccw <= 0 이면 pop
//         while (stk.size() >= 2){
//             Pt b = stk.back(), a = stk[stk.size()-2];
//             if (ccw(a,b,p) <= 0) stk.pop_back();
//             else break;
//         }
//         stk.push_back(p);
//     }
//     return stk;
// }
//
// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//
//     int N;
//     if(!(cin>>N)) return 0;
//     vector<Pt> P(N);
//     for (auto &p: P) cin >> p.x >> p.y;
//
//     // 볼록 껍질
//     vector<Pt> H = grahamHull(P);
//     int Hn = (int)H.size();
//
//     // 점이 1개면 0, 2개면 그 둘의 제곱거리
//     if (Hn == 1) { cout << 0 << "\n"; return 0; }
//
//     ull ans2 = 0;
//
//     if (Hn == 2){
//         ans2 = dist2(H[0], H[1]);
//         cout << ans2 << "\n";
//         return 0;
//     }
//
//     // Rotating Calipers (지름)
//     int j = 1;
//     // 초기 j 맞추기: 변 (Hn-1 -> 0)에 대해 area 증가 동안 j 전진
//     while (area2(H[Hn-1], H[0], H[(j+1)%Hn]) > area2(H[Hn-1], H[0], H[j])) j = (j+1) % Hn;
//
//     for (int i=0, ni=1; i<Hn; ++i, ni=(i+1)%Hn){
//         // i 고정, area 증가 동안 j 전진
//         while (area2(H[i], H[ni], H[(j+1)%Hn]) >= area2(H[i], H[ni], H[j]))
//             j = (j+1) % Hn;
//
//         // 거리 후보 갱신 (정점-정점)
//         ans2 = max(ans2, dist2(H[i],  H[j]));
//         ans2 = max(ans2, dist2(H[ni], H[j]));
//     }
//
//     cout << ans2 << "\n";
//     return 0;
// }
