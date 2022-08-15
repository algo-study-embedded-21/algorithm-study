#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

struct gps {  // 좌표 구조체
	int y;
	int x;
};

int n, m, x, y, k;
int map[20][20]; // 맵
int dice[6]; // 주사위 전개도 저장 배열
/*0
1 2 3    5가 바닥면 2가 윗면
  4
  5*/
int save; // 주사위값 교체를 위한 저장변수
vector<int> go; // 명령 저장 벡터

void change(gps now) // 도착한 맵의 숫자에 따른 주사위 밑면 숫자 바꿈 함수
{
	if (map[now.y][now.x] == 0)
	{ // 맵이 0이면 주사위 밑면 숫자를 복사해온다
		map[now.y][now.x] = dice[5];
	}
	else
	{ // 맵이 0이 아니면 그 숫자를 주사위 밑면에 복사하고 맵을 0으로 만든다
		dice[5] = map[now.y][now.x];
		map[now.y][now.x] = 0;
	}
}

void roll(gps start)
{
	queue<gps> q;
	q.push(start);
	/*change(start);*/
	for (int i = 0; i < k; i++) // 명령수 만큼 반복
	{
		gps now = q.front();
		q.pop();
		gps next;
		if (go[i] == 1) // 명령이 1 >> 동쪽으로 굴림
		{
			next.y = now.y;
			next.x = now.x + 1;
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)
			{ // 맵을 벗어나는 경우 무시하고 다시 현재위치로 갱신
				q.push(now);
				continue;
			}
			save = dice[2];
			dice[2] = dice[1];
			dice[1] = dice[5];
			dice[5] = dice[3];
			dice[3] = save;
			change(next); // 도착한 칸에서 주사위 밑면 바꿈
			q.push(next); // 현재 위치 갱신
			cout << dice[2] << "\n"; // 윗면 출력

		}
		else if (go[i] == 2) // 명령이 2 >> 서쪽으로 굴림
		{
			next.y = now.y;
			next.x = now.x - 1;
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)
			{
				q.push(now);
				continue;
			}
			save = dice[2];
			dice[2] = dice[3];
			dice[3] = dice[5];
			dice[5] = dice[1];
			dice[1] = save;
			change(next);
			q.push(next);
			cout << dice[2] << "\n";

		}
		else if (go[i] == 3) // 명령이 3 >> 북쪽으로 굴림
		{
			next.y = now.y - 1;
			next.x = now.x;
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)
			{
				q.push(now);
				continue;
			}
			save = dice[2];
			dice[2] = dice[4];
			dice[4] = dice[5];
			dice[5] = dice[0];
			dice[0] = save;
			change(next);
			q.push(next);
			cout << dice[2] << "\n";

		}
		else if (go[i] == 4) // 명령이 4 >> 남쪽으로 굴림
		{
			next.y = now.y + 1;
			next.x = now.x;
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)
			{
				q.push(now);
				continue;
			}
			save = dice[2];
			dice[2] = dice[0];
			dice[0] = dice[5];
			dice[5] = dice[4];
			dice[4] = save;
			change(next);
			q.push(next);
			cout << dice[2] << "\n";
		}

	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> x >> y >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < k; i++)
	{
		int a;
		cin >> a;
		go.push_back(a);
	}
	roll({ x,y });

	return 0;
}