#include <iostream>
#include <cmath>
#include <vector>
typedef long long ll;
using namespace std;

ll D[200001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, Q;
    cin >> n;
    for(int i=1;i<=n;i++)cin>>D[i];
    cin>>Q;
    for(int i=0;i<Q;i++){
        int q;
        cin>>q;
        if(q==1){
            ll c,x;
            cin>>c>>x;
            ll left=x;
            ll right=x;
            ll start=c; ll end=c+1;

            while(start>0){
                if(left>D[start]){
                    ll tmp=D[start];
                    D[start]*=2;
                    left-=tmp;
                    start--;
                }
                else{
                    D[start]+=left;
                    break;
                }
            }
            while(end<=n){
                if(right>=D[end]){
                    ll tmp=D[end];
                    D[end]*=2;
                    right-=tmp;
                    end++;
                }
                else{
                    D[end]+=right;
                    break;
                }
            }
        }
        else{
            int a; cin>>a;
            cout<<D[a]<<"\n";
        }
    }
    return 0;
}
