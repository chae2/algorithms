#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef double dd;
using pdi = pair<dd, int>;
using pii = pair<int, int>;
int inf = 1<<30;

int N,S=0,F;
static constexpr int D=2;

// 좌표 -> 키 변환 함수
auto key_of = [](int x,int y) {
    return ((ll)(unsigned int)x <<32) | (unsigned int)y;
};

void dijkstra(int size, unordered_map<ll,vector<int>>& bucket, const vector<pii>& coord, const dd W[5][5]) {
    vector<dd> d(size+1, inf); // s에서 인덱스까지의 거리
    priority_queue<pdi,vector<pdi>,greater<>> pq;
    pq.push({d[S]=0.0,S}); // coord 번호
    while (pq.size()) {
        auto [dist, nod] = pq.top(); pq.pop();

        if (d[nod] != dist) continue;
        if (coord[nod].second == F) {
            cout<<round(dist); return;
        }
        auto [x,y] = coord[nod];
        for (int dx=-D; dx<=D; dx++) {
            for (int dy=-D; dy<=D; dy++) {
                if (dx==0 && dy==0) continue;
                auto it = bucket.find(key_of(x+dx, y+dy));
                if (it==bucket.end()) continue; // ??
                dd cost = W[dx+D][dy+D];
                for (int n_nod: it->second) {
                    if (d[n_nod]>d[nod]+cost) pq.push({d[n_nod]=d[nod]+cost, n_nod});
                }
            }
        }
    }
    cout<<-1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>N>>F;
    vector<pii> coord(N+1); // x y coordinates
    vector<int> fin;
    coord[0].first=0, coord[0].second=0;

    unordered_map<ll, vector<int>> coord_bucket;
    coord_bucket.reserve(N*2);

    for (int i=1; i<=N; i++) {
        int x,y; cin>>x>>y; coord[i] = {x,y};
        if (y==F) fin.push_back(i);
        coord_bucket[key_of(x,y)].push_back(i);
    }

    static dd W[5][5];
    for (int dx=-D; dx<=D; dx++) {
        for (int dy=-D; dy<=D; dy++) {
            W[dx+D][dy+D] = hypot(dx,dy);
        }
    }
    dijkstra(N,coord_bucket,coord,W);

}
