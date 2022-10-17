#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>

// 31분 컷!

using namespace std;

struct gps { int y, x; };

int n, m;
int map[50][50];
vector<gps> nonvirus;
vector<gps> active;
int ans = 2134567890;

int yy[4] = { 0,0,-1,1 };
int xx[4] = { 1,-1,0,0 };

int fill()
{
	int visit[50][50] = { 0 };
	queue<gps> q;

	for (int i = 0; i < active.size(); i++) // 동시에 퍼트리기 위해 바이러스를 전부 넣어두고 시작!
	{
		gps st = active[i];
		visit[st.y][st.x] = 1;
		q.push(st);
	}
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++)
		{
			gps next = { now.y + yy[d],now.x + xx[d] };
			if (next.y > n - 1 || next.y<0 || next.x>n - 1 || next.x < 0)continue;
			if (visit[next.y][next.x] > 0)continue;
			if (map[next.y][next.x] == 1)continue;
			visit[next.y][next.x] = visit[now.y][now.x] + 1;
			q.push(next);
		}
	}
	int result = -1; // 빈칸이 없는경우 -1 반환
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 0 && visit[i][j] == 0) return -2; // 빈칸을 다 못채운경우 -2 반환
			else if (map[i][j] == 0) result = max(result, visit[i][j] - 1);
		}
	}
	return result;
}

void putvi(int level, int st)
{
	if (level == m)
	{
		int result = fill();
		if (result != -2) ans = min(result, ans);
		return;
	}
	for (int i = st; i < nonvirus.size(); i++)
	{
		gps now = nonvirus[i];
		active.push_back(now);
		putvi(level + 1, i + 1);
		active.pop_back();
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) nonvirus.push_back({ i,j });
		}
	}
	putvi(0, 0);
	if (ans > 3000)ans = -1;
	else if (ans == -1)ans = 0; // 빈칸이 없는경우 0초로 간주
	cout << ans;

	return 0;
}