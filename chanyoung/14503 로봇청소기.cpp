#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct gps
{
	int y;
	int x;
};

int n, m;
int r, c, d;
int map[50][50];
int use[50][50];
int cnt = 1; // �����ϴ� �浵 û���ϱ⶧���� 1�� ����
int yy[4] = { 0,1,0,-1 };  // ����(0)�� ���� ���������� ����
int xx[4] = { -1,0,1,0 };  // ��,��,��,�� ������ Ž�� �� ����
int direc[4] = { 1,2,3,0 }; // ������ ����迭 �ε����� ���� �����ִ� ���� ����

void clean(gps st,int direction)
{
	int stop = 0;
	int di = direction;
	if (di == 1)
	{
		di = 3;
	}
	else if (di == 3) // ������ ���� 3 ���� 1�� ����
	{
		di = 1;
	}
	gps go = st;
	while (1)
	{
		for (int i = di; i < di+4; i++) // ���� ������ �������� 4�� �ݺ�
		{
			gps next;
			next.y = go.y + yy[i % 4];
			next.x = go.x + xx[i % 4];
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)
			{
				stop = 1;
				continue;
			}
			if (use[next.y][next.x] == 1)
			{
				stop = 1;
				continue;
			}
			if (map[next.y][next.x] == 1)
			{
				stop = 1;
				continue;
			}
			stop = 0; // û���� ���� �ִٸ� 0 ���ٸ� 1
			go = next;
			use[next.y][next.x] = 1;
			di = direc[ i % 4]; // ������ �������� ���� ���� �ٲ��ֱ�
			cnt++; // û���� ���� ���� ī��Ʈ
			break;
		}
		if (stop == 1) // û���� ���� ������
		{
			gps back;
			back.y = go.y + yy[(di + 1) % 4]; // ��������� �޹����� ���?
			back.x = go.x + xx[(di + 1) % 4];

			if (map[back.y][back.x] == 1) // �ڰ� ���̶�� ��
			{
				return;
			}
			else
			{
				go = back; // ����
				stop = 0; // ������ �������� �ٽ� û�Ұ��ɻ��·� ����
			}
		}

	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	cin >> n >> m;
	cin >> r >> c >> d;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}
	use[r][c] = 1; // �����ϴ¹� ǥ��
	clean({ r,c }, d);
	cout << cnt;
	return 0;
}