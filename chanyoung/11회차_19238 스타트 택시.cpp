#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
using namespace std;

//48�� ����

struct gps { int y, x; };

int n, m, f;
int map[20][20];
vector<gps> customer; // �մ���ġ
vector<gps> goal; // ������ ��ġ
vector<int> ctog; // �մԿ��� ���������� �Ÿ�
gps taxi; // �ý� ��ǥ
int nowc, dist; // ���� ����� �մ� ��ȣ , ������ �Ÿ�
int complete; // ����Ϸ� ����

int yy[4] = { 0,0,1,-1 };
int xx[4] = { 1,-1,0,0 };

void getd(gps st, int num)
{
	queue<gps> q;
	q.push(st);
	int visit[20][20] = { 0 };
	visit[st.y][st.x] = 1;
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			gps next = { now.y + yy[i],now.x + xx[i] };
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)continue;
			if (visit[next.y][next.x] > 0)continue;
			if (map[next.y][next.x] == 1)continue;
			visit[next.y][next.x] = visit[now.y][now.x] + 1;
			q.push(next);
		}
	}
	if (num >=0) // ctog ���ϱ�
	{
		gps g = goal[num];
		ctog.push_back(visit[g.y][g.x] - 1);
	}
	else // ���� ����� �մ� ���ϱ�
	{
		int mindist = 213456789;
		for (int i = 0; i < customer.size(); i++)
		{
			gps c = customer[i];
			if (c.y == -1 && c.x == -1)continue;
			if (visit[c.y][c.x] - 1 < mindist)
			{
				mindist = visit[c.y][c.x]-1;
				dist = mindist;
				nowc = i;
			}
			else if (visit[c.y][c.x] - 1 == mindist)
			{
				gps b = customer[nowc];
				if (c.y < b.y)
				{
					dist = mindist;
					nowc = i;
				}
				else if (c.y == b.y)
				{
					if (c.x < b.x)
					{
						dist = mindist;
						nowc = i;
					}
				}
			}
		}
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> f;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}
	cin >> taxi.y >> taxi.x;
	taxi.y--;
	taxi.x--;
	int flag = 1;
	for (int i = 0; i < m; i++)
	{
		int x, y, r, c;
		cin >> y >> x >> r >> c;
		customer.push_back({ y-1,x-1 });
		goal.push_back({ r-1,c-1 });
		getd(customer[i], i); // ctog ���ϱ�
		if (ctog[i] == -1)flag = 0; // �մ��� ���������� ������ ���
	}
	while (flag)
	{
		getd(taxi, -1);
		if (dist == -1) // ������ �մ��� �ִ°��
		{
			flag = 0;
			break;
		}
		f -= dist;
		if (f < 0) // ���Ḧ �پ����
		{
			flag = 0;
			break;
		}
		taxi = customer[nowc];
		f -= ctog[nowc];
		if (f < 0) // ���Ḧ �پ����
		{
			flag = 0;
			break;
		}
		taxi = goal[nowc];
		customer[nowc] = { -1,-1 }; // �Ϸ�� �մ� ǥ��
		complete++;
		f += ctog[nowc] * 2;
		if (complete == m)break; // ��� ������ �Ϸ��� ���
	}
	if (flag == 0)cout << "-1";
	else cout << f;
	
	return 0;
}