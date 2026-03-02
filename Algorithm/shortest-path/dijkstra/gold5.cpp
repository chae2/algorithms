#include <deque>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using piii = pair<int, pii>;
int inf = 1<<30;

int N, S=0;

vector<pii> adjacent(int i, int j) {
    vector<pii> res;
    pii ways[4] = {{i+1,j},{i-1,j},{i,j+1},{i,j-1}};
    for (auto [x,y] : ways) {
        if (x>=0 && x<N && y>=0 && y<N) {
            res.push_back({x,y});
        }
    }
    return res;
}

int dijkstra(int size, const vector<vector<int>>& cave) {
    vector d(size, vector (size, inf)); // s에서 인덱스까지의 거리
    priority_queue<piii,vector<piii>,greater<>> pq;
    pq.push({d[S][S]=cave[S][S],{S,S}});
    while (pq.size()) {
        auto [rupee, vil] = pq.top(); pq.pop();
        auto [vil_x, vil_y] = vil;
        if (d[vil_x][vil_y] != rupee) continue;
        for (auto n_vil : adjacent(vil_x,vil_y)) {
            auto [n_vil_x, n_vil_y] = n_vil;
            if (d[n_vil_x][n_vil_y] > d[vil_x][vil_y]+cave[n_vil_x][n_vil_y]) {
                d[n_vil_x][n_vil_y] = d[vil_x][vil_y]+cave[n_vil_x][n_vil_y];
                pq.push({d[n_vil_x][n_vil_y], n_vil});
            }
        }
    }
    return d[size-1][size-1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cnt=0;
    cin>>N;
    while (N!=0) {
        vector rupee_cave(N, vector<int> (N));
        for (int i=0;i<N;i++) {
            for (int j=0;j<N;j++) {
                cin>>rupee_cave[i][j];
            }
        }
        cout<<"Problem "<<++cnt<<": "<<dijkstra(N, rupee_cave)<<"\n";

        cin>>N;
    }
}
