#include <algorithm>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef long long ll;

int mex(const set<int>& s) {
    int m=0;
    for (int x : s) {
        if (x!= m) return m;
        m++;
    }
    return m;
}

vector<int> grundy(int M) {
    vector<int> g(M+1);
    g[0]=g[1]=0;

    for (int n=2;n<=M;n++) {
        set<int> s;
        for (int k=0;k<=(n-2-k);k++) {
            s.insert(g[k]^g[n-2-k]);
        }
        g[n] = mex(s);
    }

    return g;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, max=1000; cin>>n;

    vector<int> g(max+1);

    g = grundy(max);

    if (g[n]==0) cout<<"2\n";
    else cout<<"1\n";

}
