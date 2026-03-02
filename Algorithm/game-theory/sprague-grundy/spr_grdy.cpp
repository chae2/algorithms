#include <algorithm>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef long long ll;

int p[100];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, sum=0; cin>>n;
    for (int i=0;i<n;i++) {
        cin>>p[i]; sum^=p[i];
    }
    if (sum==0) cout<<"cubelover";
    else cout<<"koosaga";

}