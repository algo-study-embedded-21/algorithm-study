#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 45�� ���� 1 ����

using namespace std;

struct gps { int y; int x; };

int n;
int map[500][500];

int yy[4][10] = {    // ���� ����迭 [����][%] ==> [��,��,��,��][1,2,7,10,5,a] ����
	{ -1,1,-2,2,-1,1,-1,1,0,0},
	{0,0,1,1,1,1,2,2,3,2},
	{-1,1,-2,2,-1,1,-1,1,0,0},
	{0,0,-1,-1,-1,-1,-2,-2,-3,-2} 
};
int xx[4][10] = {
	{0,0,-1,-1,-1,-1,-2,-2,-3,-2},
	{-1,1,-2,2,-1,1,-1,1,0,0},
	{0,0,1,1,1,1,2,2,3,2},
	{-1,1,-2,2,-1,1,-1,1,0,0}
};

int yyy[4] = { 0,1,0,-1 }; // ����̵��� ����迭
int xxx[4] = { -1,0,1,0 };

int per[9] = { 1,1,2,2,7,7,10,10,5 };// �� ����迭�� ���� �ۼ�Ʈ �ο�

void dust(gps now, int i) // �� ������
{
	gps ddust = { now.y + yyy[i] ,now.x + xxx[i] }; // �̵��� ����̵��� ��ġ
	if (ddust.y > n - 1 || ddust.y<0 || ddust.x>n - 1 || ddust.x < 0)
	{
		return;
	}
	long long Ndust = map[ddust.y][ddust.x]; // �̵��� ��ġ�� �� �ѷ�

	long long godust = 0;
	
	for (int k = 0; k < 10; k++)
	{
		gps next = { now.y + yy[i][k],now.x + xx[i][k] };
		if (k != 9)
		{
			godust += (Ndust * per[k]) / 100; // �� �ٱ����� �����°� ������ �̵��ϴ� ���� �ѷ�
		}
		if (next.y > n-1 || next.y<0 || next.x>n-1 || next.x < 0)
		{
			continue;
		}
		if (k == 9)
		{
			map[next.y][next.x] += Ndust - godust; // a ��ġ�� �̵��� �𷡸� �� �������� �� �̵�
			continue;
		}
		map[next.y][next.x] += Ndust * per[k] / 100;
	}
	map[ddust.y][ddust.x] = 0;
}

void storm()
{
	gps mid = { n / 2 ,n / 2  }; // �߾ӽ���
	gps now = mid;
	int dis = 1; // �ѹ������� �̵��ϴ� ����
	int flag = 0;
	while (1)
	{
		for (int i = 0; i < 2; i++) // ���� , �Ʒ��� ������ ���� dis��ŭ �̵�
		{
			int go = 0;
			while (go < dis)
			{
				dust(now, i);
				now = { now.y + yyy[i],now.x + xxx[i] };
				if (now.y > n - 1 || now.y<0 || now.x>n - 1 || now.x < 0)
				{
					flag = 1;
					break;
				}
				go++;
			}
			if (flag)
			{
				break;
			}
		}
		if (flag)
		{
			break;
		}
		dis++; // ������, ���� �̵��� ����, �Ʒ��� �̵����� 1��ŭ �� �̵��Ѵ�
		for (int i = 2; i < 4; i++) // ������ , ���� ������ ���� dis��ŭ �̵�
		{
			int go = 0;
			while (go < dis)
			{
				dust(now, i);
				now = { now.y + yyy[i],now.x + xxx[i] };
				if (now.y > n - 1 || now.y<0 || now.x>n - 1 || now.x < 0)
				{
					flag = 1;
					break;
				}
				go++;
			}
			if (flag)
			{
				break;
			}
		}
		if (flag)
		{
			break;
		}
		dis++;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	long long tdust = 0;
	for (int i = 0; i <n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			tdust += map[i][j]; // �ʱ� �� �ѷ�
		}
	}
	storm();
	long long ldust = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <n; j++)
		{
			ldust += map[i][j]; // ���� �� �ѷ�
		}
	}
	cout << tdust - ldust;

	return 0;
}