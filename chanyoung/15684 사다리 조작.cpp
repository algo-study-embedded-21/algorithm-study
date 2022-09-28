#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 1:14 예제 정답 >> 시간초과 >> 점 접근에서 선 접근으로 변경
// 1:48 PASS (여전히 9% 예제에서 시간초과 위험)

using namespace std;

struct gps
{
	int y;
	int x;
};

int n, m, h;
int block[32][10]; // 세로선 사이의 가로선을 나타냄
int ans = 10;

int down(int num) // num번째 세로선의 도착지점 구하기
{
	gps now = { 1,num };
	while (now.y != h+1)
	{
		if (now.x<n && block[now.y][now.x] == 1)
		{
			now.x += 1;
		}
		else if (now.x > 1 && block[now.y][now.x - 1] == 1)
		{
			now.x -= 1;
		}
		now.y += 1;
	}
	return now.x;
}

int check() // 원하는 사다리 완성시 1 리턴
{
	int flag = 1;
	for (int i = 1; i <= n; i++)
	{
		if (i != down(i))
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

void put(int level,int num)
{
	if (level > ans) // 이미 성공한 횟수보다 더 많은 시도 필요 X
	{
		return;
	}
	if (level > 3) // 3번 이상 시도 X
	{
		return;
	}
	if (check() == 1) // 사다리 완성시 횟수 갱신
	{
		ans = min(ans, level);
		return;
	}
	for (int i = num; i <= h; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (block[i][j] > 0) //이미 사다리 놓은곳pass
			{
				continue;
			}
			block[i][j] = 1;
			put(level + 1, i); // 중복 경우의수 제외 위해 i부터 탐색
			block[i][j] = 0;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> h;
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		block[a][b] = 1;
	}
	put(0,1);
	if (ans == 10) // 3번 이내에 불가능한경우 -1 출력
	{
		ans = -1;
	}
	cout << ans;

	return 0;
}