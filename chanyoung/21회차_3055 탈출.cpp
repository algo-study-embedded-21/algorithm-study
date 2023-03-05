#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

struct gps { int y, x; };

int r, c;
char map[50][50];
int waterfull[50][50]; // 물이 차오르는 시간
gps D, S;
vector<gps> water; // 최초 주어지는 물의 좌표

int yy[4] = { 0,0,1,-1 };
int xx[4] = { 1,-1,0,0 };

void waterBFS() // 물 채우기
{
	queue<gps> q;
	for (int i = 0; i < water.size(); i++)
	{
		gps w = water[i];
		q.push(w);
		waterfull[w.y][w.x] = 1;
	}
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++)
		{
			gps next = { now.y + yy[d],now.x + xx[d] };
			if (next.y<0 || next.y>r - 1 || next.x<0 || next.x>c - 1) continue;
			if (map[next.y][next.x] == 'D')continue; 
			if (map[next.y][next.x] == 'X')continue;
			if (waterfull[next.y][next.x])continue;
			q.push(next);
			waterfull[next.y][next.x] = waterfull[now.y][now.x] + 1;
		}
	}
}

int BFS() // 고슴도치 이동
{
	queue<gps> q;
	q.push(S);
	int visit[50][50] = { 0 };
	visit[S.y][S.x] = 1;
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++)
		{
			gps next = { now.y + yy[d],now.x + xx[d] };
			if (next.y<0 || next.y>r - 1 || next.x<0 || next.x>c - 1) continue;
			if (map[next.y][next.x] == 'X')continue;
			if (visit[next.y][next.x])continue; // 물이 없는경우 처리해주지 않으면 메모리 초과 발생
			if (map[next.y][next.x] != 'D' && waterfull[next.y][next.x] !=0 && waterfull[next.y][next.x] <= visit[now.y][now.x] + 1)continue; // 도착지가 아닌곳 && 물이 차오를수 있는 곳 && 다음시간 전에 물이 차오른 곳은 무시
			if (map[next.y][next.x] == 'D')// 도착지라면
			{
				visit[next.y][next.x] = visit[now.y][now.x] + 1;
				return visit[next.y][next.x]; // 탐색 종료
			}
			visit[next.y][next.x] = visit[now.y][now.x] + 1;
			q.push(next);
		}
	}
	return visit[D.y][D.x];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> r >> c;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == '*')water.push_back({ i,j });
			else if (map[i][j] == 'D')D = { i,j };
			else if (map[i][j] == 'S')S = { i,j };
		}
	}
	waterBFS();
	int ans = BFS();
	if (ans)cout << ans - 1;
	else cout << "KAKTUS"; // ans가 0이라면 고슴도치가 물보다 빨리 갈수 없다는 뜻

	return 0;
}
