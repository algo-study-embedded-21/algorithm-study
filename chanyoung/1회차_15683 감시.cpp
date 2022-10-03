#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

struct gps {
	int y;
	int x;
};

struct cctvgps
{
	int y;
	int x;
	int num;
};


int n, m;
int office[8][8];
int usecctv[8][8];
int minsee = 2134567890;
vector<cctvgps> cctvs;

void yplus(gps cctv)  // 현재 좌표로 부터 x값유지 y를 키우며 감시영역 표시
{
	for (int i = cctv.y + 1; i < n; i++)
	{
		if (office[i][cctv.x] == 6) // 벽이면 스탑
		{
			break;
		}
		if ((office[i][cctv.x] <= 5 && office[i][cctv.x] >= 1) || office[i][cctv.x] == 10) // cctv이거나 이미 감시한영역이면 무시
		{
			continue;
		}
		office[i][cctv.x] = 10;
	}
}
void yminus(gps cctv) // 현재 좌표로 부터 x값유지 y를 줄이며 감시영역 표시
{
	for (int i = cctv.y - 1; i >= 0; i--)
	{
		if (office[i][cctv.x] == 6)
		{
			break;
		}
		if ((office[i][cctv.x] <= 5 && office[i][cctv.x] >= 1) || office[i][cctv.x] == 10)
		{
			continue;
		}
		office[i][cctv.x] = 10;
	}
}
void xplus(gps cctv) // 현재 좌표로 부터 y값유지 x를 키우며 감시영역 표시
{
	for (int i = cctv.x + 1; i < m; i++)
	{
		if (office[cctv.y][i] == 6)
		{
			break;
		}
		if ((office[cctv.y][i] <= 5 && office[cctv.y][i] >= 1) || office[cctv.y][i] == 10)
		{
			continue;
		}
		office[cctv.y][i] = 10;
	}
}
void xminus(gps cctv)  // 현재 좌표로 부터 y값유지 x를 줄이며 감시영역 표시
{
	for (int i = cctv.x - 1; i >= 0; i--)
	{
		if (office[cctv.y][i] == 6)
		{
			break;
		}
		if ((office[cctv.y][i] <= 5 && office[cctv.y][i] >= 1) || office[cctv.y][i] == 10)
		{
			continue;
		}
		office[cctv.y][i] = 10;
	}
}

void one(gps cctv, int direction) // 1번 cctv인 경우
{
	if (direction == 1)
	{
		xplus(cctv);
	}
	else if (direction == 2)
	{
		xminus(cctv);
	}
	else if (direction == 3)
	{
		yplus(cctv);
	}
	else if (direction == 4)
	{
		yminus(cctv);
	}
}

void two(gps cctv, int direction) // 2번 cctv인 경우
{
	if (direction == 1 || direction ==3)
	{
		yplus(cctv);
		yminus(cctv);
	}
	else if (direction == 2 || direction == 4)
	{
		xplus(cctv);
		xminus(cctv);
	}
}

void three(gps cctv, int direction) // 3번 cctv인 경우
{
	if (direction == 1)
	{
		xplus(cctv);
		yplus(cctv);
	}
	else if (direction == 2)
	{
		xminus(cctv);
		yplus(cctv);
	}
	else if (direction == 3)
	{
		xplus(cctv);
		yminus(cctv);
	}
	else if (direction == 4)
	{
		xminus(cctv);
		yminus(cctv);
	}
}

void four(gps cctv, int direction) // 4번 cctv인 경우
{
	if (direction == 1)
	{
		xplus(cctv);
		yplus(cctv);
		xminus(cctv);
	}
	else if (direction == 2)
	{
		xminus(cctv);
		yplus(cctv);
		yminus(cctv);
	}
	else if (direction == 3)
	{
		xplus(cctv);
		yminus(cctv);
		yplus(cctv);
	}
	else if (direction == 4)
	{
		xminus(cctv);
		yminus(cctv);
		xplus(cctv);
	}
}

void five(gps cctv, int direction) // 5번 cctv인 경우
{
	xplus(cctv);
	xminus(cctv);
	yplus(cctv);
	yminus(cctv);
}

void resetmap(int officesave[8][8]) // 맵을 이전상태로 복구시키는 함수
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			office[i][j] = officesave[i][j];
		}
	}
}

void savemap(int officesave[8][8]) // 현상태의 맵을 저장하는 함수
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			officesave[i][j] = office[i][j];
		}
	}
}

void see(int index)
{
	if (index == cctvs.size()) // 모든 cctv의 감시영역을 표시했다면
	{
		int cnt = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (office[i][j] == 0) // 사각지대를 카운트
				{
					cnt++;
				}
			}
		}
		if (cnt < minsee)
		{
			minsee = cnt;
		}
		return;
	}
	for (int j = 1; j <= 4; j++) // cctv의 direction 최대 4개
	{
		cctvgps now = cctvs[index];
		if (usecctv[now.y][now.x] == 1) // 이미 검토한 cctv는 무시
		{
			continue;
		}
		if (now.num == 1) // 1번 cctv일 경우
		{
			usecctv[now.y][now.x] = 1; // 사용했음을 기록하고
			int officesave[8][8]; // 현재까지의 맵을 기록할 맵2를 만들고
			savemap(officesave); // 맵을 기록하고
			one({ now.y,now.x }, j); //  1번 cctv의 감시영역을 기록
			see(index+1);  // 다음 cctv로 이동
			resetmap(officesave); // 이전 맵으로 초기화하고
			usecctv[now.y][now.x] = 0; // cctv 사용기록 초기화
		}
		else if (now.num == 2)
		{
			usecctv[now.y][now.x] = 1;
			int officesave[8][8];
			savemap(officesave);
			two({ now.y,now.x }, j);
			see(index + 1);
			resetmap(officesave);
			usecctv[now.y][now.x] = 0;
		}
		else if (now.num == 3)
		{
			usecctv[now.y][now.x] = 1;
			int officesave[8][8];
			savemap(officesave);
			three({ now.y,now.x }, j);
			see(index + 1);
			resetmap(officesave);
			usecctv[now.y][now.x] = 0;
		}
		else if (now.num == 4)
		{
			usecctv[now.y][now.x] = 1;
			int officesave[8][8];
			savemap(officesave);
			four({ now.y,now.x }, j);
			see(index + 1);
			resetmap(officesave);
			usecctv[now.y][now.x] = 0;
		}
		else if (now.num == 5)
		{
			usecctv[now.y][now.x] = 1;
			int officesave[8][8];
			savemap(officesave);
			five({ now.y,now.x }, j);
			see(index + 1);
			resetmap(officesave);
			usecctv[now.y][now.x] = 0;
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
		for (int j = 0; j < m; j++)
		{
			cin >> office[i][j];
			if (office[i][j] >= 1 && office[i][j] <= 5) //cctv일 경우
			{
				cctvs.push_back({ i,j,office[i][j]}); // cctv의 좌표와 cctv 넘버를 벡터에 저장
			}
		}
	}
	see(0); // 첫번째 cctv부터 감시영역 검토 시작
	cout << minsee;
	return 0;
}
