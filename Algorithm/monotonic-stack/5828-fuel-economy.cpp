#include <deque>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;

ll N,G,B,D;
ll inf=1<<30;

ll monotonic_fuel_cost(ll window, ll start_fuel, ll dest, vector<pll>& stations) {
    ll curr_fuel = start_fuel;
    deque<pll> mq;
    mq.push_back({0,inf});
    ll total_cost=0;

    for (int i=1;i<stations.size();i++) {
        // 종료 조건
        if (stations[i].first==dest) return total_cost;
        // 연료 소모
        curr_fuel -= stations[i].first-stations[i-1].first;
        if (curr_fuel < 0) return -1;

        // 큐 관리
        while (!mq.empty() && mq.back().second>=stations[i].second) {
            mq.pop_back();
        }
        while (!mq.empty() && mq.front().first<i-window) mq.pop_front();
        mq.push_back(stations[i]);

        // 주유
        ll curr_pos=stations[i].first, next_pos=stations[i+1].first;
        if (next_pos-curr_pos > curr_fuel) {
            ll fuel_needed_for_future = 0;
            while (!mq.empty() && next_pos>mq.front().first+window) {
                ll available_pos = mq.front().first+window;
                ll fuel_needed = available_pos-curr_pos;
                if (fuel_needed<0) {
                    mq.pop_front(); continue;
                }
                ll fuel_to_buy = fuel_needed-curr_fuel;
                ll price = mq.front().second;

                total_cost += fuel_to_buy*price;
                fuel_needed_for_future += fuel_to_buy;

                curr_pos=available_pos;
                mq.pop_front();
            }
            if (mq.empty()) return -1; // 밖에서도 처리해야 할 듯
            if (next_pos > curr_pos) {
                ll fuel_needed = next_pos-curr_pos;
                ll fuel_to_buy = fuel_needed-curr_fuel;
                ll price = mq.front().second;

                total_cost += fuel_to_buy*price;
                fuel_needed_for_future += fuel_to_buy;
            }
            curr_fuel += fuel_needed_for_future;
        }
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>N>>G>>B>>D;
    vector<pll> stations;
    stations.push_back({0,inf});

    for (int i=0; i<N;i++) {
        pll a; cin>>a.first>>a.second;
        stations.push_back(a);
    }
    stations.push_back({D,0});
    sort(stations.begin(), stations.end());
    cout<<monotonic_fuel_cost(G, B, D, stations);
}