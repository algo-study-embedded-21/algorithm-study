#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
int map[1000];
int dp[1000];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n;
    for (int i = 0; i < n; i++) cin >> map[i];
    dp[0] = 1; // 제외되지 않기 위해 출발지점을 1로 세팅
    for (int i = 0; i < n-1; i++)
    {
        if (dp[i] == 0)continue; // 갈수 없는 위치면 무시
        for (int j = 1; j <= map[i]; j++)
        {
            int now = i + j;
            if (now > n - 1)continue; // 맵을 넘어가면 무시
            if (dp[now]) dp[now] = min(dp[now], dp[i] + 1); // 이미 now지점에 간적있는경우 최솟값으로 갱신
            else dp[now] = dp[i] + 1; // 간적 없는경우 현재 지점에서 한번 점프로 갈수 있다
        }
    }
    if (dp[n - 1])cout << dp[n - 1] - 1;
    else cout << "-1";

    return 0;
}
