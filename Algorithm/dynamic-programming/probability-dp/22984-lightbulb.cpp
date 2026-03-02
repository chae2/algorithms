#include <algorithm>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>
#include <sstream>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    double res, p_sum=0, x_sum=0;
    cin>>n;
    vector<double> p(n+1,0);
    for (int i=1;i<=n;i++) {
        cin>>p[i];
        p_sum += p[i];
        x_sum += p[i]*p[i-1];
    }
    cout.precision(10);
    res = 3*p_sum-(p[1]+p[n])-2*x_sum;
    cout<<fixed<<res;
}