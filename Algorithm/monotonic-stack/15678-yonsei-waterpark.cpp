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
ll inf=1<<30;

ll N, D;

ll step_stones(ll D, vector<ll>& stones) {
    deque<pll> dq; // idx val
    vector<pll> nge(stones.size(),{-1,inf}); // idx val: 현재 i의 nge 인덱스, 값
    ll window=D+1;
    for (int i=0;i<stones.size();i++) {
        while (!dq.empty() && dq.front().first<=i-window) {
            dq.pop_front();
        }
        while (!dq.empty() && dq.back().second<=stones[i]) {
            nge[dq.back().first] = {i,stones[i]};
            dq.pop_back();
        }
        dq.push_back({i,stones[i]});
    }

    int start=-1;
    for (int i=0;i<nge.size();i++) {
        if (stones[i]>0) {
            start=i;break;
        }
    }
    ll sum=0;
    if (start==-1) { // 전체 음수인 경우
        vector<ll> sort_stones = stones;
        sort(sort_stones.begin(), sort_stones.end(), greater<ll>()); // 내림차순
        sum=sort_stones[0];
    } else {
        sum += stones[start];
        int idx=0;
        for (int i=start;i<nge.size()&&nge[i].first!=-1;) {
            // cout<<"nge["<<i<<"]="<<nge[i].second<<endl;
            sum+=nge[i].second;
            i=nge[i].first;
        }
    }
    return sum;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>N>>D;
    vector<ll> stones(N);
    vector<ll> dp(N);
    for (int i=0;i<N;i++) cin>>stones[i];
    
}