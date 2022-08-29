#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<unordered_map>

using namespace std;

int wheel[5][8];  // wheel[바퀴의번호][톱니의번호] = 극
int k;
int turnox[5]; // 톱니바퀴가 돌았는지 여부

void turn(int wheelnum, int direction)
{
	turnox[wheelnum] = 1; // 지금 해당 번호의 톱니 바퀴를 돌릴것이다
	int opo;
	if (direction == 1) // 반대방향 저장
	{
		opo = -1;
	}
	else
	{
		opo = 1;
	}
	if (wheelnum < 4 && turnox[wheelnum + 1] == 0 && wheel[wheelnum][2] != wheel[wheelnum + 1][6])
	{ // 뒷번호 톱니바퀴에 영향을 주는 경우 이면서 뒷번호가 아직 돌지 않은경우
		turn(wheelnum + 1, opo);
	}
	if (wheelnum > 1 && turnox[wheelnum - 1] == 0 && wheel[wheelnum - 1][2] != wheel[wheelnum][6])
	{ // 앞번호 톱니바퀴에 영향을 주는 경우 이면서 앞번호가 아직 돌지 않은경우
		turn(wheelnum - 1, opo);
	}
	if (direction == 1) // 시계방향으로 돌기
	{
		int temp = wheel[wheelnum][7];
		for (int i = 7; i >=1; i--)
		{
			wheel[wheelnum][i] = wheel[wheelnum][i-1];
		}
		wheel[wheelnum][0] = temp;
	}
	else // 반시계방향으로 돌기
	{
		int temp = wheel[wheelnum][0];
		for (int i = 0; i < 7; i++)
		{
			wheel[wheelnum][i] = wheel[wheelnum][i+1];
		}
		wheel[wheelnum][7] = temp;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	for (int i = 1; i < 5; i++)
	{
		string line;
		cin >> line;
		for (int j = 0; j < 8; j++)
		{
			wheel[i][j] = line[j] - '0';
		}
	}
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		int wheelnum, direction;
		cin >> wheelnum >> direction;
		turn(wheelnum, direction);
		for (int j = 1; j < 5; j++) // 톱니바퀴 돌았는지 여부 초기화
		{
			turnox[j] = 0;
		}
	}
	int score = 1; // 톱니바퀴 번호가 1일때 1점
	int totalscore = 0;
	for (int i = 1; i < 6; i++)
	{
		if (wheel[i][0] == 1) // 12시의 극성이  s일때만 점수 추가
		{
			totalscore += score;
		}
		score = score * 2; // 톱니바퀴의 점수 = 2^(톱니바퀴번호-1)
	}
	cout << totalscore;
	return 0;
}