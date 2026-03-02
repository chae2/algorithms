#include <algorithm>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>
#include <sstream>
using namespace std;
typedef long long ll;

vector<int> make_lps_table(const string& pattern) {
    vector pi(pattern.length(),0);
    int idx=1, len=0;
    while (idx<pattern.length()) {
        if (pattern[idx]==pattern[len]) {
            len+=1; pi[idx++]=len;
        }else {
            if (len!=0) //
            else {

            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

}
