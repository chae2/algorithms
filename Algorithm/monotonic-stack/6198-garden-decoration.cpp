#include <deque>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
typedef long long ll;
using pii = pair<int,int>;

// vector 마지막 원소 제거: pop_back()
// 마지막 원소: back()

int n;

ll small_cnter(vector<int>& heights) {
    vector<pii> cnts; // idx, heights
    ll ans = 0;

    for (int i=0; i<heights.size(); i++) {
        // 처음으로 더 큰 애를 마주쳤을 때
        while (!cnts.empty() && cnts.back().second<=heights[i]) { // decreasing monotonic
            ans += abs(cnts.back().first-i)-1;
            cnts.pop_back();
        }
        cnts.push_back({i,heights[i]});
    }
    // cout<<"n: "<<n<<"\n";
    while (!cnts.empty()) {
        // cout<<"leftover: "<<cnts.back().second<<" with "<<n-cnts.back().first-1<<" \n";
        ans += n-cnts.back().first-1;
        cnts.pop_back();
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    vector<int> heights(n);
    for (int i=0;i<n;i++) {
        cin>>heights[i];
    }
    cout<<small_cnter(heights);
}