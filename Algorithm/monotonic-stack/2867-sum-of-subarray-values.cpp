#include <deque>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;
using pii = pair<int,int>;

int N;

ll sum_of_monotonic_stack(bool is_max, int N, vector<ll>& seq) {
    ll sum =0;
    vector<pll> subarray(N, {-1,N}); // L,R 정보
    stack<pll> stk; // idx, value
    for (int i=0;i<N;i++) {
        // 최댓값 구하는 경우 감소스택
        if (is_max) {
            while (!stk.empty() && stk.top().second<=seq[i]) {
                subarray[stk.top().first].second = i; // 작은 쪽의 R 기록
                stk.pop();
            }
        } else {
            // 최솟값 구하는 경우 증가스택
            while (!stk.empty() && stk.top().second>=seq[i]) {
                subarray[stk.top().first].second = i; // 큰 쪽의 R 기록
                stk.pop();
            }
        }
        if (!stk.empty()) subarray[i].first = stk.top().first; // L 기록
        stk.push({i, seq[i]});
    }

    for (int i=0;i<N;i++) {
        ll L = subarray[i].first, R = subarray[i].second;
        sum += seq[i]*(ll)(i-L)*(ll)(R-i);
    }
    return sum;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>N;
    vector<ll> seq(N);
    for (int i=0;i<N;i++) cin>>seq[i];
    cout<<sum_of_monotonic_stack(true,N,seq)-sum_of_monotonic_stack(false,N,seq);
}