#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

//41분 정답

struct gps { int y, x; };

int n, m, k;
int map[20][20];
gps dice = { 0,0 }; // 주사위 위치
int dd = 0; // 주사위 굴릴 방향
int dnum[6] = { 1,2,3,4,5,6 }; // 위index :0, 아래 index : 5
int score;

int change[4][6] = // 구르는 방향에 따른 바뀔 인덱스 번호
{
	{3,1,0,5,4,2},
	{2,1,5,0,4,3},
	{1,5,2,3,0,4},
	{4,0,2,3,5,1}
};

int yy[4] = { 0,0,1,-1 };
int xx[4] = { 1,-1,0,0 };

int turnd[4] = { 2,3,1,0 }; // 시계방향 회전 방향벡터 인덱스 변경
int returnd[4] = { 3,2,0,1 }; // 반시계방향  ...

int back(int d) // 맵 끝에서 방향 반대로 돌려주는 함수
{
	if (d == 1 || d == 3)return d - 1;
	else return d + 1;
}

void roll(int d) // 주사위 굴리기
{
	int tmp[6];
	for (int i = 0; i < 6; i++)
	{
		tmp[i] = dnum[change[d][i]];
	}
	for (int i = 0; i < 6; i++)
	{
		dnum[i] = tmp[i];
	}
}

int fill(gps st) // 연속해서 이동할수 있는 칸수 구하기
{
	queue<gps> q;
	int visit[20][20] = { 0 };
	q.push(st);
	visit[st.y][st.x] = 1;
	int num = map[st.y][st.x];
	int maxblock = 1;
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			gps next = { now.y + yy[i], now.x + xx[i] };
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)continue;
			if (map[next.y][next.x] != num)continue; // 같은 숫자로만 이동
			if (visit[next.y][next.x] > 0)continue;
			q.push(next);
			visit[next.y][next.x] = 1;
			maxblock++;
		}
	}
	return maxblock;
}

void go()
{
	for (int i = 0; i < k; i++)
	{
		gps next = { dice.y + yy[dd],dice.x + xx[dd] };
		if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1) // 맵 벗어나면 방향 반대로
		{
			dd = back(dd);
			next = { dice.y + yy[dd],dice.x + xx[dd] };
		}
		roll(dd);
		int blockcnt = fill(next);
		score += blockcnt * map[next.y][next.x];
		dice = next;
		if (map[next.y][next.x] < dnum[5]) dd = turnd[dd]; // 시계방향
		else if (map[next.y][next.x] > dnum[5])dd = returnd[dd]; // 반시계방향
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}
	go();
	cout << score;

	return 0;
}