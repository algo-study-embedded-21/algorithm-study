#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct value { int w, v; };

int n, k;
vector<value> obj;
int dp[101][100001];

bool cmp(value l, value r)
{
    if (l.w < r.w) return true;
    if (l.v > r.v)return true;
    
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    
    cin >> n >> k;
    obj.push_back({ 0,0 });
    for (int i = 0; i < n; i++)
    {
        int w, v;
        cin >> w >> v;
        obj.push_back({ w,v });
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (obj[i].w > j)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - obj[i].w] + obj[i].v);
            }
        }
    }

    cout << dp[n][k];
    
    return 0;
}