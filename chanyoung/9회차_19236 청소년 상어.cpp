#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

// 1:13 예제 1,3,4 정답
// 1:36 정답

using namespace std;

struct gps { int y, x; }; // 위치정보
struct fish { int num, d; }; // 각 물고기의 번호 와 방향

fish map[4][4];
int score;
gps shark; // 상어의 위치
int sharkD; // 상어의 방향
int ans = -1;

int yy[8] = { -1,-1,0,1,1,1,0,-1 };
int xx[8] = { 0,-1,-1,-1,0,1,1,1 };

void fish_move() // 물고기 움직임
{
	int now = 1;
	while (now <= 16) // 1번부터 순차적으로 이동
	{
		int flag = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++) // 온 맵을 조사하며
			{
				if (map[i][j].num == now) // 해당되는 물고기 찾아서
				{
					for (int d = 0; d < 8; d++) // 반시계방향으로 돌며 갈수있는 방향 찾기
					{
						int direction = (map[i][j].d + d) % 8; // 인덱스 터짐 방지
						gps next = { i + yy[direction],j + xx[direction] };
						if (next.y < 0 || next.y>3 || next.x < 0 || next.x>3)continue;
						if (next.y == shark.y && next.x == shark.x)continue;
						fish change = map[next.y][next.x]; // 위치 바꿀 물고기 정보
						map[next.y][next.x] = map[i][j];
						map[next.y][next.x].d = direction; // 반시계로 돌며 바뀐 방향으로 변경
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
	fish arr[4][4] = { 0 }; // 물고기 이동전 맵 저장
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arr[i][j] = map[i][j];
		}
	}
	fish_move();
	vector<gps> sharkPOS; // 상어가 갈수 있는 위치 모음
	gps next = shark;
	while (next.y + yy[sharkD] >= 0 && next.y + yy[sharkD] <= 3 && next.x + xx[sharkD] >= 0 && next.x + xx[sharkD] <= 3)
	{
		next = { next.y + yy[sharkD],next.x + xx[sharkD] };
		if (map[next.y][next.x].num == 0) continue; // 물고기 없는곳은 못감
		sharkPOS.push_back(next);
	}
	if (sharkPOS.size() == 0) // 갈수 있는곳이 없으면 탈출
	{
		ans = max(ans, score);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++) // 탈출전 물고기 이동 전으로 복귀
			{
				map[i][j] = arr[i][j];
			}
		}
		return;
	}
	for (int i = 0; i < sharkPOS.size(); i++)
	{
		gps now = sharkPOS[i]; // 상어가 갈 위치
		fish realfish = map[now.y][now.x]; // 먹을 고기 정보 저장
		gps realshark = shark; // 현재 상어 위치 저장
		int direction = sharkD; // 현재 상어 방향 저장
		shark = now;
		sharkD = realfish.d;
		score += realfish.num;
		map[now.y][now.x] = { 0,0 }; // 먹은 물고기 삭제
		shark_move();
		map[now.y][now.x] = realfish;
		shark = realshark;
		sharkD = direction;
		score -= realfish.num;
	}
	for (int i = 0; i < 4; i++) // 모든 경우의 수 따진후 물고기 이동전으로 복귀
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
			map[i][j] = { n,d - 1 }; // d는 1부터 인덱스는 0부터
		}
	}
	shark = { 0,0 }; // 상어 입장위치
	sharkD = map[0][0].d;
	score += map[0][0].num;
	map[0][0] = { 0,0 };
	shark_move();
	cout << ans;

	return 0;
}
