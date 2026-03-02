#include <algorithm>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>
#include <sstream>
using namespace std;
typedef long long ll;

int idx_change(int real) {
    return real/2+1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int num; cin >>num;
    vector<int> s(num); for (int i=0;i<num;i++) cin>>s[i];

    // 1. 문자 사이 특수 문자 삽입 (홀수화)
    vector<int> s_; s_.push_back(-1);
    for (int i=0;i<num;i++) {
        s_.push_back(s[i]);
        s_.push_back(-1);
    }
    int sz=s_.size();
    vector p(sz,0);
    int center=0, right=0;

    // 2. 펠린드롬 반경 계산하기
    for (int i=0;i<sz;i++) {
        int mirror=2*center-i;
        if (i<=right) {
            p[i]=min(p[mirror],right-i); // 초기화
        }

        while (i+p[i]+1<sz && i-p[i]-1>=0 && s_[i+p[i]+1]==s_[i-p[i]-1]) {
            p[i]++; // 초기화 상관없이 확장
        }
        if (p[i]+i>right) { // 맨 오른쪽에 있는 펠린드롬이 된다면 center, right 업데이트
            center=i; right=i+p[i];
        }
    }

    // 3. 구간이 팰린드롬인지 확인
    cin>>num;
    while (num--) {
        int i,j; cin>>i>>j; // i 문자부터 j 문자까지 팰린드롬인지 확인
        int l = 2*i-1, r = 2*j-1;
        int mid = (l+r)/2, len = r-l+1;
        if (p[mid] >= len/2) {
            // cout<<mid<<": "<<p[mid]<<"\n";
            cout<<"1\n";
        } else {
            cout<<"0\n";
        }
    }

}