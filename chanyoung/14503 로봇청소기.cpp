#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct gps
{
	int y;
	int x;
};

int n, m;
int r, c, d;
int map[50][50];
int use[50][50];
int cnt = 1; // 시작하는 방도 청소하기때문에 1로 시작
int yy[4] = { 0,1,0,-1 };  // 북쪽(0)을 보고 진입했을때 기준
int xx[4] = { -1,0,1,0 };  // 서,남,동,북 순으로 탐색 후 진입
int direc[4] = { 1,2,3,0 }; // 진입한 방향배열 인덱스에 따라 보고있는 방향 변경

void clean(gps st,int direction)
{
	int stop = 0;
	int di = direction;
	if (di == 1)
	{
		di = 3;
	}
	else if (di == 3) // 강제로 동을 3 서를 1로 변경
	{
		di = 1;
	}
	gps go = st;
	while (1)
	{
		for (int i = di; i < di+4; i++) // 현재 방향을 기준으로 4번 반복
		{
			gps next;
			next.y = go.y + yy[i % 4];
			next.x = go.x + xx[i % 4];
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)
			{
				stop = 1;
				continue;
			}
			if (use[next.y][next.x] == 1)
			{
				stop = 1;
				continue;
			}
			if (map[next.y][next.x] == 1)
			{
				stop = 1;
				continue;
			}
			stop = 0; // 청소할 방이 있다면 0 없다면 1
			go = next;
			use[next.y][next.x] = 1;
			di = direc[ i % 4]; // 진입한 방향으로 보는 방향 바꿔주기
			cnt++; // 청소한 방의 갯수 카운트
			break;
		}
		if (stop == 1) // 청소할 방이 없을때
		{
			gps back;
			back.y = go.y + yy[(di + 1) % 4]; // 현재방향의 뒷방향은 어디?
			back.x = go.x + xx[(di + 1) % 4];

			if (map[back.y][back.x] == 1) // 뒤가 벽이라면 끝
			{
				return;
			}
			else
			{
				go = back; // 후진
				stop = 0; // 후진을 했음으로 다시 청소가능상태로 변경
			}
		}

	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	cin >> n >> m;
	cin >> r >> c >> d;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}
	use[r][c] = 1; // 시작하는방 표시
	clean({ r,c }, d);
	cout << cnt;
	return 0;
}