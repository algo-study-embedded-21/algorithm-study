#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>

using namespace std;

struct gps
{
	int y;
	int x;
	int space;
};

bool cmp(gps l, gps r)  // ����� ū�� > ���ȣ ������ > ����ȣ ������
{
	if (l.space > r.space)
	{
		return true;
	}
	if (l.space < r.space)
	{
		return false;
	}
	if (l.y < r.y)
	{
		return true;
	}
	if (l.y > r.y)
	{
		return false;
	}
	if (l.x < r.x)
	{
		return true;
	}
	if (l.x > r.x)
	{
		return false;
	}
	return false;
}

int n;
int map[20][20]; // �¼�ǥ
vector<int> love[401]; // �� �л��� �����ϴ� �л� ����
vector<gps> chair[401]; // �ֺ��� �����ϴ� �л��� ���� ���� ��ġ'��' ����
vector<int> line; // �¼��� �� �л� ���� ����

void school(int st)
{
	int maxlike = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] != 0)
			{
				continue; // �̹� ������ �ɾ��ִ��¼� ���
			}
			int yc[4] = { -1,0,0,1 };
			int xc[4] = { 0,-1,1,0 };
			int like = 0; // �ֺ��� ��ȣ�ϴ� �л� ��
			int spacecnt = 0; // �ֺ��� ����� ��
			for (int k = 0; k < 4; k++)
			{
				int yy = i + yc[k];
				int xx = j + xc[k];
				if (yy<0 || yy>n - 1 || xx<0 || xx>n - 1)
				{
					continue;
				}
				for (int a = 0; a < 4; a++)
				{
					if (map[yy][xx] == love[st][a]) // �αٿ� ��ȣ�ϴ� �л��� �ִ°��
					{
						like++;
					}
				}
				if (map[yy][xx] == 0) // �αٿ� ���ڸ��� �ִ°��
				{
					spacecnt++;
				}
			}
			if (maxlike == like) // �����ϴ� �л����� �ִ�ġ�� ������
			{
				chair[st].push_back({ i,j,spacecnt }); // �ĺ� ��ġ �߰�
			}
			if (maxlike < like) // �ִ�ġ�� ����������
			{
				maxlike = like;
				vector<gps> newchair; 
				chair[st] = newchair; // ���������� �ĺ����� �����
				chair[st].push_back({ i,j,spacecnt }); // �ĺ� ��ġ�� ���
			}
		}
	}
	sort(chair[st].begin(), chair[st].end(), cmp); // ���ǿ� �°� �����Ͽ�
	map[chair[st][0].y][chair[st][0].x] =  st; // ���� ������ �ĺ� ��ġ�� ����
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	int student = n * n;
	for (int i = 1; i <= student; i++) 
	{
		int st, a, b, c, d;
		cin >> st >> a >> b >> c >> d;
		line.push_back(st);  // ���� ����
		// ��������
		love[st].push_back(a);  
		love[st].push_back(b);
		love[st].push_back(c);
		love[st].push_back(d);
	}
	for (int i = 0; i < student; i++)
	{
		school(line[i]); // ��� �л� ����
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int st = map[i][j];
			int yc[4] = { -1,0,0,1 };
			int xc[4] = { 0,-1,1,0 };
			int like = 0;
			for (int k = 0; k < 4; k++)
			{
				int yy = i + yc[k];
				int xx = j + xc[k];
				if (yy<0 || yy>n - 1 || xx<0 || xx>n - 1)
				{
					continue;
				}
				for (int a = 0; a < 4; a++)
				{
					if (map[yy][xx] == love[st][a])
					{
						
						like++;
					}
				}
			}
			if (like > 0) // ������ �ڸ� �ֺ��� ��ȣ�ϴ� �л��� �ִ°��
			{
				int score = 1;
				for (int a = 1; a < like; a++)
				{
					score = score * 10; // 1�϶� 1�� 2�϶� 10�� 3�϶� 100�� 4�϶� 1000��
				}
				ans += score;
			}
		}
	}
	cout << ans;
	return 0;
}