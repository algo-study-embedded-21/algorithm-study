#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

// 1:13 예제 1,3,4 정답
// 1:36 정답

using namespace std;

struct gps { int y, x; };
struct fish { int num, d; };

fish map[4][4];
int score;
gps shark;
int sharkD;
int ans = -1;

int yy[8] = { -1,-1,0,1,1,1,0,-1 };
int xx[8] = { 0,-1,-1,-1,0,1,1,1 };

void fish_move()
{
	int now = 1;
	while (now <= 16)
	{
		int flag = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (map[i][j].num == now)
				{
					for (int d = 0; d < 8; d++)
					{
						int direction = (map[i][j].d + d) % 8;
						gps next = { i + yy[direction],j + xx[direction] };
						if (next.y < 0 || next.y>3 || next.x < 0 || next.x>3)continue;
						if (next.y == shark.y && next.x == shark.x)continue;
						fish change = map[next.y][next.x];
						map[next.y][next.x] = map[i][j];
						map[next.y][next.x].d = direction;
						map[i][j] = change;
						break;
					}
					flag = 1;
					break;
				}
			}
			if (flag)break;
		}
		now++;
	}
}

void shark_move()
{
	fish arr[4][4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arr[i][j] = map[i][j];
		}
	}
	fish_move();
	vector<gps> sharkPOS;
	gps next = shark;
	while (next.y + yy[sharkD] >= 0 && next.y + yy[sharkD] <= 3 && next.x + xx[sharkD] >= 0 && next.x + xx[sharkD] <= 3)
	{
		next = { next.y + yy[sharkD],next.x + xx[sharkD] };
		if (map[next.y][next.x].num == 0) continue;
		sharkPOS.push_back(next);
	}
	if (sharkPOS.size() == 0)
	{
		ans = max(ans, score);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][j] = arr[i][j];
			}
		}
		return;
	}
	for (int i = 0; i < sharkPOS.size(); i++)
	{
		gps now = sharkPOS[i];
		fish realfish = map[now.y][now.x];
		gps realshark = shark;
		int direction = sharkD;
		shark = now;
		sharkD = realfish.d;
		score += realfish.num;
		map[now.y][now.x] = { 0,0 };
		shark_move();
		map[now.y][now.x] = realfish;
		shark = realshark;
		sharkD = direction;
		score -= realfish.num;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = arr[i][j];
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int n, d;
			cin >> n >> d;
			map[i][j] = { n,d - 1 };
		}
	}
	shark = { 0,0 };
	sharkD = map[0][0].d;
	score += map[0][0].num;
	map[0][0] = { 0,0 };
	shark_move();
	cout << ans;

	return 0;
}