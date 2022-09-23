#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 59분 컷!

using namespace std;

struct gps
{
	int x;
	int y;
};

int n, ans;
int maxx = -1, maxy = -1; // 드래곤 커브중 가장 큰 y값과 x값
int map[101][101];
vector<gps> curve; // 드래곤 커브의 모든 좌표 저장

int xx[4] = { 1,0,-1,0 };
int yy[4] = { 0,-1,0,1 };

void dragon(gps st , int d, int g) // 드래곤 커브 만들기
{
	vector<int> direction; // 이번 드래곤커브의 진행 방향
	int gen = 0;
	direction.push_back(d);
	curve.push_back(st);
	maxx = max(st.x, maxx);
	maxy = max(st.y, maxy);
	while (gen < g)
	{
		int size = direction.size();
		for (int i = size-1; i >=0; i--) // 이전 세대 방향중 가장 마지막 방향부터 시작
		{
			int dir = direction[i];
			direction.push_back((dir + 1) % 4); // 이전 세대방향을 시계방향으로 회전
		}
		gen++; // 다음세대로
	}
	for (int i = 0; i < direction.size(); i++)
	{
		gps now = curve[curve.size() - 1]; // 현재 위치(진행중인 드래곤커브의 가장 마지막 위치)
		gps next;
		next.x = now.x + xx[direction[i]];
		next.y = now.y + yy[direction[i]];
		curve.push_back(next);
		maxx = max(next.x, maxx);
		maxy = max(next.y, maxy);
	}
}

void sq() // 사각형 갯수세기
{
	for (int i = 0; i < curve.size(); i++) // 드래곤 커브 전체 맵으로 옮기기
	{
		gps now = curve[i];
		map[now.x][now.y] = 1;
	}
	for (int i = 0; i <= maxx; i++) // 각각 드래곤커브의 최대 좌표내에서 조사
	{
		for (int j = 0; j <= maxy; j++)
		{
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1)
			{
				ans++; // 사각형이 모두 드래곤 커브에 포함되는 경우 +1
			}
		}
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
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		dragon({ x,y }, d, g);
	}
	sq();
	cout << ans;

	return 0;
}