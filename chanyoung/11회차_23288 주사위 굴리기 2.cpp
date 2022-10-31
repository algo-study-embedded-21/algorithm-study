#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

//41�� ����

struct gps { int y, x; };

int n, m, k;
int map[20][20];
gps dice = { 0,0 }; // �ֻ��� ��ġ
int dd = 0; // �ֻ��� ���� ����
int dnum[6] = { 1,2,3,4,5,6 }; // ��index :0, �Ʒ� index : 5
int score;

int change[4][6] = // ������ ���⿡ ���� �ٲ� �ε��� ��ȣ
{
	{3,1,0,5,4,2},
	{2,1,5,0,4,3},
	{1,5,2,3,0,4},
	{4,0,2,3,5,1}
};

int yy[4] = { 0,0,1,-1 };
int xx[4] = { 1,-1,0,0 };

int turnd[4] = { 2,3,1,0 }; // �ð���� ȸ�� ���⺤�� �ε��� ����
int returnd[4] = { 3,2,0,1 }; // �ݽð����  ...

int back(int d) // �� ������ ���� �ݴ�� �����ִ� �Լ�
{
	if (d == 1 || d == 3)return d - 1;
	else return d + 1;
}

void roll(int d) // �ֻ��� ������
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

int fill(gps st) // �����ؼ� �̵��Ҽ� �ִ� ĭ�� ���ϱ�
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
			if (map[next.y][next.x] != num)continue; // ���� ���ڷθ� �̵�
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
		if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1) // �� ����� ���� �ݴ��
		{
			dd = back(dd);
			next = { dice.y + yy[dd],dice.x + xx[dd] };
		}
		roll(dd);
		int blockcnt = fill(next);
		score += blockcnt * map[next.y][next.x];
		dice = next;
		if (map[next.y][next.x] < dnum[5]) dd = turnd[dd]; // �ð����
		else if (map[next.y][next.x] > dnum[5])dd = returnd[dd]; // �ݽð����
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