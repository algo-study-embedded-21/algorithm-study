#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>

// 1:05  ���� 1�� ����
// 1:20  ���� 2�� ����
// 2:16  ����

using namespace std;

struct gps { int y; int x; };

int n, q;
int map[70][70]; // 2^6 =64
vector<int> command; //�ֹ� ����

int yy[4] = { 0,0,1,-1 };
int xx[4] = { 1,-1,0,0 };

void turn(int dy, int dx, int sector) // ������ ���� ������ �ð�������� ������
{
	int temp[70][70] = { 0 };
	for (int i = dy; i < dy + sector; i++)
	{
		for (int j = dx; j < dx + sector; j++)
		{
			temp[dy+j-dx][dx+sector-1-i+dy] = map[i][j];
		}
	}
	for (int i = dy; i < dy + sector; i++)
	{
		for (int j = dx; j < dx + sector; j++)
		{
			map[i][j] = temp[i][j];
		}
	}
}

void magic(int L,int N) // ���� ���� >> ������ �̵��ذ��� �����ֱ�
{
	int sector = pow(2, L);
	if (sector <= 1) return;
	for (int i = 0; i <= N-sector; i += sector)
	{
		for (int j = 0; j <= N - sector; j += sector)
		{
			turn(i, j, sector);
		}
	}
}

void ice(int N) // ���ǿ� �´� ���� ���̱�
{
	vector<gps> melt;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] <= 0)continue;
			int cnt = 0;
			for (int d = 0; d < 4; d++)
			{
				gps nt = { i + yy[d],j + xx[d] };
				if (nt.y<0 || nt.y>N - 1 || nt.x<0 || nt.x>N - 1)continue;
				if (map[nt.y][nt.x] <= 0)continue;
				cnt++;
			}
			if (cnt < 3) melt.push_back({ i,j });
		}
	}
	for (int i = 0; i < melt.size(); i++) map[melt[i].y][melt[i].x] -= 1; // ���� �ȹް� �ѹ��� ���̱�
}

gps result(int N)  //result.y = �� ������ ��  // result.x = ����ū ������� ũ��
{
	int visit[70][70] = { 0 };
	int giant = 0;
	int totalice = 0;
	for(int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] <= 0)continue;
			totalice += map[i][j]; // ���� �ѷ� ����
			queue<gps> qq;
			qq.push({ i,j });
			visit[i][j] = 1;
			int cnt = 2;
			while (!qq.empty())
			{
				gps now = qq.front();
				qq.pop();
				for (int d = 0; d < 4; d++)
				{
					gps next = { now.y + yy[d],now.x + xx[d] };
					if (next.y > N - 1 || next.y<0 || next.x>N - 1 || next.x < 0)continue;
					if (map[next.y][next.x] <= 0)continue;
					if (visit[next.y][next.x] > 0)continue;
					visit[next.y][next.x] = cnt;
					giant = max(giant, cnt); // ����ū ������� ����
					cnt++;
					qq.push(next);
				}
			}
		}
	}
	return { totalice,giant };
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> q;
	int N = pow(2, n);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < q; i++)
	{
		int a;
		cin >> a;
		command.push_back(a);
	}
	for (int i = 0; i < q; i++)
	{
		magic(command[i], N);
		ice(N);
	}
	gps res = result(N);
	cout << res.y << "\n" << res.x;

	return 0;
}