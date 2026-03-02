#include <deque>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;
using pii = pair<int,int>;
ll inf = 1<<30;

int N,K;

ll max_min_diff(int N, int K, vector<int>& V) {
    deque<pii> dq; // idx, val
    vector<ll> terms(N-1);
    priority_queue<ll, vector<ll>, greater<>> m_plus_M;
    int window = N-K-1;

    for (int i=1;i<N;i++) {
        terms[i-1] = V[i]-V[i-1];
    }

    // N-K-1 슬라이딩
    for (int i=0;i<N-1;i++) {
        while (!dq.empty() && dq.front().first <= i-window) {
            dq.pop_front();
        }
        // 극소.
        while (!dq.empty() && dq.back().second >= terms[i]) {
            dq.pop_back();
        }

        dq.push_back({i,terms[i]});
        if (i>=window-1) {
            ll M = (ll)V[i+1]-V[i-window+1];
            ll m = dq.front().second;
            m_plus_M.push(M+m);
        }
    }
    return m_plus_M.top();
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>N>>K;
    vector<int> V(N);
    for (int i=0;i<N;i++) cin>>V[i];
    sort(V.begin(), V.end());
    cout<<max_min_diff(N, K, V);
}