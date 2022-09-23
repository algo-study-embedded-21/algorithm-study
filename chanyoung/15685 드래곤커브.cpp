#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 59�� ��!

using namespace std;

struct gps
{
	int x;
	int y;
};

int n, ans;
int maxx = -1, maxy = -1; // �巡�� Ŀ���� ���� ū y���� x��
int map[101][101];
vector<gps> curve; // �巡�� Ŀ���� ��� ��ǥ ����

int xx[4] = { 1,0,-1,0 };
int yy[4] = { 0,-1,0,1 };

void dragon(gps st , int d, int g) // �巡�� Ŀ�� �����
{
	vector<int> direction; // �̹� �巡��Ŀ���� ���� ����
	int gen = 0;
	direction.push_back(d);
	curve.push_back(st);
	maxx = max(st.x, maxx);
	maxy = max(st.y, maxy);
	while (gen < g)
	{
		int size = direction.size();
		for (int i = size-1; i >=0; i--) // ���� ���� ������ ���� ������ ������� ����
		{
			int dir = direction[i];
			direction.push_back((dir + 1) % 4); // ���� ��������� �ð�������� ȸ��
		}
		gen++; // ���������
	}
	for (int i = 0; i < direction.size(); i++)
	{
		gps now = curve[curve.size() - 1]; // ���� ��ġ(�������� �巡��Ŀ���� ���� ������ ��ġ)
		gps next;
		next.x = now.x + xx[direction[i]];
		next.y = now.y + yy[direction[i]];
		curve.push_back(next);
		maxx = max(next.x, maxx);
		maxy = max(next.y, maxy);
	}
}

void sq() // �簢�� ��������
{
	for (int i = 0; i < curve.size(); i++) // �巡�� Ŀ�� ��ü ������ �ű��
	{
		gps now = curve[i];
		map[now.x][now.y] = 1;
	}
	for (int i = 0; i <= maxx; i++) // ���� �巡��Ŀ���� �ִ� ��ǥ������ ����
	{
		for (int j = 0; j <= maxy; j++)
		{
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1)
			{
				ans++; // �簢���� ��� �巡�� Ŀ�꿡 ���ԵǴ� ��� +1
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		dragon({ x,y }, d, g);
	}
	sq();
	cout << ans;

	return 0;
}