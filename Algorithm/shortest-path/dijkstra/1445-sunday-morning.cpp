#include <deque>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using piii = pair<pair<int,int>,int>;
using pp = pair<pii,pii>;
using pid = pair<int,double>;
int inf = 1<<30;

pii operator+(const pii& a, const pii& b) {
    return {a.first+b.first, a.second+b.second};
}

vector<pii> adjacent(int i, int j, int n, int m) {
    vector<pii> res;
    pii ways[4] = {{i+1,j},{i-1,j},{i,j+1},{i,j-1}};
    for (auto [x,y] : ways) {
        if (x>=0 && x<n && y>=0 && y<m) {
            res.push_back({x,y});
        }
    }
    return res;
}

void calculate_g(int i, int j, int n, int m, vector<vector<pii>>& g, vector<string>& map){
    g[i][j] = {1,0};
    pii ways[4] = {{i+1,j},{i-1,j},{i,j+1},{i,j-1}};
    for (auto [x,y] : ways) {
        if (x>=0 && x<n && y>=0 && y<m && map[x][y]=='.') {
            g[x][y] = {0,1}; // map[x][y]=='g'인 경우에는 덮어씌워졌던 것!
        }
    }
}

pii dijkstra(pii s, pii end, int n, int m, const vector<vector<pii>>& garbages) {
    vector d(n, vector<pii> (m,{inf,inf}));
    d[s.first][s.second]={0,0};
    priority_queue<pp, vector<pp>, greater<>> pq; // w1, w2, x, y
    pq.push({d[s.first][s.second],{s.first,s.second}});
    while (!pq.empty()) {
        auto [w, node] = pq.top(); pq.pop();
        if (w!=d[node.first][node.second]) continue;
        for (auto [x, y] :adjacent(node.first,node.second,n,m)) {
            if (d[x][y]>garbages[x][y]+d[node.first][node.second]) {
                pq.push({d[x][y]=garbages[x][y]+d[node.first][node.second], {x,y}});
            }
        }
    }
    return d[end.first][end.second];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; cin>>n>>m;
    cin.ignore();
    vector garbages(n, vector<pii>(m,{0,0}));
    vector<string> map(n);
    pii s, end;
    for (int i=0;i<n;i++) {
        getline(cin,map[i]);
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            switch (map[i][j]) {
                case 'g':
                    calculate_g(i,j,n,m,garbages, map);
                break;
                case 'F':
                    end = {i,j};
                break;
                case 'S':
                    s = {i,j};
                break;
            }
        }
    }
    pii G = dijkstra(s,end,n,m,garbages);
    cout<<G.first<<" "<<G.second;
    // pair 연산 test
    // pii p1 = {1,0};
    // pii p2 = {2,3};
    // pii sum = p1+p2;
    // cout << "(" << sum.first << ", " << sum.second << ")\n";
}