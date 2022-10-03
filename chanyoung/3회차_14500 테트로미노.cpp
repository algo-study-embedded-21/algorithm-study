#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>

using namespace std;

struct gps
{
	int y;
	int x;
};

int n, m;
int map[500][500];
int maxsum = -1;
int score;
int use[500][500];
gps trans[4]; //
vector<gps> path;

int yy[4] = { 0,0,1,-1 };
int xx[4] = { 1,-1,0,0 };

void four(gps st,int level)
{
	if (level == 3) // 시작좌표와 3개를 추가로 골랐다 = 총 4개가 선택되었다
	{
		maxsum = max(maxsum, score);
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		gps nt;
		nt.y = st.y + yy[i];
		nt.x = st.x + xx[i];
		if (nt.y<0 || nt.y>n - 1 || nt.x<0 || nt.x>m - 1)
		{
			continue;
		}
		if (use[nt.y][nt.x] == 1)
		{
			continue;
		}
		use[nt.y][nt.x] = 1;
		score += map[nt.y][nt.x];
		path.push_back(nt);
		four(nt, level + 1);
		path.pop_back();
		score -= map[nt.y][nt.x];
		use[nt.y][nt.x] = 0;
	}
}

void ttsum(int level,int st) // T모양 경우의수 구하기
{
	if (level == 3)
	{
		maxsum = max(maxsum, score);
		return;
	}
	for (int i = st; i < 4; i++)
	{
		gps now = trans[i]; // 현재좌표를 중심으로 하는 T모양 선택 배열
		if (now.y<0 || now.y>n - 1 || now.x<0 || now.x>m - 1)
		{
			continue;
		}
		score += map[now.y][now.x];
		path.push_back(now);
		ttsum(level + 1,i+1);
		path.pop_back();
		score -= map[now.y][now.x];
	}
}

void tt(gps st) // T 모양 선택배열을 구하는 함수
{
	for (int i = 0; i < 4; i++)
	{
		int ty = st.y + yy[i];
		int tx = st.x + xx[i];
		trans[i] = { ty,tx }; 
	}
	score = map[st.y][st.x];
	path.push_back(st);
	ttsum(0,0);
	path.pop_back();
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
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			score = map[i][j];
			use[i][j] = 1;
			path.push_back({ i,j }); 
			four({ i,j }, 0); // 현재 좌표를 기준으로 3개 더 선택하기
			path.pop_back(); 
			use[i][j] = 0;
			tt({ i,j }); // 현재좌표를 중심으로하는 T모양 고르기
		}
	}
	cout << maxsum;
	return 0;
}
