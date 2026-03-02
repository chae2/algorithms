#include <deque>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using piii = pair<int, pii>;
int inf = 1<<30;

int N,M, T,D; // T: 높이 차, D: 어두워지는 시간

vector<piii> adjacent(int i, int j, const vector<vector<int>>& heights) {
    vector<piii> res;
    int now = heights[i][j];
    pii ways[4] = {{i+1,j},{i-1,j},{i,j+1},{i,j-1}};
    for (auto [x,y] : ways) {
        if (x>=0 && x<N && y>=0 && y<M) {
            int delta = heights[x][y] - now;
            if (abs(delta) > T) continue;
            res.push_back({delta, {x,y}});
        }
    }
    return res;
}

vector<vector<int>> dijkstra(int s_x, int s_y, vector<vector<int>>& heights) {
    vector d(N, vector (M, inf)); // s에서 인덱스까지의 거리
    priority_queue<piii,vector<piii>,greater<>> pq;
    pq.push({d[s_x][s_y]=0,{s_x,s_y}});

    while (pq.size()) {
        auto [vil_cost, vil] = pq.top(); pq.pop();
        auto [vil_x, vil_y] = vil;
        if (d[vil_x][vil_y] != vil_cost) continue;
        for (auto [delta, n_vil] : adjacent(vil_x, vil_y, heights)) {
            auto [n_vil_x, n_vil_y] = n_vil;
            int cost;
            if (delta > 0) cost = delta*delta;
            else cost = 1;
            if (d[n_vil_x][n_vil_y] > vil_cost+cost) {
                d[n_vil_x][n_vil_y] = vil_cost+cost;
                pq.push({d[n_vil_x][n_vil_y], {n_vil_x,n_vil_y}});
            }
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>N>>M>>T>>D;
    vector heights(N,vector<int> (M));
    for (int i=0;i<N;i++) {
        for (int j=0;j<M;j++) {
            char c; cin>>c;
            if (std::isupper(c)) heights[i][j] = c-'A';
            else heights[i][j] = c-'a'+26;
            // cout<< heights[i][j]<<" ";
        }
        // cout<< "\n";
    }
    vector<vector<int>> d = dijkstra(0,0, heights);
    priority_queue<piii, vector<piii>, less<>> biggest;
    for (int i=0;i<N;i++) {
        for (int j=0;j<M;j++) {
            if (d[i][j]!=inf) biggest.push({heights[i][j],{i,j}});
        }
    }
    while (!biggest.empty()) {
        auto [cost, n] = biggest.top(); biggest.pop();
        auto [n_x, n_y] = n;
        if (d[n_x][n_y] + dijkstra(n_x,n_y, heights)[0][0] <= D) {
            cout<<heights[n_x][n_y]; return 0;
        }
    }

}
