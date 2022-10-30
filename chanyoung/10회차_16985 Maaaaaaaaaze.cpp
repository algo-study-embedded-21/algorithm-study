#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// 45분 예제 1,2,3,4,6번 정답
// 1:31 정답

struct gps { int z, y, x; };

int cube[5][5][5] = { 0 }; // 참가자가 조합한 큐브
int save[5][5][5] = { 0 }; // 주어진 큐브
int ans = 500;
int stackvisit[5]; // 같은 층 중복 쌓음 방지

int yy[6] = { 0,0,-1,1,0,0 };
int xx[6] = { 1,-1,0,0,0,0 };
int zz[6] = { 0,0,0,0,1,-1 };

gps enter[8] = { {0,0,0},{0,0,4},{0,4,0},{0,4,4},{4,0,0},{4,0,4},{4,4,0},{4,4,4} }; // 입출구 후보 좌표

int maze(gps st) // 3차원 최소 탈출경로 완전탐색
{
	int visit[5][5][5] = { 0 };
	queue<gps> q;
	q.push(st);
	visit[st.z][st.y][st.x] = 1;
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int i = 0; i < 6; i++)
		{
			gps next = { now.z + zz[i], now.y + yy[i], now.x + xx[i] };
			if (next.z < 0 || next.z>4 || next.y < 0 || next.y>4 || next.x < 0 || next.x>4)continue;
			if (visit[next.z][next.y][next.x] > 0)continue;
			if (cube[next.z][next.y][next.x] == 0)continue;
			q.push(next);
			visit[next.z][next.y][next.x] = visit[now.z][now.y][now.x] + 1;
		}
	}
	return visit[4][4][4] - 1;
}

void exitcube(int level) // 큐브의 각 층을 돌리는 4가지 경우의수 완전탐색 (1024가지)
{
	if (level == 5) {
		if (cube[0][0][0] == 0 || cube[4][4][4] == 0)return; // 입 출구가 막힌경우 제외
		int exit = maze({ 0,0,0 });
		if (exit > 0) ans = min(ans, exit);
		return;
	}

	for (int d = 0; d < 4; d++)
	{
		int turn[5][5] = { 0 };
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				turn[j][4-i] = cube[level][i][j];
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cube[level][i][j] = turn[i][j];
			}
		}
		exitcube(level + 1);
	}
}

void stack(int level) // 5개의 층을 쌓아올리는 경우의수 3125가지 완전탐색
{
	if (level == 5)
	{
		int cnt = 0;
		for (int i = 0; i < 4; i++) // 입구후보
		{
			gps a = enter[i];
			if (cube[a.z][a.y][a.x] == 0) cnt++;
		}
		if (cnt == 4)return;// 모든 입구가 막혔으면 제외
		cnt = 0;
		for (int i = 4; i < 8; i++) // 출구후보
		{
			gps a = enter[i];
			if (cube[a.z][a.y][a.x] == 0) cnt++;
		}
		if (cnt == 4)return; // 모든 출구후보가 막혔다면 제외
		exitcube(0);
		return;
	}
	for (int z = 0; z < 5; z++)
	{
		if (stackvisit[z] == 1)continue; // 이미 선택된 층으로 중복쌓기 방지
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cube[level][i][j] = save[z][i][j];
			}
		}
		stackvisit[z] = 1;
		stack(level + 1);
		stackvisit[z] = 0;
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				cin >> save[i][j][k];
			}
		}
	}
	stack(0);
	if (ans == 500) cout << "-1";
	else cout << ans;

	return 0;
}
