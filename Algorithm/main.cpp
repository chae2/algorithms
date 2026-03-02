#include <algorithm>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// void build(int idx, int low, int high, vector<int>& seg, vector<int>& a) {
//     if (low==high) {
//         seg[idx]=a[low]; return;
//     }
//     int mid = (low+high)/2;
//     build(2*idx+1,low,mid,seg,a);
//     build(2*idx+2,mid+1,high,seg,a);
//     seg[idx]=seg[2*idx+1]+seg[2*idx+2];
// }
//
// int query(int idx, int low, int high, int l, int r, vector<int>& seg) {
//     if (low>=l && high<=r) {
//         return seg[idx];
//     }
//     if (high<l || low>r) return 0;
//     int mid = (low+high)/2;
//     int left = query(2*idx+1,low,mid,l,r,seg);
//     int right = query(2*idx+2,mid+1,high,l,r,seg);
//     return left+right;
// }
//
// void rangeUpdate(int idx, int low, int high, int l, int r, int val, vector<int>& seg, vector<int>& lazy) {
//     if (lazy[idx]!=0) {
//         seg[idx] += (high-low+1)*lazy[idx];
//         if (low!=high) {
//             lazy[2*idx+1]+=lazy[idx];
//             lazy[2*idx+2]+=lazy[idx];
//         }
//         lazy[idx]=0;
//     }
//
//     if (high<l || low>r || low>high) return;
//     if (low>=l && high<=r) {
//         seg[idx] += (high-low+1)*val;
//         if (low!=high) {
//             lazy[2*idx+1] += lazy[idx];
//             lazy[2*idx+2] += lazy[idx];
//         }
//         return;
//     }
//
//     int mid = (low+high)/2;
//     rangeUpdate(2*idx+1,low,mid,l,r,val,seg,lazy);
//     rangeUpdate(2*idx+2,mid+1,high,l,r,val,seg,lazy);
//     seg[idx]=seg[2*idx+1]+seg[2*idx+2];
// }
//
// void pointUpdate(int idx, int low, int high, int p, int val, vector<int>& seg) {
//     if (low==high) {
//         seg[idx] += val;
//     } else {
//         int mid = (low+high)/2;
//         if (p>=low && p<=mid) pointUpdate(2*idx+1,low,mid,p,val,seg);
//         else pointUpdate(2*idx+2, mid+1, high, p, val, seg);
//         seg[idx] = seg[2*idx+1]+seg[2*idx+2];
//     }
// }
//
// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     int n,m; cin>>n>>m;
//     vector<int> seg(4*(n*n+1)), flat(n*n+1), lazy(4*(n*n+1),0);
//     // vector a(n,vector<int>(n));
//     for (int i=1;i<=n;i++) {
//         for (int j=1;j<=n;j++) {
//             // cin>>a[i][j];
//             cin>>flat[(i-1)*n+j];
//         }
//     }
//     build(0,1,n*n,seg,flat);
//     for (int i=1;i<=m;i++) {
//         int w; cin>>w;
//         if (w==1) \
//             int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
//             int l = (x1-1)*n+y1;
//             int r = (x2-1)*n+y2;
//             cout<<query(0,1,n*n,l,r,seg)<<"\n";
//         }else {
//             int x,y,c; cin>>x>>y>>c;
//             int p=(x-1)*n+y;
//             pointUpdate(0,1,n*n,p,c,seg);
//         }
//     }
//
// }
int main() {
    cin.tie(0)->sync_with_stdio(0);

}