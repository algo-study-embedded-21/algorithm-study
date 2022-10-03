#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

using namespace std;

struct gps
{
	int y;
	int x;
};

int r, c, t;
int map[50][50];
vector<gps> air; // 공기청정기의 위치
queue<gps> dust; // 먼지들의 위치

int yy[4] = { 1,-1,0,0 };
int xx[4] = { 0,0,1,-1 };

void aircondition()
{  // 공기청정기 상부 순환
	for (int i = air[0].y - 1; i > 0; i--)
	{
		map[i][0] = map[i - 1][0];
		if (map[i][0] > 0)
		{
			dust.push({ i,0 });
		}
	}
	for (int i = 0; i < c - 1; i++)
	{
		map[0][i] = map[0][i + 1];
		if (map[0][i] > 0)
		{
			dust.push({ 0,i });
		}
	}
	for (int i = 0; i < air[0].y; i++)
	{
		map[i][c - 1] = map[i + 1][c - 1];
		if (map[i][c - 1] > 0)
		{
			dust.push({ i ,c - 1 });
		}
	}
	for (int i = c - 1; i > 1; i--)
	{
		map[air[0].y][i] = map[air[0].y][i - 1];
		if (map[air[0].y][i] > 0)
		{
			dust.push({ air[0].y,i});
		}
	}
	map[air[0].y][1] = 0;
	// 공기청정기 하부 순환
	for (int i = air[1].y + 1; i < r - 1; i++)
	{
		map[i][0] = map[i + 1][0];
		if (map[i][0] > 0)
		{
			dust.push({ i ,0 });
		}
	}
	for (int i = 0; i < c - 1; i++)
	{
		map[r - 1][i] = map[r - 1][i + 1];
		if (map[r - 1][i] > 0)
		{
			dust.push({ r-1,i});
		}
	}
	for (int i = r - 1; i > air[1].y; i--)
	{
		map[i][c - 1] = map[i - 1][c - 1];
		if (map[i][c - 1] > 0)
		{
			dust.push({ i ,c - 1 });
		}
	}
	for (int i = c - 1; i > 1; i--)
	{
		map[air[1].y][i] = map[air[1].y][i - 1];
		if (map[air[1].y][i] > 0)
		{
			dust.push({ air[1].y ,i });
		}
	}
	map[air[1].y][1] = 0;
}

void wind()
{
	int dustmap[50][50] ={0}; // 확산되는 먼지들을 기록할 맵 (확산은 동시에 일어남으로 영향을 주지 않기 위해)
	int visit[50][50] = { 0 };
	int manydust = dust.size(); // 큐에 변동이 있기전 크기만큼만 반복하기 위함 
	queue<gps> plusdust; // 먼지가 확산된 곳들의 위치
	for (int k = 0; k < manydust; k++)
	{
		gps now = dust.front();
		dust.pop();
		if (map[now.y][now.x] == 0) // 먼지가 없는곳은 제외
		{
			continue;
		}
		if (visit[now.y][now.x] > 0) // 이미 확산을 시도한 곳은 제외
		{
			continue;
		}
		dust.push(now);
		visit[now.y][now.x] = 1;
		int minidust = map[now.y][now.x] / 5; // 확산될 먼지의 양
		if (minidust == 0)
		{
			continue; // 확산할 먼지크기가 0이면 제외
		}
		int cnt = 0; // 몇 곳이나 확산되었는지 카운팅
		for (int i = 0; i < 4; i++)
		{
			gps next;
			next.y = now.y + yy[i];
			next.x = now.x + xx[i];
			if (next.y<0 || next.y>r - 1 || next.x<0 || next.x>c - 1)
			{
				continue;
			}
			if (map[next.y][next.x] == -1) // 공기청정로는 확산 X
			{
				continue;
			}
			cnt++;
			if (dustmap[next.y][next.x] == 0) // 확산된적 없는곳이면 위치 저장(중복방지)
			{
				plusdust.push(next);
			}
			dustmap[next.y][next.x] += minidust;
		}
		map[now.y][now.x] -= minidust * cnt; // now로 부터 확산이 끝나면 확산된 먼지만큼 차감
	}
	manydust = plusdust.size(); 
	for (int i = 0; i < manydust; i++)
	{
		gps now = plusdust.front();
		plusdust.pop();
		if (map[now.y][now.x] == 0)
		{
			dust.push(now); // 먼지가 없던 위치라면 갱신
		}
		map[now.y][now.x] += dustmap[now.y][now.x]; // 본 맵에 확산된 먼지 추가
	}
	aircondition(); // 공기청정기 가동
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> r >> c >> t;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			int a;
			cin >> a;
			map[i][j]=a;
			if (a == -1)
			{
				air.push_back({ i,j });
			}
			else if (a != 0)
			{
				dust.push({ i,j });
			}
		}
	}
	for (int i = 0; i < t; i++) // t초동안 반복
	{
		wind();
	}
	int totaldust = 0; // 총 먼지의 양
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (map[i][j] > 0)
			{
				totaldust += map[i][j];
			}
		}
	}
	cout << totaldust;

	return 0;
}
