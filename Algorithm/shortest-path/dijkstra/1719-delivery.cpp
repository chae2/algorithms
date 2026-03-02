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
    vector<int> pre(size+1); // 최단경로 시 가장 처음에 마주하게 되는 노드
    priority_queue<pii,vector<pii>,greater<>> pq;
    pq.push({d[s]=0,s});
    while (pq.size()) {
        auto [time, vil] = pq.top(); pq.pop();
        if (d[vil] != time) continue;
        for (auto [n_vil, n_time] : adj[vil]) {
            if (d[n_vil] > d[vil]+n_time) {
                d[n_vil] = d[vil]+n_time;
                pq.push({d[n_vil], n_vil});
                if (vil==s) pre[n_vil] = n_vil;
                else pre[n_vil] = pre[vil];
            }
        }
    }
    return pre;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; cin>>n>>m;
    vector<vector<pii>> adj(n+1);
    for (int i=0;i<m;i++) {
        int x,y,w; cin>>x>>y>>w;
        adj[x].push_back({y,w}); adj[y].push_back({x,w});
    }
    for (int i=1;i<n+1;i++) {
        vector pre = dijkstra(i,n,adj);
        for (int j=1; j<n+1; j++) {
            if (j==i) cout<<"-";
            else cout<<pre[j];
            if (j!=n) cout<<" ";
        }
        cout<<"\n";
    }

}