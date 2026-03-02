#include <deque>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;
using scc_result = pair<int, vector<vector<int>>>;

int V,E;

void dfs(int node, vector<int> &vis, vector<int> adj[], stack<int> &stk) {
    vis[node]=1;
    for (auto it:adj[node]) {
        if (!vis[it]) {
            dfs(it, vis, adj, stk);
        }
    }
    stk.push(node);
}

void dfs_2(int node, vector<int> &vis, vector<int> adj_t[], vector<int> &scc) {
    vis[node]=1;
    scc.push_back(node);

    for (auto it:adj_t[node]) {
        if (!vis[it]) {
            dfs_2(it, vis, adj_t, scc);
        }
    }
}

scc_result kosaraju(int V, vector<int> adj[]) {
    vector<int> vis(V+1, 0);
    stack<int> stk;
    for (int i=1;i<=V;i++) {
        if (!vis[i]) {
            dfs(i,vis,adj,stk);
        }
    }
    // transpose graph
    vector<int> adj_t[V+1];
    for (int i=1;i<=V;i++) {
        vis[i]=0;
        for (auto it: adj[i]) {
            // i->it를 it->i로 바꾸기
            adj_t[it].push_back(i);
        }
    }
    vector<vector<int>> all_sccs;
    int cnt=0;
    while (!stk.empty()) {
        int node = stk.top(); stk.pop();
        if (!vis[node]) {
            cnt++;
            vector<int> current_scc;
            dfs_2(node, vis, adj_t, current_scc);
            sort(current_scc.begin(), current_scc.end());
            all_sccs.push_back(current_scc);
        }
    }
    sort(all_sccs.begin(), all_sccs.end(), [](const vector<int>&a, vector<int>&b) {
        return a[0]<b[0];
    });
    return {cnt, all_sccs};
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>V>>E;
    vector<int> adj[V+1];
    for (int i=0;i<E;i++) {
        int x,y; cin>>x>>y;
        adj[x].push_back(y);
    }
    auto [cnt, all_sccs] = kosaraju(V, adj);
    cout<<cnt<<"\n";
    for (const auto& scc : all_sccs) {
        for (int c : scc) cout<<c<<" ";
        cout<<"-1\n";
    }
}