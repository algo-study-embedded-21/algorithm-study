#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

struct gps { int y, x; };

int n, m;
int map[101][101];  // 벽을 포함한 맵
int visit[101][101]; // 방번호 표시
vector<gps> group; // 벽을 뚫으면 같은방이 되는 번호 모음
vector<gps> wallgps; // 벽 좌표 모음
vector<int> roomsize; // 각 방의 크기
vector<int> wall[16]; // 맵에서 0~15가 갖는 벽의 방향모음

int yy[4] = { 0,-1,0,1 };
int xx[4] = { -1,0,1,0 };

void makewall() // 맵에 번호에 따라 벽 세우기
{
	for (int i = 1; i < 2 * m; i += 2)
	{
		for (int j = 1; j < 2 * n; j += 2)
		{
			if (map[i][j] != 0 && map[i][j] < 100)
			{
				int index = map[i][j];
				for (int k = 0; k < wall[index].size(); k++)
				{
					int d = wall[index][k];
					map[i + yy[d]][j + xx[d]] = 100;
					wallgps.push_back({ i + yy[d],j + xx[d] });
				}
			}
		}
	}
	// 외곽 벽 세우기
	for (int i = 0; i < 2*n; i++)
	{
		map[0][i] = 100;
		map[2 * m][i] = 100;
	}
	for (int i = 0; i < 2 * m; i++)
	{
		map[i][0] = 100;
		map[i][2 * n] = 100;
	} 
	// 꼭짓점 채우기
	for (int i = 0; i <= 2 * m; i += 2)
	{
		for (int j = 0; j <= 2 * n; j += 2)
		{
			map[i][j] = 100;
		}
	}
}

void makeroom(gps st, int num) // bfs로 방번호 표시
{
	roomsize.push_back(1);
	queue<gps> q;
	q.push(st);
	visit[st.y][st.x] = num;
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++)
		{
			gps next = { now.y + yy[d],now.x + xx[d] };
			if (map[next.y][next.x] == 100)continue;
			if (visit[next.y][next.x] > 0)continue;
			visit[next.y][next.x] = num;
			if (map[next.y][next.x] != -1)roomsize[num] += 1; // 벽은 세지 않고 방 사이즈 체크
			q.push(next);
		}
	}
}

void near() // 인접 방번호 묶기
{
	for (int i = 0; i < wallgps.size(); i++) // 모든 벽에 대해서
	{
		gps now = wallgps[i];
		int D=4;
		if (now.y == 0 || now.y == 2 * m || now.x == 0 || now.x == 2 * n)continue; // 외곽벽 제외
		for (int d = 0; d < 2; d++) 
		{
			gps next = { now.y + yy[d],now.x + xx[d] };
			if (map[next.y][next.x] != -1 && map[next.y][next.x] != 100) // 좌,상 중 방이 있는경우 찾기
			{
				D = d;
				break;
			}
		}
		if (D < 4)
		{
			gps next = { now.y + yy[D],now.x + xx[D] };
			int first = visit[next.y][next.x];
			D += 2; // 좌측에 방이 있으면 우측에 방이있고, 위에 방이있으면 아래에 방이있다
			next = { now.y + yy[D],now.x + xx[D] };
			int second = visit[next.y][next.x];
			if (first != second) group.push_back({ first, second }); // 두 방이 같은 방이 아니면 묶기
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	memset(map, -1, sizeof(map));
	roomsize.push_back(0);
	for (int i = 1; i < 2 * m; i += 2)
	{
		for (int j = 1; j < 2 * n; j += 2)
		{
			cin >> map[i][j];
		}
	}
	for (int i = 15; i >= 1; i--) // wall[0~15] 채우기
	{
		int num = i;
		int index = 8;
		int di = 3;
		while (num > 0)
		{
			if (num >= index)
			{
				wall[i].push_back(di);
				num -= index;
			}
			index /= 2;
			di -= 1;
		}
	}
	makewall();
	int num = 1;
	for (int i = 1; i < 2 * m; i += 2) // 모든 방번호 표시
	{
		for (int j = 1; j < 2 * n; j += 2)
		{
			if (visit[i][j] > 0)continue;
			makeroom({ i,j },num);
			num += 1;
		}
	}
	int maxsize = -1;
	for (int i = 0; i < roomsize.size(); i++)
	{
		maxsize = max(maxsize, roomsize[i]); // 방중에 가장 큰 방
	}
	int maxsum = -1;
	near();
	for (int i = 0; i < group.size(); i++)
	{
		maxsum = max(maxsum, (roomsize[group[i].y] + roomsize[group[i].x])); // 그룹중에 가장 큰 그룹
	}
	cout << num - 1 << endl << maxsize << endl << maxsum;

	return 0;
}