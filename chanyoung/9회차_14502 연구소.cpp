#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>

// 36ºÐ ÄÆ!

using namespace std;

struct gps { int y; int x; };

int n, m;
int map[8][8];
vector<gps> virus;
vector<gps> zero;
int ans = -1;

int yy[4] = { -1,1,0,0 };
int xx[4] = { 0,0,-1,1 };

int fill()
{
	int visit[8][8] = { 0 };
	int cnt = 0;
	for (int i = 0; i < virus.size(); i++)
	{
		gps st= virus[i];
		visit[st.y][st.x] = 1;
		queue<gps> q;
		q.push(st);
		while (!q.empty())
		{
			gps now = q.front();
			q.pop();
			for (int j = 0; j < 4; j++)
			{
				gps nt = { now.y + yy[j],now.x + xx[j] };
				if (nt.y > n - 1 || nt.y<0 || nt.x>m - 1 || nt.x < 0)continue;
				if (map[nt.y][nt.x] == 1 || map[nt.y][nt.x] == 2)continue;
				if (visit[nt.y][nt.x] == 1)continue;
				visit[nt.y][nt.x] = 1;
				q.push(nt);
			}
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (map[i][j] == 0 && visit[i][j] == 0) cnt++;
		}
	}
	return cnt;
}

void wall(int level,int st)
{
	if (level == 3)
	{
		ans = max(ans, fill());
		return; 
	}
	for (int i = st; i < zero.size(); i++)
	{
		gps now = zero[i];
		map[now.y][now.x] = 1;
		wall(level + 1, i+1);
		map[now.y][now.x] = 0;
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
			cin >> map[i][j];
			if (map[i][j] == 2)virus.push_back({ i,j });
			else if (map[i][j] == 0)zero.push_back({ i,j });
		}
	}
	wall(0, 0);
	cout << ans;

	return 0;
}