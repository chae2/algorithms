#include <algorithm>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>
#include <sstream>
using namespace std;
typedef long long ll;
using pii = pair<int,int>;
using pic = pair<int,char>;
using pcc = pair<char, char>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; string s, c, T, M;
    cin>>n>>s>>c>>T;
    vector<pcc> D;
    for (int i=0;i<n;i++) {
        D.push_back({s[i],c[i]});
    }
    priority_queue<pic> pq;

    pq.push({});

}