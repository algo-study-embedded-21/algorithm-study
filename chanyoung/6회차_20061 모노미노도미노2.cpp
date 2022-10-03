#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 1시간 구현끝 , 예제 일부 맞춤
// 1시간 40분 예제 전체 맞춤
// 1시간 58분 완료

using namespace std;

struct gps
{
	int y;
	int x;
};

int n;
int map[10][10];
int score;

int yy[4] = { 0,0,0,1 };
int xx[4] = { 0,0,1,0 };

void put(int t, gps st) //블럭놓기
{
	gps stt; // 모양에 따른 추가 블록
	stt.y = st.y + yy[t];
	stt.x = st.x + xx[t];
	gps blue = st;
	gps bluee = stt;
	while (map[blue.y][blue.x] == 0 && map[bluee.y][bluee.x] == 0) // 둘중하나라도 걸리는 지점이 생길때까지
	{
		if (blue.x + 1 > 9 || bluee.x + 1 > 9) // 범위 바깥이면 스탑
		{
			blue.x += 1;
			bluee.x += 1;
			break;
		}
		blue.x += 1;
		bluee.x += 1;
	}
	map[blue.y][blue.x-1] = 1;
	map[bluee.y][bluee.x-1] = 1;
	gps green = st;
	gps greenn = stt;
	while (map[green.y][green.x] == 0 && map[greenn.y][greenn.x] == 0)
	{
		if (green.y + 1 > 9 || greenn.y + 1 > 9)
		{
			green.y += 1;
			greenn.y += 1;
			break;
		}
		green.y += 1;
		greenn.y += 1;
	}
	map[green.y-1][green.x] = 1;
	map[greenn.y-1][greenn.x] = 1;
}

void light() // 연한색 구역
{
	int lightblue = 0; // 블럭이 있는 연파랑 열의 갯수
	int lightgreen = 0; // 블럭이 있는 연초록 행의 갯수
	for (int j = 4; j < 6; j++) // 연파랑 조사
	{
		for (int i = 0; i < 4; i++)
		{
			if (map[i][j] == 1)
			{
				lightblue++;
				break;
			}
		}
	}
	for (int i = 4; i < 6; i++) // 연초록 조사
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 1)
			{
				lightgreen++;
				break;
			}
		}
	}
	for (int j = 9; j > 3; j--) // 연파랑 열수만큼 옮기기
	{
		for (int i = 0; i < 4; i++)
		{
			map[i][j] = map[i][j - lightblue];
		}
	}
	for (int i = 9; i > 3; i--) // 연초록 행수만큼 옮기기
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = map[i - lightgreen][j];
		}
	}
}

void bomb() // 터뜨리기
{
	int gcol[4] = { 0 };
	int braw[4] = { 0 };
	for (int i = 6; i < 10; i++) // 초록색 조사
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 1)
			{
				gcol[i - 6] += 1;
			}
		}
	}
	for (int i = 0; i < 4; i++) // 파란색 조사
	{
		for (int j = 6; j < 10; j++)
		{
			if (map[i][j] == 1)
			{
				braw[j - 6] += 1;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (gcol[i] == 4) // 초록색 터뜨리기
		{
			for (int j = i + 6; j > 3; j--)
			{
				for (int k = 0; k < 4; k++)
				{
					map[j][k] = map[j - 1][k];
				}
			}
			score += 1;
		}
		if (braw[i] == 4) // 파란색 터뜨리기
		{
			for (int j = i + 6; j > 3; j--)
			{
				for (int k = 0; k < 4; k++)
				{
					map[k][j] = map[k][j-1];
				}
			}
			score += 1;
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
		int t, y, x;
		cin >> t >> y >> x;
		put(t, { y,x });
		bomb(); // 터뜨리기가 연한칸 보다 먼저 연산
		light();
	}
	int block = 0;
	for (int i = 0; i < 4; i++) // 파란칸 갯수 세기
	{
		for (int j = 6; j < 10; j++)
		{
			block += map[i][j];
		}
	}
	for (int i = 6; i < 10; i++) // 초록칸 갯수 세기
	{
		for (int j = 0; j < 4; j++)
		{
			block += map[i][j];
		}
	}
	cout << score << "\n" << block;

	return 0;
}
