#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

using namespace std;

// ���Ͽ� ���ε尡 �����غ������� BFS��...

struct gps
{
	int y;
	int x;
};

int n, m;
int map[20][20];
int visit[20][20];
vector<gps> capgroup; // ����ū �׷��� ��ϵ�
gps cap = { -1,-1 }; // ���� ū �׷��� ���غ��
int trytime = 1;
int rainbowtime = -1;
int score;
int maxbow = -1;
int yy[4] = { 1,-1,0,0 };
int xx[4] = { 0,0,1,-1 };

void group(gps st) // �׷�ȭ �ϱ�
{
	gps block = st; //���غ��
	vector<gps> thisgroup; // ���� �׷�ȭ �Ǵ� �׷�
	queue<gps> q;
	q.push(st);
	thisgroup.push_back(st);
	visit[st.y][st.x] = trytime; 
	int color = map[st.y][st.x]; // �׷�ȭ �ϰ����ϴ� ��
	int rainbow = 0; // �̹� �׷쿡 ���ԵǴ� ������ ��ϼ�
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			gps next;
			next.y = now.y + yy[i];
			next.x = now.x + xx[i];
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)
			{
				continue;
			}
			if (visit[next.y][next.x] == trytime) // �̹� �õ��� �ٳణ���� ����
			{
				continue;
			}
			if (map[next.y][next.x] != color && map[next.y][next.x] != 0) // ���� �÷� �Ǵ� �������� �ƴϸ� ����
			{
				continue;
			}
			if (map[next.y][next.x] == 0)
			{
				if (visit[next.y][next.x] == rainbowtime) // �������� �̹� �� �׷쿡 ���� ����� ����
				{
					continue;
				}
				rainbow++;
				visit[next.y][next.x] = rainbowtime; // ó�� �� �׷쿡 ���ԵǴ� ������ ���
			}
			else
			{
				visit[next.y][next.x] = trytime; // ���� �÷��� ���
			}
			thisgroup.push_back(next);
			q.push(next);
		}
	}
	rainbowtime--; // ���� �׷�ȭ���� �̹��׷�ȭ�� ��� ����������� ����Ҽ� �ֵ���
	if (thisgroup.size() > capgroup.size()) // �� �׷��� ���ݱ����� �׷��߿� ���� ū���
	{
		capgroup.clear();
		capgroup = thisgroup;
		cap = block;
		maxbow = rainbow;
	}
	else if (thisgroup.size() == capgroup.size())
	{
		if (maxbow < rainbow) // �׷� ������� ������ �������� �������
		{
			capgroup.clear();
			capgroup = thisgroup;
			cap = block;
			maxbow = rainbow;
		}
		else if (maxbow == rainbow) // �׷�,������ ���� ��� ���غ�� ��
		{
			if (cap.y < block.y)
			{
				capgroup.clear();
				capgroup = thisgroup;
				cap = block;
				maxbow = rainbow;
			}
			else if (cap.y == block.y)
			{
				if (cap.x < block.x)
				{
					capgroup.clear();
					capgroup = thisgroup;
					cap = block;
					maxbow = rainbow;
				}
			}
		}
	}
}

void fall(gps st) // �߷���Ʈ
{
	int color = map[st.y][st.x];
	map[st.y][st.x] = 6;
	int yyy = st.y;
	while (yyy < n && map[yyy][st.x] == 6)
	{
		yyy++;
	}
	map[yyy - 1][st.x] = color;
}

void turn() // ȸ����Ʈ
{
	int turnmap[20][20];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			turnmap[i][j] = map[j][n - 1 - i];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			map[i][j] = turnmap[i][j];
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
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}
	while (1)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (visit[i][j] == trytime) // �׷�ȭ�� ����� ����
				{
					continue;
				}
				if (map[i][j] == 0 || map[i][j] == -1 || map[i][j] == 6)
				{
					continue;
				}
				group({ i,j });
			}
		}
		trytime++; // �� ��ü �׷�ȭ�� ������ ���� Ÿ�Ӷ� vist�� �ʱ�ȭ ���� �ʰ� ����ϱ� ����
		if (capgroup.size() < 2)
		{
			break; // ���� ū �׷��� 2���� �۴ٸ� �����÷��� ����
		}
		score += pow(capgroup.size(), 2);
		for (int i = 0; i < capgroup.size(); i++)
		{
			gps b = capgroup[i];
			map[b.y][b.x] = 6; // ���õ� ����� ��� ���� (=6)
		}
		capgroup.clear(); // �ʱ�ȭ
		cap = { -1,-1 };
		maxbow = -1;
		for (int i = n - 2; i >= 0; i--) // �߷��� �ؿ������� �ۿ��ϰ� �ǹ����� ������ �ʿ䰡 ����
		{
			for (int j = 0; j < n; j++)
			{
				if (map[i][j] == -1 || map[i][j] == 6)
				{
					continue;
				}
				fall({ i,j });
			}
		}
		turn();
		for (int i = n - 2; i >= 0; i--)
		{
			for (int j = 0; j < n; j++)
			{
				if (map[i][j] == -1 || map[i][j] == 6)
				{
					continue;
				}
				fall({ i,j });
			}
		}
		int ttt = 0;
	}

	cout << score;

	return 0;
}