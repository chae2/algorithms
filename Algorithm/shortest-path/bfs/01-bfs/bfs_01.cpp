#include <iostream>
#include <deque>
#include <limits>
#include <sstream>
#include <vector>
using namespace std;

using pii=pair<int,int>;
using piii=pair<pii,pii>;
const int INF = numeric_limits<int>::max();

vector<pii> adjacent(int i,int j, int iend, int jend) {
    int dx[] = {1,-1,0,0};
    int dy[] = {0,0,1,-1};
    vector<pii> res;
    for (int d=0; d<4; d++) {
        int ni = i+dx[d];
        int nj = j+dy[d];
        if (ni>=1 && ni<=iend && nj>=1 && nj<=jend) {
            res.push_back({ni,nj});
        }
    }
    return res;
}

// 0-1 bfs
void bfs_01(int h, int w, const pii& start, const vector<vector<int>>& rooms, vector<vector<int>>& dist) {
    deque<pii> dq;
    dq.push_front(start);
    dist[start.first][start.second] = 0;
    while (!dq.empty()) {
        auto [x,y] = dq.front(); dq.pop_front();

        for (auto [nx,ny] : adjacent(x,y,h,w)) {
            int cost = rooms[nx][ny];
            if (cost == INF) continue;
            if (dist[x][y]+cost < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y]+cost;
                if (cost == 0) dq.push_front({nx,ny});
                else dq.push_back({nx,ny});
            }
        }
    }
}

int main(){
    int m,n; cin>>m>>n; // 열 행
    vector dist(n+1, vector (m+1, INF));
    vector rooms(n+1, vector<int> (m+1));
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            char c; cin>>c;
            rooms[i][j] = c-'0';
        }
    }
    bfs_01(n,m,{1,1},rooms,dist);
    cout<<dist[n][m];
 }
