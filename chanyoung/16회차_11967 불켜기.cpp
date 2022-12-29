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

int go(gps st) // st위치가 갈수 있는 곳인지 체크
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
		for (int d = 0; d < 4; d++)// now를 갈수있게되면서 갈수있게된 주변 위치 탐색
		{
			gps next = { now.y + yy[d],now.x + xx[d] };
			if (next.y<1 || next.y>n || next.x<1 || next.x>n)continue;
			if (light[next.y][next.x] == 1)
			{
				light[next.y][next.x] = 2; // 갈수 있다고 표시
				q.push(next);
			}
		}
		for (int i = 0; i < map[now.y][now.x].size(); i++) 
		{
			gps next = map[now.y][now.x][i]; // now에서 켤수 있는 방들
			if (light[next.y][next.x] == 2) continue; // 이미 가본곳은 제외
			if (light[next.y][next.x] == 0)cnt++; // 지금 처음 켜지는거라면 갯수 체크
			light[next.y][next.x] = 1; // 불만 켜두기
			if (go(next)) // 갈수 있는곳이라면
			{
				light[next.y][next.x] = 2; // 갈수 있다고 표시
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