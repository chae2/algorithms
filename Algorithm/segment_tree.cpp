//
// Created by chaei on 25. 4. 3.
//

#include "segment_tree.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;

const int sz=1<<20; // 2^20
int tree[sz*2];

void update(int idx, int val) {
    idx = idx-1+sz;     // leaf node
    tree[idx]=val;      // update a[idx] to value
    while (idx > 1) {
        idx /= 2;       // move upper
        tree[idx] = tree[idx*2]+tree[idx*2+1]; // recalculate parent
    }
}
int query(int l, int r) {
    l = l-1+sz;
    r = r-1+sz;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
	cout<<"hello!";

}


