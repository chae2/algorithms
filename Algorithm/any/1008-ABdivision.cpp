#include <iomanip>
#include <iostream>
#include <queue>
#include <string>

using namespace std;
struct MM {string tor; string ti;};

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin>>N;
    auto cmp = [&](const MM& M1, const MM& M2) {
        if (M1.tor != M2.tor) return M1.tor > M2.tor;
        if (M2.ti != M2.ti) return M1.ti < M2.ti;
        return M1.ti < M2.ti;
    };

    priority_queue<MM, vector<MM>, decltype(cmp)> pq(cmp);
    while (N--) {
        MM men; cin>>men.tor>>men.ti;
        pq.push(men);
    }
    while (!pq.empty()) {
        MM m = pq.top(); pq.pop();
        cout<<m.tor<<" "<<m.ti<<"\n";
    }
}