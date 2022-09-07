#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

using namespace std;

// 유니온 파인드가 적합해보이지만 BFS로...

struct gps
{
	int y;
	int x;
};

int n, m;
int map[20][20];
int visit[20][20];
vector<gps> capgroup; // 가장큰 그룹의 블록들
gps cap = { -1,-1 }; // 가장 큰 그룹의 기준블록
int trytime = 1;
int rainbowtime = -1;
int score;
int maxbow = -1;
int yy[4] = { 1,-1,0,0 };
int xx[4] = { 0,0,1,-1 };

void group(gps st) // 그룹화 하기
{
	gps block = st; //기준블록
	vector<gps> thisgroup; // 지금 그룹화 되는 그룹
	queue<gps> q;
	q.push(st);
	thisgroup.push_back(st);
	visit[st.y][st.x] = trytime; 
	int color = map[st.y][st.x]; // 그룹화 하고자하는 색
	int rainbow = 0; // 이번 그룹에 포함되는 무지개 블록수
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
			if (visit[next.y][next.x] == trytime) // 이번 시도에 다녀간곳은 제외
			{
				continue;
			}
			if (map[next.y][next.x] != color && map[next.y][next.x] != 0) // 같은 컬러 또는 무지개가 아니면 제외
			{
				continue;
			}
			if (map[next.y][next.x] == 0)
			{
				if (visit[next.y][next.x] == rainbowtime) // 무지개중 이미 이 그룹에 속한 블록은 제외
				{
					continue;
				}
				rainbow++;
				visit[next.y][next.x] = rainbowtime; // 처음 이 그룹에 포함되는 무지개 블록
			}
			else
			{
				visit[next.y][next.x] = trytime; // 같은 컬러의 블록
			}
			thisgroup.push_back(next);
			q.push(next);
		}
	}
	rainbowtime--; // 다음 그룹화에서 이번그룹화에 썼던 무지개블록을 사용할수 있도록
	if (thisgroup.size() > capgroup.size()) // 이 그룹이 지금까지의 그룹중에 가장 큰경우
	{
		capgroup.clear();
		capgroup = thisgroup;
		cap = block;
		maxbow = rainbow;
	}
	else if (thisgroup.size() == capgroup.size())
	{
		if (maxbow < rainbow) // 그룹 사이즈는 같지만 무지개가 많은경우
		{
			capgroup.clear();
			capgroup = thisgroup;
			cap = block;
			maxbow = rainbow;
		}
		else if (maxbow == rainbow) // 그룹,무지개 같은 경우 기준블록 비교
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

void fall(gps st) // 중력파트
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

void turn() // 회전파트
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
				if (visit[i][j] == trytime) // 그룹화된 블록은 무시
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
		trytime++; // 맵 전체 그룹화가 끝나면 다음 타임때 vist을 초기화 하지 않고 사용하기 위해
		if (capgroup.size() < 2)
		{
			break; // 가장 큰 그룹이 2보다 작다면 오토플레이 종료
		}
		score += pow(capgroup.size(), 2);
		for (int i = 0; i < capgroup.size(); i++)
		{
			gps b = capgroup[i];
			map[b.y][b.x] = 6; // 선택된 블록을 모두 제거 (=6)
		}
		capgroup.clear(); // 초기화
		cap = { -1,-1 };
		maxbow = -1;
		for (int i = n - 2; i >= 0; i--) // 중력은 밑에서부터 작용하고 맨밑줄은 시행할 필요가 없다
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