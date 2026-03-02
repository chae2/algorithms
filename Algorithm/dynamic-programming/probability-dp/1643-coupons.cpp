#include <algorithm>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef long long ll;
using pii = pair<int,int>;
using ipii = pair<int,pii>;

ipii harmonic(int x) {
    // 1/1 + 1/2 + 1/3 +.. +1/n
    int big=0, q, r, least=1;
    vector<int> remainders(x+1, 0);
    vector<int> is;
    for (int i=1;i<=x;i++) {
        q = x/i;
        r = x%i;
        big+=q;
        remainders[i] = r;
        //is.push_back(i);
        if (r!=0) is.push_back(i);
    }
    for (int i : is) {
        least = lcm(least, i); // 최소공배수
    }
    int ans=0, numerator;
    for (int i=1;i<=x;i++) {
        numerator = least/i * remainders[i];
        ans += numerator;
    }
    // 기약분수 체크
    q=ans/least;
    r=ans%least;
    big+=q;
    int gcd_val = gcd(r,least);
    r /=gcd_val;
    least /=gcd_val;
    return {big, {r, least}};

}

void printSpaces(int cnt) {
    for (int i=0;i<cnt;i++) {
        cout<<' ';
    }
}

void printLines(int cnt) {
    for (int i=0;i<cnt;i++) {
        cout<<'-';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int x;

    while (cin>>x) {
        auto [q,p] = harmonic(x);
        auto [r, least] = p;
        if (!r) {
            cout<<q<<"\n";
        } else {
            int q_cnt = to_string(q).length();
            int r_cnt = to_string(r).length();
            int l_cnt = to_string(least).length();
            printSpaces(q_cnt+1); cout<<r<<"\n";
            cout<<q<<" "; printLines(max(r_cnt, l_cnt)); cout<<"\n";
            printSpaces(q_cnt+1); cout<<least<<"\n";
        }

    }
}