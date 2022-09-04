#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
//#include<algorithm>
#include<unordered_map>
//#include<cmath>

using namespace std;

struct shark
{
	int s;
	int d;
	int z;
};

struct gps
{
	int y;
	int x;
};

int r, c, m;
shark map[101][101];
shark movemap[101][101];
int ans;
queue<gps> shk;

int yy[5] = { 0,-1,1,0,0 };
int xx[5] = { 0,0,0,1,-1 }; // 1: 위 2:아래 3: 오른쪽 4: 왼쪽 인덱스 맞춤

gps turn(gps go)
{
	gps t;
	t.y =  r - 1 - abs((abs(go.y % (2 * (r - 1)))) - (r - 1)); //   -| |x%2r| - r| + r   r=r-1
	t.x =  c - 1 - abs((abs(go.x % (2 * (c - 1)))) - (c - 1));
	return t;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> r >> c >> m;
	for (int i = 0; i < m; i++)
	{
		int rr, cc, s, d, z;
		cin >> rr >> cc >> s >> d >> z;
		map[rr-1][cc-1] = { s,d,z };
		shk.push({ rr-1, cc-1 });
	}
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < r; j++)
		{
			if (map[j][i].z > 0)
			{
				ans += map[j][i].z; // 상어잡기
				map[j][i] = { 0,0,0 }; // 상어잡은칸 초기화
				break;
			}
		}
		int size = shk.size();
		for (int k = 0; k < size; k++) // 상어가 있는 위치를 탐색하며
		{
			gps now = shk.front();
			shk.pop();
			if (map[now.y][now.x].z == 0) // 잡힌 상어위치면 무시
			{
				continue;
			}
			shark one = map[now.y][now.x];
			int di = map[now.y][now.x].d; // 본래 상어의 방향
			gps go;
			go.y = now.y + one.s * yy[one.d];
			go.x = now.x + one.s * xx[one.d]; // 속도만큼 방향으로 이동
			if (di == 3 || di == 4) // 좌우이동일때 바뀐방향으로 수정
			{
				if (go.x % (c-1) > 0) // 양의 방향으로 인덱스를 넘어간경우
				{
					if ((go.x / (c - 1)) % 2 == 1) // 홀수번 넘었으면 방향변경
					{
						if (di == 3)
						{
							map[now.y][now.x].d = 4;
						}
						else
						{
							map[now.y][now.x].d = 3;
						}
					}
				}
				else // 음의 방향으로 인덱스를 넘어간경우
				{
					if ((go.x / (c - 1)) % 2 == 0) // 짝수번 넘었으면 방향변경
					{
						if (di == 3)
						{
							map[now.y][now.x].d = 4;
						}
						else
						{
							map[now.y][now.x].d = 3;
						}
					}
				}
			}
			else // 상하 이동일때 바뀐방향 수정
			{
				if (go.y % (r-1) > 0)
				{
					if ((go.y / (r - 1)) % 2 == 1)
					{
						if (di == 1)
						{
							map[now.y][now.x].d = 2;
						}
						else
						{
							map[now.y][now.x].d = 1;
						}
					}
				}
				else 
				{
					if ((go.y / (r - 1)) % 2 == 0)
					{
						if (di == 1)
						{
							map[now.y][now.x].d = 2;
						}
						else
						{
							map[now.y][now.x].d = 1;
						}
					}
				}
			}
			go = turn(go); // 넘어가는 위치 수정
			if (map[now.y][now.x].z < movemap[go.y][go.x].z) 
			{ // 이동할 좌표에 이미 이동해온 상어가 있고 그 상어가 현재 상어보다 큰경우 잡아먹힘
				map[now.y][now.x] = { 0,0,0 };
				continue;
			}
			movemap[go.y][go.x] = map[now.y][now.x]; // 내가 제일 큰 상어라면 잡아먹고 자리차지
			map[now.y][now.x] = { 0,0,0 };
			shk.push(go); // 상어 좌표 표시
		}
		int sharksize = shk.size();
		for (int k = 0; k < sharksize; k++)
		{ // 이동해온 상어들을 현재위치를 나타내는 맵에 옮기고 이동맵은 초기화
			gps moveshark = shk.front();
			shk.pop();
			if (map[moveshark.y][moveshark.x].z != 0)
			{
				continue;
			}
			map[moveshark.y][moveshark.x] = movemap[moveshark.y][moveshark.x];
			movemap[moveshark.y][moveshark.x] = { 0,0,0 };
			shk.push(moveshark);
		}
	}
	cout << ans;

	return 0;
}