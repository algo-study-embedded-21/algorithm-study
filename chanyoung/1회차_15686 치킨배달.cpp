#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

struct chicken {
	int y;
	int x;
};

int n, m;
int cost;
int t;
int tsave;
int mincost = 2134567890;
vector<int> use;
vector<chicken> store;  // 치킨집 좌표 저장 벡터
vector<chicken> home;  // 집 좌표 저장 벡터
vector<chicken> storecheck; // 선택된 치킨집 좌표 저장벡터

void bfs(chicken house)
{
	int mindist = 2134567890;
	int dist = 0;
	for (int j = 0; j < storecheck.size(); j++) // 확정된 치킨집을 기준으로
	{
		int xx, yy;
		// y축거리 계산
		if (storecheck[j].y > house.y)
		{
			yy = storecheck[j].y - house.y;
		}
		else
		{
			yy = house.y - storecheck[j].y;
		}
		// x축거리 계산
		if (storecheck[j].x > house.x)
		{
			xx = storecheck[j].x - house.x;
		}
		else
		{
			xx = house.x - storecheck[j].x;
		}
		dist = yy + xx; // y축거리 + x축거리 = 총거리
		if (dist < mindist) // 최소거리 = 치킨거리
		{
			mindist = dist;
		}
	}
	cost = cost + mindist;  // 각 집의 치킨거리 누적합
}

void dfs(int s) // m개의 치킨집을 고르는 모든 경우의수
{
	if (s == m) // m개의 치킨집을 골랐다면 계산
	{
		cost = 0;
		for (int i = 0; i < home.size(); i++)
		{
			// m개의 치킨집 선택후 치킨거리 계산
			bfs(home[i]);
		}
		if (cost < mincost)
		{  // 이전의 치킨거리보다 작다면 저장
			mincost = cost;
		}
		return;
	}
	for (int i = t; i < store.size(); i++)
	{
		if (use[i] == 1) // 이미 선택한 치킨집이라면 무시
		{
			continue;
		}
		storecheck.push_back({ store[i].y,store[i].x }); // 선택된 치킨집 좌표 저장
		use[i] = 1;
		tsave = t;
		t = i;
		dfs(s + 1);
		t = tsave;
		use[i] = 0;
		storecheck.pop_back();
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			int a;
			cin >> a; // 맵을 입력 받음
			if (a == 2)
			{
				// 치킨집 좌표저장
				store.push_back({ i,j });
				use.push_back(0);  // 치킨집의 총 수만큼 use 벡터 공간 확보
			}
			if (a == 1)
			{
				// 집들의 좌표 저장
				home.push_back({ i,j });
			}
		}
	}

	dfs(0);
	cout << mincost;

	return 0;
}
