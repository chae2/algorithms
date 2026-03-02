#include <deque>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using ipii = pair<int, pii>; // [거리], [시작-도착지]
int inf = 1<<30;

int N, A, B;

int dijkstra(int size, int A, int B, const vector<vector<int>>& rails) {
    vector d(size+1, inf); // s에서 인덱스까지의 거리
    priority_queue<pii,vector<pii>,greater<>> pq;
    pq.push({d[A]=0,A});
    while (pq.size()) {
        auto [sch, now] = pq.top(); pq.pop();
        if (d[now] != sch) continue;
        int i=0;
        for (int next : rails[now]) {
            if (d[next] > d[now] + i) {
                d[next] = d[now] + i;
                pq.push({d[next], next});
            }
            i=1;
        }

        // int i=0;
        // for (auto next : rails[now]) {
        //     if (d[next]>d[now]+i) {
        //         pq.push({d[next]=d[now]+i,next});
        //         i=1;
        //     }
        // }
    }
    return d[B]==inf ? -1 : d[B];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    // N개 간선
    cin>>N>>A>>B; // A -> B까지 최소.
    vector<vector<int>> rails(N+1); // i번째 -> 도착 번째
    for (int i=1;i<=N;i++) {
        int T;
        cin>>T; while (T--) {
            int X; cin>>X; rails[i].push_back(X);
        }
    }
    cout<<dijkstra(N,A,B,rails);
}