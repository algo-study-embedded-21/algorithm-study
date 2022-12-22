#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

struct gps { int y, x; };

int n;
int map[100][100]; // 색종이가 붙어있는지 여부
int col[100][100]; // 열의 연속된 길이 표시

int ans = -1;

void post(gps st)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			map[st.y + i][st.x + j] = 1;
		}
	}
}

void square()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (map[i][j] == 1)
			{
				int minlen = col[i][j];
				int cnt = 1;
				ans = max(minlen * cnt,ans);
				int d = j+1;
				while (map[i][d] == 1) // 색종이가 연결된동안
				{
					cnt++; // 연속된 길이
					minlen = min(minlen, col[i][d]); // 가장 낮은 높이 = 공통 높이
					ans = max(ans, minlen * cnt); // 공통높이 x 길이 = 넓이 중 최댓값
					d++;
				}
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		post({ y,x }); // 색종이 붙이기
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (map[i][j] == 1)
			{
				if (i == 0) col[i][j] = 1;
				else col[i][j] = col[i - 1][j] + 1;
			}
		}
	}
	square();
	cout << ans;
	
	return 0;
}
