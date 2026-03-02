#include <deque>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using ipii = pair<int,pii>;
int inf = 1<<30;

bool dijkstra_01(int s, int n, int stand, int k, const vector<vector<pii>>& adj) {
    vector d(n+1, inf);
    vector<vector<pii>> n_adj(n+1);
    for (int i=1;i<=n;i++) {
        for (auto [n,t] : adj[i]) {
            n_adj[i].push_back({n, (t>stand) ? 1 : 0});
        }
    }
    priority_queue<pii,vector<pii>,greater<>> pq;
    pq.push({d[s]=0, s});
    while (!pq.empty()) {
        auto [t,n] = pq.top(); pq.pop();
        if (t != d[n]) continue;
        for (auto [n_n, n_t] : n_adj[n]) {
            if (d[n_n] > d[n]+n_t) {
                pq.push({d[n_n] = d[n]+n_t, n_n});
            }
        }
    }
    return d[n] <= k;
}

int binary_search(int s, int n, int k, int max_l, const vector<vector<pii>>& adj) {
    int low=0, high=max_l;
    int ans=0;
    while (low>=0 && high<=max_l && low<=high) {
        int mid=(low+high)/2;
        if (dijkstra_01(s,n,mid,k,adj)) { // 작은 쪽 탐색
            high=mid-1;
            ans=mid;
        } else {
            low=mid+1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p, k; cin>>n>>p>>k; // k : free, 1-n connection needed
    vector<vector<pii>> adj(n+1);
    int max_l = 0;
    for (int i=0; i<p; i++) {
        int a, b, l; cin>>a>>b>>l;
        adj[a].push_back({b,l});
        adj[b].push_back({a,l});
        if (l>max_l) max_l=l;
    }
    if (!dijkstra_01(1,n,max_l,k,adj)){ // 아예 되지 않는 케이스
        cout<<-1; return 0;
    }
    cout<<binary_search(1,n,k,max_l,adj);
}