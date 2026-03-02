#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <valarray>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using ipii = pair<int, pii>;
constexpr int inf = 1e9;

vector<ipii> adjacent_road(int r_loc, int c_loc, int r, int c, int time, const vector<string>& map, const vector<ipii>& rules) {
    /* 4방위
     * # - 비용 1
     * int - 비용은 현재비용에 따라 달라짐.
     * . - 비용 inf
     */
    const ipii planes[4] = {{1,{r_loc+1,c_loc}},{1,{r_loc-1,c_loc}},
                                {0,{r_loc,c_loc+1}}, {0,{r_loc, c_loc-1}}};
    vector<ipii> adj;
    for (auto [d,pos]: planes) { // 방향(0: -, 1: |), 좌표
        auto [a,b] = pos;
        if (a>=r || a<0 || b>=c || b<0 || map[a][b] == '.') continue;
        if (map[a][b] == '#' || map[a][b]=='B' || map[a][b]=='A') {
            adj.push_back({1,pos});
        } else if (isdigit(map[a][b])) {
            int id = map[a][b]-'0';
            auto [dir_idx, dir] = rules[id]; // 동서, 남북 방향
            auto [w1,w2] = dir;

            int cycle = w1+w2;
            int x = (time) % cycle;
            // if (!x && !time) {x=cycle;}
            int curr, cost;
            if (dir_idx == 0) {
                curr = (x<w1) ? 0 : 1;
                cost = (curr==d) ? 1 : w1+1-x+w2*curr;
            } else {
                curr = (x<w1) ? 1 : 0;
                cost = (curr==d) ? 1 : w1+1-x+w2*(1-curr);
            }
            adj.push_back({cost,pos});
        }
    }
    return adj;

}

vector<vector<int>> dijkstra(pii s, int r, int c,
                            const vector<string>& map,
                            const vector<ipii>& rules) {
    vector<vector<int>> d(r, vector<int>(c,inf)); // s에서 인덱스까지의 거리
    priority_queue<ipii,vector<ipii>,greater<>> pq; // pii 시간, 위치<pii>
    pq.push({d[s.first][s.second]=0,s});
    while (!pq.empty()) {
        auto [time, loc] = pq.top(); pq.pop();
        auto [p_r,p_c] = loc; // 현재 위치
        if (d[p_r][p_c] != time) continue;

        for (auto [n_time, n_loc] : adjacent_road(p_r, p_c, r, c, time, map, rules)) {
            auto [n_r, n_c] = n_loc;
            if (d[n_r][n_c] > d[p_r][p_c]+n_time) {
                d[n_r][n_c] = d[p_r][p_c]+n_time;
                pq.push({d[n_r][n_c], n_loc});
            }
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r,c;
    pii start, end;

    while (true) {
        cin>>r>>c;
        vector<string> map(r);
        vector<ipii> rules(10);
        int biggest=-1;
        if (r==0&&c==0) break;
        for (int i=0;i<r;i++) {
            cin>>map[i];
            int idx=0;
            for (char h : map[i]) {
                int h_i = h-'0';
                if (isdigit(h) && h_i>biggest) {
                    biggest = h_i;
                } else if (h=='A') {
                    start = {i, idx};
                } else if (h=='B') {
                    end = {i,idx};
                }
                idx++;
            }
        }
        cin>>ws;
        if (biggest >= 0) {
            for (int i=0;i<=biggest; i++) {
                int idx, a,b;
                char dir;
                cin>>idx>>dir>>a>>b;
                if (dir == '-') {
                    rules[idx] = {0,{a,b}};
                } else {
                    rules[idx] = {1,{b,a}};
                }
            }
        }
        vector dkstra = dijkstra(start, r, c, map, rules);
        auto [a,b] = end;
        if (dkstra[a][b] != inf) {
            cout<<dkstra[a][b]<<"\n";
        } else {
            cout<<"impossible\n";
        }
    }
    return 0;
}