#include <deque>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;
using pii = pair<int,int>;
using pli = pair<ll, int>;

vector<pii> adjacent(int i,int j, int r, int h, const vector<vector<ll>>& weights) {
    int dx[] = {1,-1,0,0};
    int dy[] = {0,0,1,-1};
    vector<pii> res;
    for (int d=0; d<4; d++) {
        int ni = i+dx[d];
        int nj = j+dy[d];
        if (ni>=0 && ni<=r && nj>=0 && nj<=h && weights[ni][nj]>0) {
            res.push_back({ni,nj});
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin >> n>>m;
    vector<vector<ll>> weights(n, vector<ll>(m,0L));
    priority_queue<pli, vector<pli>, greater<>> pq; // 값, 행
    vector<pii> starts;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            cin>> weights[i][j];
            pq.push({weights[i][j], i});
        }
    }

    ll cnt = 0;
    while (!pq.empty()) {
        auto [w, r] = pq.top(); pq.pop();
        int idx = 0;
        for (ll a : weights[r]) {
            idx += 1;
            if (a==w) {
                break;
            }
        }
        int c = idx;
        while (true) {
            vector<pii> adj = adjacent(r,c,n,m, weights);
            if (adj.size()==0) break;
            for (auto [nx,ny] : adj) {
                if (weights[nx][ny]>0) {
                    weights[nx][ny] -= 1;
                    if (weights[r][c]>0) weights[r][c] -=1;
                    cnt += 1;
                }
            }
        }
    }
    cout<<cnt;
}