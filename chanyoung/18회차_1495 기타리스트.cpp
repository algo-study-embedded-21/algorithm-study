#include <iostream>
#include <vector>

using namespace std;

int n, s, m;
vector<int> v;
int dp[51][1001]; // dp[n][i] = n번째 곡에서 i볼륨이 가능한지 여부
int ans = -1;

int calculation(int n1, int n2, int d)
{
	if (d) return n1 + n2;
	else return n1 - n2;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> s >> m;
	v.push_back(s);
	for (int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;
		v.push_back(a);
	}
	dp[0][s] = 1; // 시작 볼륨 세팅
	for (int i = 1; i <= n; i++) // n번째 곡까지
	{
		for (int j = 0; j <= m; j++)
		{
			if (dp[i - 1][j]) // i-1번째 곡에서 j볼륨이 가능했다면
			{
				for (int d = 0; d < 2; d++)
				{
					int cal = calculation(j, v[i], d); // i번째 곡에서 가능한 볼륨 계산
					if (cal<0 || cal>m)continue; // 범위 밖이면 무시
					dp[i][cal] = 1;
				}
			}
		}
	}
	for (int i = m; i >= 0; i--) // 가장 큰 볼륨 부터 탐색
	{
		if (dp[n][i])
		{
			ans = i; // 가능한 가장큰 볼륨 갱신후 탈출
			break;
		}
	}
	cout << ans;
	
	return 0;
}
