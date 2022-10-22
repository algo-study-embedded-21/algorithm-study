#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// 45�� ���� 1,2,3,4,6�� ����
// 1:31 ����

struct gps { int z, y, x; };

int cube[5][5][5] = { 0 }; // �����ڰ� ������ ť��
int save[5][5][5] = { 0 }; // �־��� ť��
int ans = 500;
int stackvisit[5]; // ���� �� �ߺ� ���� ����

int yy[6] = { 0,0,-1,1,0,0 };
int xx[6] = { 1,-1,0,0,0,0 };
int zz[6] = { 0,0,0,0,1,-1 };

gps enter[8] = { {0,0,0},{0,0,4},{0,4,0},{0,4,4},{4,0,0},{4,0,4},{4,4,0},{4,4,4} }; // ���ⱸ �ĺ� ��ǥ

int maze(gps st) // 3���� �ּ� Ż���� ����Ž��
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

void exitcube(int level) // ť���� �� ���� ������ 4���� ����Ǽ� ����Ž�� (1024����)
{
	if (level == 5) {
		if (cube[0][0][0] == 0 || cube[4][4][4] == 0)return; // �� �ⱸ�� ������� ����
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

void stack(int level) // 5���� ���� �׾ƿø��� ����Ǽ� 3125���� ����Ž��
{
	if (level == 5)
	{
		int cnt = 0;
		for (int i = 0; i < 4; i++) // �Ա��ĺ�
		{
			gps a = enter[i];
			if (cube[a.z][a.y][a.x] == 0) cnt++;
		}
		if (cnt == 4)return;// ��� �Ա��� �������� ����
		cnt = 0;
		for (int i = 4; i < 8; i++) // �ⱸ�ĺ�
		{
			gps a = enter[i];
			if (cube[a.z][a.y][a.x] == 0) cnt++;
		}
		if (cnt == 4)return; // ��� �ⱸ�ĺ��� �����ٸ� ����
		exitcube(0);
		return;
	}
	for (int z = 0; z < 5; z++)
	{
		if (stackvisit[z] == 1)continue; // �̹� ���õ� ������ �ߺ��ױ� ����
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