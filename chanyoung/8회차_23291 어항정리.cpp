#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>

// 1 : 36 예제 1~6 정답
// 2 : 06 정답!


using namespace std;

struct gps { int y; int x; };

int n, k;
int map[100][100];
int Ystart = 99; // 현재 어항이 있는 가장 아래 좌표 (고정)
int Yend = 98; // 현재 어항이 있는 가장 위 좌표 +1
int Xstart = 0; // 현재 어항이 있는 가장 왼쪽좌표
int Xend = 1; // 공중부양할 어항중 가장 오른쪽 좌표 +1
int stack = Xend - Xstart; // 바닥줄 위로 쌓일 어행 층수

int yy[2] = { -1,0 };
int xx[2] = { 0,1 };

void level1() // 어항 말아 올리기
{
	while ((Xend + Ystart - Yend) <= n) // 이번에 쌓을 어항이 삐져나가지 않는동안 
	{
		for (int i = Ystart; i > Yend; i--)
		{
			for (int j = Xstart; j < Xend; j++)
			{
				map[Ystart - stack + (j - Xstart)][Xend + (Ystart - i)] = map[i][j];
				map[i][j] = 0;
			}
		}
		Xstart = Xend;
		Xend = Xend + (Ystart - Yend);
		Yend = Ystart - stack - 1;
		stack = Xend - Xstart;
	}
}

void level2() // 물고기 재분배
{
	int move[100][100] = { 0 }; // 동시에 일어나는 사건에 영향을 주지 않기위해 누적 배열 하나 생성
	for (int i = Ystart; i > Yend; i--)
	{
		for (int j = Xstart; j < n; j++)
		{
			if (map[i][j] != 0)
			{
				for (int d = 0; d < 2; d++) // 중복을 피하기 위해 위,오른쪽 방향만 검사
				{
					gps next = { i + yy[d],j + xx[d] };
					if (next.y > 99 || next.y <= Yend || next.x > n - 1 || next.x < Xstart)continue; // 어항이 있는 범위 내
					if (map[next.y][next.x] == 0)continue;
					if (map[i][j] == map[next.y][next.x])continue; // 같은경우 배치할것 없음
					int bigger = max(map[next.y][next.x], map[i][j]);
					int smaller = min(map[next.y][next.x], map[i][j]);
					if (bigger - smaller >= 5)
					{
						int movement = (bigger - smaller) / 5;
						if (map[next.y][next.x] > map[i][j])
						{
							move[next.y][next.x] -= movement;
							move[i][j] += movement;
						}
						else
						{
							move[next.y][next.x] += movement;
							move[i][j] -= movement;
						}
					}
				}
			}
		}
	}
	for (int i = Ystart; i > Yend; i--)
	{
		for (int j = Xstart; j < n; j++)
		{
			if (move[i][j] == 0)continue;
			map[i][j] += move[i][j]; // 누적배열 합산
		}
	}
}

void level3() // 어항 펼치기
{
	int put = 0;
	for (int j = Xstart; j < n; j++) // 2. 가장 왼쪽 어항부터
	{
		for (int i = Ystart; i > Yend; i--) // 1. 가장 아래쪽 어항부터
		{
			if (map[i][j] == 0)continue;
			map[99][put] = map[i][j]; // 제일 왼쪽부터 채워넣기
			if (i != 99)map[i][j] = 0;
			put++;
		}
	}
	Yend = 98; // 초기값으로 리셋
	Xstart = 0;
	Xend = 1;
	stack = Xend - Xstart;
}

void level4() // 반씩 잘라 올리기
{
	int N = n / 2; // 첫 반
	for (int j = 0; j < N; j++)
	{
		map[98][n-1 - j] = map[99][j]; // 180도 회전하여 올리기 >> 제일 오른쪽부터 채워넣기
		map[99][j] = 0;
	}
	int NN = n - (N / 2); // 반의 반 좌표
	for (int i = 99; i >= 98; i--)// 두개의 층을
	{
		for (int j = N; j < NN; j++)
		{
			map[97-(i-98)][n - 1 - (j - N)] = map[i][j];
			map[i][j] = 0;
		}
	}
	Yend = 95; // 4개층높이로 쌓임
	Xstart = NN; // 반의 반 좌표부터
	Xend = n; // 끝까지 존재
}

int check() // 가장 많은 물고기와 가장 적은 물고기의 차이 반환
{
	int maxfish = -1;
	int minfish = 10001;
	for (int i = 0; i < n; i++)
	{
		maxfish = max(maxfish, map[99][i]);
		minfish = min(minfish, map[99][i]);
	}
	return maxfish - minfish;
}

int pot() // 조건을 만족하는 정리횟수 반환
{
	int cnt = 0;
	int fish = check();
	while (fish > k) // 목표값보다 큰동안
	{
		int m = 10001;
		vector<gps> minfish; // 가장 적은 물고기가 있는 어항들의 위치 저장
		for (int i = 0; i < n; i++)
		{
			if (map[99][i] < m)
			{
				minfish.clear(); // 갱신
				minfish.push_back({ 99,i });
				m = map[99][i];
			}
			else if (map[99][i] == m) minfish.push_back({ 99,i }); // 추가
		}
		for (int i = 0; i < minfish.size(); i++)
		{
			gps fish = minfish[i];
			map[fish.y][fish.x] += 1; // 가장 적은양의 어항들 물고기 +1
		}
		level1();
		level2();
		level3();
		level4();
		level2();
		level3();
		cnt++; // +1회
		fish = check();
	}
	return cnt;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> map[99][i];
	}
	cout << pot();
	return 0;
}