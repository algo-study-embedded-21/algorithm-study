#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct gps { int y, x; };

int n, m;
int map[1000][1000];
long long dp[1000][1000];

int yy[3] = { -1,0,-1 };
int xx[3] = { 0,-1,-1 };

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }
    dp[0][0] = map[0][0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0 && j == 0)continue;
            for (int d = 0; d < 3; d++)
            {
                int dy = i + yy[d]; // dy,dx : i,j 위치로 올수 있는 좌표
                int dx = j + xx[d];
                if (dy < 0 || dx < 0)continue; // 맵 벗어나는것 방지
                dp[i][j] = max(dp[i][j], dp[dy][dx] + map[i][j]); // 3가지 방향중 가장 큰 값으로 갱신하며 진행
            }
        }
    }
    cout << dp[n - 1][m - 1];

    return 0;
}
