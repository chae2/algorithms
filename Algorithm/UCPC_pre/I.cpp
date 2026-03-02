#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int y[200001];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> y[i];
    }
    sort(y, y + N);
    vector<int> v;
    for (int i = 0; i < N; i++)
    {
        if (y[i] == y[i + 1])
            continue;
        else
            v.push_back(y[i]);
    }
    int cnt = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i]+1 == v[i + 1])
        {
            continue;
        }
        else
            cnt += 1;
    }
    cout << cnt << "\n";
    cout << N;
    return 0;
}
