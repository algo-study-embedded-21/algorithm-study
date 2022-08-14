#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct gps {
	int y;
	int x;
};

struct moment {
	int time;
	char direction;
};

int n, k;
int L;
vector<moment> go;
int map[100][100];
int overtime;
int direcNum_head;
int direcNum_tail;
int body;
int t_head;
int t_tail;
int yy[4] = { 0,1,0,-1 };
int xx[4] = { 1,0,-1,0 };

void game(gps start)
{
	queue<gps> q;
	q.push(start);
	map[start.y][start.x] = 1;

	while (1)
	{
		while (direcNum_head >=go.size() || overtime != go[direcNum_head].time) // 다음 방향을 트는 시간까지 진행
		{
			gps now = q.front();
			q.pop();
			gps next; // 머리위치 
			next.y = now.y + yy[t_head];
			next.x = now.x + xx[t_head];
			if (next.y < 0 || next.y>n - 1 || next.x<0 || next.x>n - 1)
			{ // 벽에 닿으면 게임 오버
				overtime++;
				return;
			}
			if (map[next.y][next.x] == 1)
			{ // 몸에 닿으면 게임 오버
				overtime++;
				return;
			}
			if (map[next.y][next.x] == 5)
			{ // 사과를 먹은경우
				map[next.y][next.x] = 1;
				overtime++;
				body++; // 몸길이 증가
				q.push(next);
			}
			else
			{ // 빈공간으로 이동한경우
				map[next.y][next.x] = 1;
				overtime++;
				map[start.y][start.x] = 0; // 꼬리 위치수축
				start.y = start.y + yy[t_tail];
				start.x = start.x + xx[t_tail];
				q.push(next);
			}
			if (direcNum_tail<go.size() && overtime - body == go[direcNum_tail].time) // 꼬리가 꺽는 머리가 꺽은 위치에 도달한 경우
			{
				if (go[direcNum_tail].direction == 'L')
				{
					t_tail = t_tail - 1;
					if (t_tail < 0)
					{
						t_tail = 3;
					}
					direcNum_tail++;
				}
				else if (go[direcNum_tail].direction == 'D')
				{
					t_tail = t_tail + 1;
					if (t_tail > 3)
					{
						t_tail = 0;
					}
					direcNum_tail++;
				}
			}
		}
		if (go[direcNum_head].direction == 'L') // 머리 방향이 꺾이는 시간인 경우
		{
			t_head = t_head - 1;
			if (t_head < 0)
			{
				t_head = 3;
			}
			direcNum_head++;
		}
		else if (go[direcNum_head].direction == 'D')
		{
			t_head = t_head + 1;
			if (t_head > 3)
			{
				t_head = 0;
			}
			direcNum_head++;
		}
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i < k; i++)
	{ // 맵을 0,0 기준으로 세팅
		int y, x;
		cin >> y >> x;
		map[y-1][x-1] = 5;
	}
	cin >> L;
	for (int i = 0; i < L; i++)
	{
		int x;
		char c;
		cin >> x >> c;
		go.push_back({ x,c });
	}
	game({ 0,0 });
	cout << overtime;
	
	return 0;
}