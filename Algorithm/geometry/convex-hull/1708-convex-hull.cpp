#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using pdp = pair<double, pii>;
int N;
int inf = 1<<30;

struct Pt {ll x,y;};
struct Node {double ang; ll dist; Pt p;}; // dist는 거리

// AB와 AC의 벡터 외적
bool counter_clockwise(const Pt& a, const Pt& b, const Pt& c) {
    __int128 x1 = b.x-a.x, y1 = b.y-a.y;
    __int128 x2 = c.x-a.x, y2 = c.y-a.y;
    __int128 z = x1*y2 - y1*x2;
    return z>0; // 0인 경우(collinear)도 배제.
}

int grahamScan(const vector<Pt>& P) {
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
    return stk.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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
    // cout<<"standard: ("<<std.x<<", "<<std.y<<")\n";
    // cout<<"P[0]: ("<<P[0].x<<", "<<P[0].y<<")\n";
    swap(P[0],P[piv]);

    cout<<grahamScan(P);
}