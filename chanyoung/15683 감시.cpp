#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

struct gps {
	int y;
	int x;
};

struct cctvgps
{
	int y;
	int x;
	int num;
};


int n, m;
int office[8][8];
int usecctv[8][8];
int minsee = 2134567890;
vector<cctvgps> cctvs;

void yplus(gps cctv)  // ���� ��ǥ�� ���� x������ y�� Ű��� ���ÿ��� ǥ��
{
	for (int i = cctv.y + 1; i < n; i++)
	{
		if (office[i][cctv.x] == 6) // ���̸� ��ž
		{
			break;
		}
		if ((office[i][cctv.x] <= 5 && office[i][cctv.x] >= 1) || office[i][cctv.x] == 10) // cctv�̰ų� �̹� �����ѿ����̸� ����
		{
			continue;
		}
		office[i][cctv.x] = 10;
	}
}
void yminus(gps cctv) // ���� ��ǥ�� ���� x������ y�� ���̸� ���ÿ��� ǥ��
{
	for (int i = cctv.y - 1; i >= 0; i--)
	{
		if (office[i][cctv.x] == 6)
		{
			break;
		}
		if ((office[i][cctv.x] <= 5 && office[i][cctv.x] >= 1) || office[i][cctv.x] == 10)
		{
			continue;
		}
		office[i][cctv.x] = 10;
	}
}
void xplus(gps cctv) // ���� ��ǥ�� ���� y������ x�� Ű��� ���ÿ��� ǥ��
{
	for (int i = cctv.x + 1; i < m; i++)
	{
		if (office[cctv.y][i] == 6)
		{
			break;
		}
		if ((office[cctv.y][i] <= 5 && office[cctv.y][i] >= 1) || office[cctv.y][i] == 10)
		{
			continue;
		}
		office[cctv.y][i] = 10;
	}
}
void xminus(gps cctv)  // ���� ��ǥ�� ���� y������ x�� ���̸� ���ÿ��� ǥ��
{
	for (int i = cctv.x - 1; i >= 0; i--)
	{
		if (office[cctv.y][i] == 6)
		{
			break;
		}
		if ((office[cctv.y][i] <= 5 && office[cctv.y][i] >= 1) || office[cctv.y][i] == 10)
		{
			continue;
		}
		office[cctv.y][i] = 10;
	}
}

void one(gps cctv, int direction) // 1�� cctv�� ���
{
	if (direction == 1)
	{
		xplus(cctv);
	}
	else if (direction == 2)
	{
		xminus(cctv);
	}
	else if (direction == 3)
	{
		yplus(cctv);
	}
	else if (direction == 4)
	{
		yminus(cctv);
	}
}

void two(gps cctv, int direction) // 2�� cctv�� ���
{
	if (direction == 1 || direction ==3)
	{
		yplus(cctv);
		yminus(cctv);
	}
	else if (direction == 2 || direction == 4)
	{
		xplus(cctv);
		xminus(cctv);
	}
}

void three(gps cctv, int direction) // 3�� cctv�� ���
{
	if (direction == 1)
	{
		xplus(cctv);
		yplus(cctv);
	}
	else if (direction == 2)
	{
		xminus(cctv);
		yplus(cctv);
	}
	else if (direction == 3)
	{
		xplus(cctv);
		yminus(cctv);
	}
	else if (direction == 4)
	{
		xminus(cctv);
		yminus(cctv);
	}
}

void four(gps cctv, int direction) // 4�� cctv�� ���
{
	if (direction == 1)
	{
		xplus(cctv);
		yplus(cctv);
		xminus(cctv);
	}
	else if (direction == 2)
	{
		xminus(cctv);
		yplus(cctv);
		yminus(cctv);
	}
	else if (direction == 3)
	{
		xplus(cctv);
		yminus(cctv);
		yplus(cctv);
	}
	else if (direction == 4)
	{
		xminus(cctv);
		yminus(cctv);
		xplus(cctv);
	}
}

void five(gps cctv, int direction) // 5�� cctv�� ���
{
	xplus(cctv);
	xminus(cctv);
	yplus(cctv);
	yminus(cctv);
}

void resetmap(int officesave[8][8]) // ���� �������·� ������Ű�� �Լ�
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			office[i][j] = officesave[i][j];
		}
	}
}

void savemap(int officesave[8][8]) // �������� ���� �����ϴ� �Լ�
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			officesave[i][j] = office[i][j];
		}
	}
}

void see(int index)
{
	if (index == cctvs.size()) // ��� cctv�� ���ÿ����� ǥ���ߴٸ�
	{
		int cnt = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (office[i][j] == 0) // �簢���븦 ī��Ʈ
				{
					cnt++;
				}
			}
		}
		if (cnt < minsee)
		{
			minsee = cnt;
		}
		return;
	}
	for (int j = 1; j <= 4; j++) // cctv�� direction �ִ� 4��
	{
		cctvgps now = cctvs[index];
		if (usecctv[now.y][now.x] == 1) // �̹� ������ cctv�� ����
		{
			continue;
		}
		if (now.num == 1) // 1�� cctv�� ���
		{
			usecctv[now.y][now.x] = 1; // ��������� ����ϰ�
			int officesave[8][8]; // ��������� ���� ����� ��2�� �����
			savemap(officesave); // ���� ����ϰ�
			one({ now.y,now.x }, j); //  1�� cctv�� ���ÿ����� ���
			see(index+1);  // ���� cctv�� �̵�
			resetmap(officesave); // ���� ������ �ʱ�ȭ�ϰ�
			usecctv[now.y][now.x] = 0; // cctv ����� �ʱ�ȭ
		}
		else if (now.num == 2)
		{
			usecctv[now.y][now.x] = 1;
			int officesave[8][8];
			savemap(officesave);
			two({ now.y,now.x }, j);
			see(index + 1);
			resetmap(officesave);
			usecctv[now.y][now.x] = 0;
		}
		else if (now.num == 3)
		{
			usecctv[now.y][now.x] = 1;
			int officesave[8][8];
			savemap(officesave);
			three({ now.y,now.x }, j);
			see(index + 1);
			resetmap(officesave);
			usecctv[now.y][now.x] = 0;
		}
		else if (now.num == 4)
		{
			usecctv[now.y][now.x] = 1;
			int officesave[8][8];
			savemap(officesave);
			four({ now.y,now.x }, j);
			see(index + 1);
			resetmap(officesave);
			usecctv[now.y][now.x] = 0;
		}
		else if (now.num == 5)
		{
			usecctv[now.y][now.x] = 1;
			int officesave[8][8];
			savemap(officesave);
			five({ now.y,now.x }, j);
			see(index + 1);
			resetmap(officesave);
			usecctv[now.y][now.x] = 0;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> office[i][j];
			if (office[i][j] >= 1 && office[i][j] <= 5) //cctv�� ���
			{
				cctvs.push_back({ i,j,office[i][j]}); // cctv�� ��ǥ�� cctv �ѹ��� ���Ϳ� ����
			}
		}
	}
	see(0); // ù��° cctv���� ���ÿ��� ���� ����
	cout << minsee;
	return 0;
}