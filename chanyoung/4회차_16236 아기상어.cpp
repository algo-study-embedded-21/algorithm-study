#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct gps {
	int y;
	int x;
};

bool cmp(gps l, gps r)
{
	if (l.y < r.y)
	{
		return true;
	}
	if (l.y > r.y)
	{
		return false;
	}
	if (l.x < r.x)
	{
		return true;
	}
	if (l.x > r.x)
	{
		return false;
	}
	return false;
}

int n;
int map[20][20];
vector<gps> aqua;
int body = 2;
gps shark;
int totaltime;
int cnt;

int yy[4] = { 1,0,0,-1 }; // 최대한 위쪽부터
int xx[4] = { 0,-1,1,0 }; // 최대한 왼쪽부터

int eat(gps st)
{
	vector<gps> fish; // 몸크기 보다 작은 물고기들 보관
	vector<gps> catchfish; // 최소거리 물고기들중 도달할수 있는 물고기들만 보관
	for (int i = 0; i < aqua.size(); i++)
	{
		gps g = aqua[i];
		if (map[g.y][g.x] < body && map[g.y][g.x] != 0 && map[g.y][g.x]!=9)  // map[g.y][g.x]!=9 없어서 계속틀렸다..... ㅠ
		{
			fish.push_back({ g.y,g.x }); // 먹을수 있는 물고기 위치 저장
		}
	}
	if (fish.size() == 0) // 먹을수 있는 물고기가 없다면 종료
	{
		return 0;
	}
	int mindist = 2134567890;
	int use[20][20] = { 0 };
	int hungry = 0;
	queue<gps> q;
	q.push(st);
	use[st.y][st.x] = 1;
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int i = 0; i < fish.size(); i++)
		{
			gps fishup = fish[i];
			if (fishup.y == now.y && fishup.x == now.x) // 지금의 위치가 먹을수 있는 물고기 위치중 하나라면
			{
				if (use[now.y][now.x] <= mindist) // 그중 가장 가까운 물고기라면
				{
					mindist = use[now.y][now.x];
					catchfish.push_back({ now.y,now.x }); // 최종 후보 물고기 등록
				}
				else
				{
					hungry = 1; // 물고기가 있는 위치이지만 더 가까운물고기가 있는경우 탐색 중단
				}
				break;
			}
		}
		if (hungry == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				gps next;
				next.y = now.y + yy[i];
				next.x = now.x + xx[i];
				if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)
				{
					continue;
				}
				if (map[next.y][next.x] > body) // 몸집보다 큰 물고기는 못지나간다
				{
					continue;
				}
				if (use[next.y][next.x] > 0)
				{
					continue;
				}
				q.push(next);
				use[next.y][next.x] = use[now.y][now.x] + 1; // 물고기까지의 거리 저장
			}
		}
		else
		{
			break;
		}
	}
	if (catchfish.size() > 0) // 최종후보가 있다면
	{
		sort(catchfish.begin(), catchfish.end(), cmp); // 조건에맞게 정렬
		gps eatfish = catchfish[0]; // 조건에 가장 적합한 물고기
		map[shark.y][shark.x] = 0; // 상어가 있던곳은 빈칸으로
		shark.y = eatfish.y;
		shark.x = eatfish.x;
		map[shark.y][shark.x] = 9; // 먹은 물고기 칸으로 이동
		cnt++; // 먹은 물고기의 수 증가
		if (cnt == body) // 몸집 크기만큼 먹었다면 성장
		{
			body++;
			cnt = 0;
		}
		return use[shark.y][shark.x] - 1; // 물고기까지의 거리 = 걸린 시간
	}
	else
	{
		return 0;  // 먹을수 있는 물고기는 있지만 갈수 없는경우
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a;
			cin >> a;
			map[i][j] = a;
			if (a == 9)
			{
				shark.y = i;
				shark.x = j;
			}
			else if (a > 0)
			{
				aqua.push_back({ i,j });
			}
		}
	}
	int eating = eat({ shark.y,shark.x });
	totaltime = eating;
	while (eating != 0) // 걸린시간이 0이 아닐동안 = 물고기를 먹을수 있는 동안
	{
		eating = eat({ shark.y,shark.x });
		totaltime += eating; // 시간 누적합
	}
	cout << totaltime;
	return 0;
}
