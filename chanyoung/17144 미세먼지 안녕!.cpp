#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

using namespace std;

struct gps
{
	int y;
	int x;
};

int r, c, t;
int map[50][50];
vector<gps> air; // ����û������ ��ġ
queue<gps> dust; // �������� ��ġ

int yy[4] = { 1,-1,0,0 };
int xx[4] = { 0,0,1,-1 };

void aircondition()
{  // ����û���� ��� ��ȯ
	for (int i = air[0].y - 1; i > 0; i--)
	{
		map[i][0] = map[i - 1][0];
		if (map[i][0] > 0)
		{
			dust.push({ i,0 });
		}
	}
	for (int i = 0; i < c - 1; i++)
	{
		map[0][i] = map[0][i + 1];
		if (map[0][i] > 0)
		{
			dust.push({ 0,i });
		}
	}
	for (int i = 0; i < air[0].y; i++)
	{
		map[i][c - 1] = map[i + 1][c - 1];
		if (map[i][c - 1] > 0)
		{
			dust.push({ i ,c - 1 });
		}
	}
	for (int i = c - 1; i > 1; i--)
	{
		map[air[0].y][i] = map[air[0].y][i - 1];
		if (map[air[0].y][i] > 0)
		{
			dust.push({ air[0].y,i});
		}
	}
	map[air[0].y][1] = 0;
	// ����û���� �Ϻ� ��ȯ
	for (int i = air[1].y + 1; i < r - 1; i++)
	{
		map[i][0] = map[i + 1][0];
		if (map[i][0] > 0)
		{
			dust.push({ i ,0 });
		}
	}
	for (int i = 0; i < c - 1; i++)
	{
		map[r - 1][i] = map[r - 1][i + 1];
		if (map[r - 1][i] > 0)
		{
			dust.push({ r-1,i});
		}
	}
	for (int i = r - 1; i > air[1].y; i--)
	{
		map[i][c - 1] = map[i - 1][c - 1];
		if (map[i][c - 1] > 0)
		{
			dust.push({ i ,c - 1 });
		}
	}
	for (int i = c - 1; i > 1; i--)
	{
		map[air[1].y][i] = map[air[1].y][i - 1];
		if (map[air[1].y][i] > 0)
		{
			dust.push({ air[1].y ,i });
		}
	}
	map[air[1].y][1] = 0;
}

void wind()
{
	int dustmap[50][50] ={0}; // Ȯ��Ǵ� �������� ����� �� (Ȯ���� ���ÿ� �Ͼ���� ������ ���� �ʱ� ����)
	int visit[50][50] = { 0 };
	int manydust = dust.size(); // ť�� ������ �ֱ��� ũ�⸸ŭ�� �ݺ��ϱ� ���� 
	queue<gps> plusdust; // ������ Ȯ��� ������ ��ġ
	for (int k = 0; k < manydust; k++)
	{
		gps now = dust.front();
		dust.pop();
		if (map[now.y][now.x] == 0) // ������ ���°��� ����
		{
			continue;
		}
		if (visit[now.y][now.x] > 0) // �̹� Ȯ���� �õ��� ���� ����
		{
			continue;
		}
		dust.push(now);
		visit[now.y][now.x] = 1;
		int minidust = map[now.y][now.x] / 5; // Ȯ��� ������ ��
		if (minidust == 0)
		{
			continue; // Ȯ���� ����ũ�Ⱑ 0�̸� ����
		}
		int cnt = 0; // �� ���̳� Ȯ��Ǿ����� ī����
		for (int i = 0; i < 4; i++)
		{
			gps next;
			next.y = now.y + yy[i];
			next.x = now.x + xx[i];
			if (next.y<0 || next.y>r - 1 || next.x<0 || next.x>c - 1)
			{
				continue;
			}
			if (map[next.y][next.x] == -1) // ����û���δ� Ȯ�� X
			{
				continue;
			}
			cnt++;
			if (dustmap[next.y][next.x] == 0) // Ȯ����� ���°��̸� ��ġ ����(�ߺ�����)
			{
				plusdust.push(next);
			}
			dustmap[next.y][next.x] += minidust;
		}
		map[now.y][now.x] -= minidust * cnt; // now�� ���� Ȯ���� ������ Ȯ��� ������ŭ ����
	}
	manydust = plusdust.size(); 
	for (int i = 0; i < manydust; i++)
	{
		gps now = plusdust.front();
		plusdust.pop();
		if (map[now.y][now.x] == 0)
		{
			dust.push(now); // ������ ���� ��ġ��� ����
		}
		map[now.y][now.x] += dustmap[now.y][now.x]; // �� �ʿ� Ȯ��� ���� �߰�
	}
	aircondition(); // ����û���� ����
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> r >> c >> t;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			int a;
			cin >> a;
			map[i][j]=a;
			if (a == -1)
			{
				air.push_back({ i,j });
			}
			else if (a != 0)
			{
				dust.push({ i,j });
			}
		}
	}
	for (int i = 0; i < t; i++) // t�ʵ��� �ݺ�
	{
		wind();
	}
	int totaldust = 0; // �� ������ ��
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (map[i][j] > 0)
			{
				totaldust += map[i][j];
			}
		}
	}
	cout << totaldust;

	return 0;
}