#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, k;
int coin[100];
long long dp[10001];
int visit[100001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> coin[i];
        if (coin[i] <= k)dp[coin[i]] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        int won = coin[i]; 
        if (visit[won]) continue; // 중복동전 제외
        visit[won] = 1;
        if (won > k)continue; // 목표금액보다 크면 제외
        for (int j = 0; j <= k - won; j++)
        {
            if (won + j > k)continue; 
            if (dp[j] == 0)continue; // j원을 구성할수 없는경우 제외
            if (dp[j + won]) dp[j + won] = min(dp[j] + 1, dp[j + won]); // j+won의 경우의 수가 이미 있을때, j원을 만드는경우의 수 + 1(won원짜리 동전1개 추가)중 작은수로 갱신
            else dp[j + won] = dp[j] + 1; // j+won을 처음 만드는경우
        }
    }
    if (dp[k])cout << dp[k]; //k원을 만드는게 가능한경우
    else cout << "-1";

    return 0;
}
