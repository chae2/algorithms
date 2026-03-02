#include <deque>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using ipii = pair<int,pii>;
int N,M, S,E;
int inf = 1<<30;
int max_c = 1e9;

bool dijkstra_01(int s, int e, int n, int load, const vector<vector<pii>>& adj) {
    vector d(n+1, inf);
    vector<vector<pii>> n_adj(n+1);
    for (int i=1;i<=n;i++) {
        for (auto [n,t] : adj[i]) {
            // stand보다 크면 버티기 가능; 4가 load
            n_adj[i].push_back({n, (t>=load) ? 1: inf});
        }
    }
    priority_queue<pii,vector<pii>,greater<>> pq;
    pq.push({d[s]=0, s});
    while (!pq.empty()) {
        auto [t,n] = pq.top(); pq.pop();
        if (t != d[n]) continue;
        for (auto [n_n, n_t] : n_adj[n]) {
            if (n_t==inf || d[n]==inf) continue;
            if (d[n_n] > d[n]+n_t) {
                pq.push({d[n_n] = d[n]+n_t, n_n});
            }
        }
    }
    return d[e] != inf;
}

int binary_search(int n, int s, int e, int max_c, const vector<vector<pii>>& adj) {
    int low=0, high=max_c;
    int ans=0;
    while (low>=0 && high<=max_c && low<=high) {
        int mid=(low+high)/2;
        if (dijkstra_01(s,e,n,mid,adj)) { // 큰 쪽 탐색
            low=mid+1;
            ans=mid;
        } else {
            high=mid-1;
        }
    }
    return ans;
}
/*
 * 2 3 4
 * mid=2, true니까 ans=mid, low=3, high=4
 * mid=3, true면 ans=mid, low=4, high=4
 * mid=4, true면 ans=mid, low=5, high=4; false면 high=3, low=4
 * 종료
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>N>>M;
    vector<vector<pii>> adj(N+1);
    for (int i=0; i<M; i++) {
        int a, b, l; cin>>a>>b>>l;
        adj[a].push_back({b,l});
        adj[b].push_back({a,l});
    }
    cin>>S>>E;
    cout<<binary_search(N,S,E,max_c,adj);

}