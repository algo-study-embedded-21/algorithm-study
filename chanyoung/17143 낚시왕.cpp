#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
//#include<algorithm>
#include<unordered_map>
//#include<cmath>

using namespace std;

struct shark
{
	int s;
	int d;
	int z;
};

struct gps
{
	int y;
	int x;
};

int r, c, m;
shark map[101][101];
shark movemap[101][101];
int ans;
queue<gps> shk;

int yy[5] = { 0,-1,1,0,0 };
int xx[5] = { 0,0,0,1,-1 }; // 1: �� 2:�Ʒ� 3: ������ 4: ���� �ε��� ����

gps turn(gps go)
{
	gps t;
	t.y =  r - 1 - abs((abs(go.y % (2 * (r - 1)))) - (r - 1)); //   -| |x%2r| - r| + r   r=r-1
	t.x =  c - 1 - abs((abs(go.x % (2 * (c - 1)))) - (c - 1));
	return t;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> r >> c >> m;
	for (int i = 0; i < m; i++)
	{
		int rr, cc, s, d, z;
		cin >> rr >> cc >> s >> d >> z;
		map[rr-1][cc-1] = { s,d,z };
		shk.push({ rr-1, cc-1 });
	}
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < r; j++)
		{
			if (map[j][i].z > 0)
			{
				ans += map[j][i].z; // ������
				map[j][i] = { 0,0,0 }; // �������ĭ �ʱ�ȭ
				break;
			}
		}
		int size = shk.size();
		for (int k = 0; k < size; k++) // �� �ִ� ��ġ�� Ž���ϸ�
		{
			gps now = shk.front();
			shk.pop();
			if (map[now.y][now.x].z == 0) // ���� �����ġ�� ����
			{
				continue;
			}
			shark one = map[now.y][now.x];
			int di = map[now.y][now.x].d; // ���� ����� ����
			gps go;
			go.y = now.y + one.s * yy[one.d];
			go.x = now.x + one.s * xx[one.d]; // �ӵ���ŭ �������� �̵�
			if (di == 3 || di == 4) // �¿��̵��϶� �ٲ�������� ����
			{
				if (go.x % (c-1) > 0) // ���� �������� �ε����� �Ѿ���
				{
					if ((go.x / (c - 1)) % 2 == 1) // Ȧ���� �Ѿ����� ���⺯��
					{
						if (di == 3)
						{
							map[now.y][now.x].d = 4;
						}
						else
						{
							map[now.y][now.x].d = 3;
						}
					}
				}
				else // ���� �������� �ε����� �Ѿ���
				{
					if ((go.x / (c - 1)) % 2 == 0) // ¦���� �Ѿ����� ���⺯��
					{
						if (di == 3)
						{
							map[now.y][now.x].d = 4;
						}
						else
						{
							map[now.y][now.x].d = 3;
						}
					}
				}
			}
			else // ���� �̵��϶� �ٲ���� ����
			{
				if (go.y % (r-1) > 0)
				{
					if ((go.y / (r - 1)) % 2 == 1)
					{
						if (di == 1)
						{
							map[now.y][now.x].d = 2;
						}
						else
						{
							map[now.y][now.x].d = 1;
						}
					}
				}
				else 
				{
					if ((go.y / (r - 1)) % 2 == 0)
					{
						if (di == 1)
						{
							map[now.y][now.x].d = 2;
						}
						else
						{
							map[now.y][now.x].d = 1;
						}
					}
				}
			}
			go = turn(go); // �Ѿ�� ��ġ ����
			if (map[now.y][now.x].z < movemap[go.y][go.x].z) 
			{ // �̵��� ��ǥ�� �̹� �̵��ؿ� �� �ְ� �� �� ���� ���� ū��� ��Ƹ���
				map[now.y][now.x] = { 0,0,0 };
				continue;
			}
			movemap[go.y][go.x] = map[now.y][now.x]; // ���� ���� ū ����� ��Ƹ԰� �ڸ�����
			map[now.y][now.x] = { 0,0,0 };
			shk.push(go); // ��� ��ǥ ǥ��
		}
		int sharksize = shk.size();
		for (int k = 0; k < sharksize; k++)
		{ // �̵��ؿ� ������ ������ġ�� ��Ÿ���� �ʿ� �ű�� �̵����� �ʱ�ȭ
			gps moveshark = shk.front();
			shk.pop();
			if (map[moveshark.y][moveshark.x].z != 0)
			{
				continue;
			}
			map[moveshark.y][moveshark.x] = movemap[moveshark.y][moveshark.x];
			movemap[moveshark.y][moveshark.x] = { 0,0,0 };
			shk.push(moveshark);
		}
	}
	cout << ans;

	return 0;
}