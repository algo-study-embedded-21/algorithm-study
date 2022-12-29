#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

struct gps { int y, x; };

int n, m;
vector<gps> map[101][101];
int light[101][101];
int cnt = 1;

int yy[4] = { 0,0,1,-1 };
int xx[4] = { -1,1,0,0 };

int go(gps st) // st��ġ�� ���� �ִ� ������ üũ
{
	for (int d = 0; d < 4; d++)
	{
		gps next = { st.y + yy[d],st.x + xx[d] };
		if (next.y<1 || next.y>n || next.x<1 || next.x>n)continue;
		if (light[next.y][next.x] == 2)return 1;
	}
	return 0;
}

void bfs(gps st)
{
	queue<gps> q;
	q.push(st);
	light[st.y][st.x] = 2;
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++)// now�� �����ְԵǸ鼭 �����ְԵ� �ֺ� ��ġ Ž��
		{
			gps next = { now.y + yy[d],now.x + xx[d] };
			if (next.y<1 || next.y>n || next.x<1 || next.x>n)continue;
			if (light[next.y][next.x] == 1)
			{
				light[next.y][next.x] = 2; // ���� �ִٰ� ǥ��
				q.push(next);
			}
		}
		for (int i = 0; i < map[now.y][now.x].size(); i++) 
		{
			gps next = map[now.y][now.x][i]; // now���� �Ӽ� �ִ� ���
			if (light[next.y][next.x] == 2) continue; // �̹� �������� ����
			if (light[next.y][next.x] == 0)cnt++; // ���� ó�� �����°Ŷ�� ���� üũ
			light[next.y][next.x] = 1; // �Ҹ� �ѵα�
			if (go(next)) // ���� �ִ°��̶��
			{
				light[next.y][next.x] = 2; // ���� �ִٰ� ǥ��
				q.push(next);
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
	for (int i = 0; i < m; i++)
	{
		int y, x, a, b;
		cin >> y >> x >> a >> b;
		map[y][x].push_back({ a,b });
	}
	bfs({ 1,1 });
	cout << cnt;

	return 0;
}