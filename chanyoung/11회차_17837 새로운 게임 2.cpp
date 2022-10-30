#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// 59분 예제 1,2,3 정답
// 1:05 정답

struct gps { int y, x; };
struct unit { int num, d; }; // num = 움직일 순서 , d = 방향
struct info { gps g; int stack; }; // gps = 위치 , stack = 쌓여진 높이

int n, k;
int color[12][12]; // 각 위치의 색 정보
vector<unit> map[12][12];
vector<info> chess;

int yy[4] = { 0,0,-1,1 };
int xx[4] = { 1,-1,0,0 };

int back(int d) // 반대방향 반환 함수
{
	if (d == 0 || d == 2) return d + 1;
	else return d - 1;
}

int game()
{
	int turn = 1;
	int flag = 0;
	while (turn <= 1000)
	{
		for (int i = 0; i < k; i++)
		{
			info ch = chess[i]; // 지금 움직일 말 정보
			gps now = ch.g; // 지금 움직이는 말의 위치
			int d = map[now.y][now.x][ch.stack].d; // 움직일 말의 방향
			gps next = { now.y + yy[d],now.x + xx[d] }; // 움직인 위치
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1 || color[next.y][next.x] == 2) // 방향을 바꿔야 하는경우
			{
				d = back(d);
				next = { now.y + yy[d],now.x + xx[d] };
				map[now.y][now.x][ch.stack].d = d;
				if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1 || color[next.y][next.x] == 2) continue;// 못움직이는 경우
			}
			if (color[next.y][next.x] == 1) // 빨간색
			{
				int size = map[now.y][now.x].size();
				for (int j = size - 1; j >= ch.stack; j--) // 맨 윗말부터 해당 말까지 역순으로
				{
					unit top = map[now.y][now.x][j];
					map[next.y][next.x].push_back(top);
					chess[top.num] = { next, int(map[next.y][next.x].size() - 1) };
					map[now.y][now.x].pop_back();
					if (map[next.y][next.x].size() >= 4){
						flag = 1;
						break;
					}
				}
			}
			else // 흰색
			{
				int size = map[now.y][now.x].size();
				for (int j = ch.stack; j < size; j++) // 해당 말부터 맨 윗말까지 그대로
				{
					unit top = map[now.y][now.x][j];
					map[next.y][next.x].push_back(top);
					chess[top.num] = { next, int(map[next.y][next.x].size() - 1) };
					if (map[next.y][next.x].size() >= 4) {
						flag = 1;
						break;
					}
				}
				if (!flag) // 순서때문에 pop과정을 따로 진행
				{
					for (int a = 0; a < size - ch.stack; a++)
					{
						map[now.y][now.x].pop_back();
					}
				}
			}
			if (flag) break;
		}
		if (flag) break;
		turn++;
	}
	return turn;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> color[i][j];
		}
	}
	for (int i = 0; i < k; i++)
	{
		int y, x, d;
		cin >> y >> x >>d;
		map[y - 1][x - 1].push_back({ i ,d-1 });
		chess.push_back({ { y - 1,x - 1 }, 0 });
	}
	int turn = game();
	if (turn > 1000) cout << "-1";
	else cout << turn;

	return 0;
}