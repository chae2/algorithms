#include <deque>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
int inf = 1<<30;

vector<int> dijkstra(int s, int size, const vector<vector<pii>>& adj) {
    vector<int> d(size+1, inf); // s에서 인덱스까지의 거리
    priority_queue<pii,vector<pii>,greater<>> pq;
    pq.push({d[s]=0,s});
    while (pq.size()) {
        auto [time, vil] = pq.top(); pq.pop();
        if (d[vil] != time) continue;
        for (auto [n_vil, n_time] : adj[vil]) {
            if (d[n_vil] > d[vil]+n_time) {
                d[n_vil] = d[vil]+n_time;
                pq.push({d[n_vil], n_vil});
            }
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, x; cin>>n>>m>>x;
    vector<vector<pii>> adj(n+1);
    for (int i=0; i<m; i++) {
        int x, y, t; cin>>x>>y>>t;
        adj[x].push_back({y,t});
    }
    int longest = 0;

    vector d_x = dijkstra(x, n+1, adj);
    for (int i=1;i<n+1;i++) {
        if (i==x) continue;
        vector d = dijkstra(i, n, adj);
        if (d[x]+d_x[i] > longest) longest = d[x]+d_x[i];
    }
    cout<<longest;

}