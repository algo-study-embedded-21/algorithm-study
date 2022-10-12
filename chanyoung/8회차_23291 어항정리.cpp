#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>

// 1 : 36 ���� 1~6 ����
// 2 : 06 ����!


using namespace std;

struct gps { int y; int x; };

int n, k;
int map[100][100];
int Ystart = 99; // ���� ������ �ִ� ���� �Ʒ� ��ǥ (����)
int Yend = 98; // ���� ������ �ִ� ���� �� ��ǥ +1
int Xstart = 0; // ���� ������ �ִ� ���� ������ǥ
int Xend = 1; // ���ߺξ��� ������ ���� ������ ��ǥ +1
int stack = Xend - Xstart; // �ٴ��� ���� ���� ���� ����

int yy[2] = { -1,0 };
int xx[2] = { 0,1 };

void level1() // ���� ���� �ø���
{
	while ((Xend + Ystart - Yend) <= n) // �̹��� ���� ������ ���������� �ʴµ��� 
	{
		for (int i = Ystart; i > Yend; i--)
		{
			for (int j = Xstart; j < Xend; j++)
			{
				map[Ystart - stack + (j - Xstart)][Xend + (Ystart - i)] = map[i][j];
				map[i][j] = 0;
			}
		}
		Xstart = Xend;
		Xend = Xend + (Ystart - Yend);
		Yend = Ystart - stack - 1;
		stack = Xend - Xstart;
	}
}

void level2() // ����� ��й�
{
	int move[100][100] = { 0 }; // ���ÿ� �Ͼ�� ��ǿ� ������ ���� �ʱ����� ���� �迭 �ϳ� ����
	for (int i = Ystart; i > Yend; i--)
	{
		for (int j = Xstart; j < n; j++)
		{
			if (map[i][j] != 0)
			{
				for (int d = 0; d < 2; d++) // �ߺ��� ���ϱ� ���� ��,������ ���⸸ �˻�
				{
					gps next = { i + yy[d],j + xx[d] };
					if (next.y > 99 || next.y <= Yend || next.x > n - 1 || next.x < Xstart)continue; // ������ �ִ� ���� ��
					if (map[next.y][next.x] == 0)continue;
					if (map[i][j] == map[next.y][next.x])continue; // ������� ��ġ�Ұ� ����
					int bigger = max(map[next.y][next.x], map[i][j]);
					int smaller = min(map[next.y][next.x], map[i][j]);
					if (bigger - smaller >= 5)
					{
						int movement = (bigger - smaller) / 5;
						if (map[next.y][next.x] > map[i][j])
						{
							move[next.y][next.x] -= movement;
							move[i][j] += movement;
						}
						else
						{
							move[next.y][next.x] += movement;
							move[i][j] -= movement;
						}
					}
				}
			}
		}
	}
	for (int i = Ystart; i > Yend; i--)
	{
		for (int j = Xstart; j < n; j++)
		{
			if (move[i][j] == 0)continue;
			map[i][j] += move[i][j]; // �����迭 �ջ�
		}
	}
}

void level3() // ���� ��ġ��
{
	int put = 0;
	for (int j = Xstart; j < n; j++) // 2. ���� ���� ���׺���
	{
		for (int i = Ystart; i > Yend; i--) // 1. ���� �Ʒ��� ���׺���
		{
			if (map[i][j] == 0)continue;
			map[99][put] = map[i][j]; // ���� ���ʺ��� ä���ֱ�
			if (i != 99)map[i][j] = 0;
			put++;
		}
	}
	Yend = 98; // �ʱⰪ���� ����
	Xstart = 0;
	Xend = 1;
	stack = Xend - Xstart;
}

void level4() // �ݾ� �߶� �ø���
{
	int N = n / 2; // ù ��
	for (int j = 0; j < N; j++)
	{
		map[98][n-1 - j] = map[99][j]; // 180�� ȸ���Ͽ� �ø��� >> ���� �����ʺ��� ä���ֱ�
		map[99][j] = 0;
	}
	int NN = n - (N / 2); // ���� �� ��ǥ
	for (int i = 99; i >= 98; i--)// �ΰ��� ����
	{
		for (int j = N; j < NN; j++)
		{
			map[97-(i-98)][n - 1 - (j - N)] = map[i][j];
			map[i][j] = 0;
		}
	}
	Yend = 95; // 4�������̷� ����
	Xstart = NN; // ���� �� ��ǥ����
	Xend = n; // ������ ����
}

int check() // ���� ���� ������ ���� ���� ������� ���� ��ȯ
{
	int maxfish = -1;
	int minfish = 10001;
	for (int i = 0; i < n; i++)
	{
		maxfish = max(maxfish, map[99][i]);
		minfish = min(minfish, map[99][i]);
	}
	return maxfish - minfish;
}

int pot() // ������ �����ϴ� ����Ƚ�� ��ȯ
{
	int cnt = 0;
	int fish = check();
	while (fish > k) // ��ǥ������ ū����
	{
		int m = 10001;
		vector<gps> minfish; // ���� ���� ����Ⱑ �ִ� ���׵��� ��ġ ����
		for (int i = 0; i < n; i++)
		{
			if (map[99][i] < m)
			{
				minfish.clear(); // ����
				minfish.push_back({ 99,i });
				m = map[99][i];
			}
			else if (map[99][i] == m) minfish.push_back({ 99,i }); // �߰�
		}
		for (int i = 0; i < minfish.size(); i++)
		{
			gps fish = minfish[i];
			map[fish.y][fish.x] += 1; // ���� �������� ���׵� ����� +1
		}
		level1();
		level2();
		level3();
		level4();
		level2();
		level3();
		cnt++; // +1ȸ
		fish = check();
	}
	return cnt;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> map[99][i];
	}
	cout << pot();
	return 0;
}