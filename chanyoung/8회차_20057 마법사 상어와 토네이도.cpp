#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 45분 예제 1 맞춤

using namespace std;

struct gps { int y; int x; };

int n;
int map[500][500];

int yy[4][10] = {    // 모래의 방향배열 [방향][%] ==> [왼,아,오,위][1,2,7,10,5,a] 순서
	{ -1,1,-2,2,-1,1,-1,1,0,0},
	{0,0,1,1,1,1,2,2,3,2},
	{-1,1,-2,2,-1,1,-1,1,0,0},
	{0,0,-1,-1,-1,-1,-2,-2,-3,-2} 
};
int xx[4][10] = {
	{0,0,-1,-1,-1,-1,-2,-2,-3,-2},
	{-1,1,-2,2,-1,1,-1,1,0,0},
	{0,0,1,1,1,1,2,2,3,2},
	{-1,1,-2,2,-1,1,-1,1,0,0}
};

int yyy[4] = { 0,1,0,-1 }; // 토네이도의 방향배열
int xxx[4] = { -1,0,1,0 };

int per[9] = { 1,1,2,2,7,7,10,10,5 };// 모래 방향배열에 따른 퍼센트 부여

void dust(gps now, int i) // 모래 날리기
{
	gps ddust = { now.y + yyy[i] ,now.x + xxx[i] }; // 이동한 토네이도의 위치
	if (ddust.y > n - 1 || ddust.y<0 || ddust.x>n - 1 || ddust.x < 0)
	{
		return;
	}
	long long Ndust = map[ddust.y][ddust.x]; // 이동할 위치의 모래 총량

	long long godust = 0;
	
	for (int k = 0; k < 10; k++)
	{
		gps next = { now.y + yy[i][k],now.x + xx[i][k] };
		if (k != 9)
		{
			godust += (Ndust * per[k]) / 100; // 맵 바깥으로 나가는거 포함한 이동하는 모래의 총량
		}
		if (next.y > n-1 || next.y<0 || next.x>n-1 || next.x < 0)
		{
			continue;
		}
		if (k == 9)
		{
			map[next.y][next.x] += Ndust - godust; // a 위치는 이동한 모래를 뺀 나머지가 다 이동
			continue;
		}
		map[next.y][next.x] += Ndust * per[k] / 100;
	}
	map[ddust.y][ddust.x] = 0;
}

void storm()
{
	gps mid = { n / 2 ,n / 2  }; // 중앙시작
	gps now = mid;
	int dis = 1; // 한방향으로 이동하는 길이
	int flag = 0;
	while (1)
	{
		for (int i = 0; i < 2; i++) // 왼쪽 , 아래쪽 방향이 같은 dis만큼 이동
		{
			int go = 0;
			while (go < dis)
			{
				dust(now, i);
				now = { now.y + yyy[i],now.x + xxx[i] };
				if (now.y > n - 1 || now.y<0 || now.x>n - 1 || now.x < 0)
				{
					flag = 1;
					break;
				}
				go++;
			}
			if (flag)
			{
				break;
			}
		}
		if (flag)
		{
			break;
		}
		dis++; // 오른쪽, 위쪽 이동이 왼쪽, 아래쪽 이동보다 1만큼 더 이동한다
		for (int i = 2; i < 4; i++) // 오른쪽 , 위쪽 방향이 같은 dis만큼 이동
		{
			int go = 0;
			while (go < dis)
			{
				dust(now, i);
				now = { now.y + yyy[i],now.x + xxx[i] };
				if (now.y > n - 1 || now.y<0 || now.x>n - 1 || now.x < 0)
				{
					flag = 1;
					break;
				}
				go++;
			}
			if (flag)
			{
				break;
			}
		}
		if (flag)
		{
			break;
		}
		dis++;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	long long tdust = 0;
	for (int i = 0; i <n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			tdust += map[i][j]; // 초기 모래 총량
		}
	}
	storm();
	long long ldust = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <n; j++)
		{
			ldust += map[i][j]; // 남은 모래 총량
		}
	}
	cout << tdust - ldust;

	return 0;
}