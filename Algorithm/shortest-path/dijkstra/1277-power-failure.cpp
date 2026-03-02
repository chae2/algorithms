#include <deque>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
using pid = pair<int,double>;
using pdi = pair<double,int>;
int inf = 1<<30;

double calculate_weight(int a, int b, const vector<pii>& nodes) {
    int dx = nodes[a].first - nodes[b].first;
    int dy = nodes[a].second - nodes[b].second;
    return sqrt(pow(dx,2)+pow(dy,2));
}

double dijkstra(int n, const vector<vector<pid>>& wires) {
    vector<double> d(n+1, inf);
    d[1]=0;
    priority_queue<pdi, vector<pdi>, greater<>> pq; // w, n
    pq.push({0,1});
    while (!pq.empty()) {
        auto [w, n] = pq.top(); pq.pop();
        if (w!=d[n]) continue;
        for (auto [n_n, n_w] :wires[n]) {
            // cout<<"when n: "<<n<<", w: "<<w<<"\n";
            if (d[n_n]>n_w+d[n]) {
                // cout<<"     update: "<<d[n]+n_w<<"\n";
                pq.push({d[n_n]=n_w+d[n], n_n});
            }
        }
    }
    return d[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,w; double m;
    cin>>n>>w>>m;

    vector<pii> nodes(n+1,{0,0});
    vector wires(n+1, vector<pid>());
    for (int i=1;i<=n;i++) {
        int x,y; cin>>x>>y;
        nodes[i] = {x,y};
    }
    for (int i=0;i<w;i++) {
        int p1, p2; cin>>p1>>p2;
        wires[p1].push_back({p2,0});
        wires[p2].push_back({p1,0});
    }
    for (int i=1;i<=n;i++) {
        for (int j=i+1; j<=n;j++) {
            double w = calculate_weight(i,j,nodes);
            // cout<<"i: "<<i<<", j: "<<j<<", w: "<<w<<"\n";
            if (w<=m) {
                wires[i].push_back({j,w});
                wires[j].push_back({i,w});
            }
        }
    }
    // for (int i=1;i<=n;i++) {
    //     cout<<"i: "<<i<<"\n";
    //     for (auto [n,w] : wires[i]) {
    //         cout<<"        n: "<<n<<", w: "<<w<<"\n";
    //     }
    // }

    double ans = dijkstra(n, wires);
    if (ans==inf) {
        cout<<-1; return 0;
    }
    cout<<int(ans*1000); return 0;
}
