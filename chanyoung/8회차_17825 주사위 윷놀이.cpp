#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>

// 1:47 예제 일부정답
// 2:10 갈아엎기
// 2:59 예제 정답
// 3:40 정답.....

using namespace std;

struct dir { int red; int blue; };

int dice[10];
dir unit[4]; // unit[i].red = i번째 말의 위치  unit[i].blue = i번째 말이 파란화살표를 몇번 타고 왔는지
dir map[41]; // map[i].red = 파란화살표를 탄적없는경우 가야할 다음칸 map[i].blue = 파란화살표를 탄적이 있는경우 가야할 다음 칸
int score;
int maxscore = -1;
vector<int> path[4];
vector<int> pathmap[4];

int check(int now, int bluecnt) // 이동할 위치에 이미 놓여진 말이 있는지 확인
{
	if (now > 40)
	{
		return 1;
	}
	for (int i = 0; i < 4; i++)
	{
		if (unit[i].red == now && (now == 40 || unit[i].blue == bluecnt)) //40은 하나뿐
		{
			return 0;
		}
	}
	return 1;
}

void play(int level)
{
	if (level == 10)
	{
		maxscore = max(score, maxscore);
		if (score == maxscore)
		{
			int t = 1;
		}
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		int now = unit[i].red;
		if (now > 40) // 이미 도착한 말은 움직이지 않는다
		{
			continue;
		}
		int temp = now;
		int crossblue = unit[i].blue;
		if (now == 10 || now == 20 ) // 파란색 칸(10또는20) 에서 출발하는경우
		{
			for (int j = 0; j < dice[level]; j++)
			{
				now = map[now].blue;
			}
			if (check(now, 1)) // 다른말이 없으면 이동
			{
				unit[i].red = now;
				unit[i].blue = 1; // 파란색 화살표를 하나 타고 왔다
			}
			else continue;
		}
		else if (now == 30 && crossblue == 0) /////////// 파란색 30번 칸에서 출발하는경우
		{
			now = 28; // 억지로 한칸 옮기고 시작
			for (int j = 0; j < dice[level] -1; j++)
			{
				now = map[now].blue;
			}
			if (check(now, 1)) // 다른말이 없으면 이동
			{
				unit[i].red = now;
				unit[i].blue = 1; // 파란색 화살표를 하나 타고 왔다
			}
			else continue;
		}
		else if (crossblue == 0) // 파란색 화살표를 탄적이 없는경우
		{
			for (int j = 0; j < dice[level]; j++)
			{
				now = map[now].red;
				if (now > 40) break; // 도착하면 탈출
			}
			if (check(now, 0)) unit[i].red = now; // 다른말이 없으면 이동
			else continue;
		}
		else // 파란색 화살표를 탄적이 있는경우
		{
			for (int j = 0; j < dice[level]; j++)
			{
				if (now == 30) now = 35;
				else now = map[now].blue;
				if (now > 40) break; // 도착하면 탈출
			}
			if (check(now, 1)) unit[i].red = now; // 다른말이 없으면 이동
			else continue;
		}
		if (now <= 40) score += unit[i].red;
		path[i].push_back(now);
		pathmap[i].push_back(dice[level]);
		play(level + 1);
		pathmap[i].pop_back();
		path[i].pop_back();
		if (now <= 40) score -= unit[i].red;
		unit[i].red = temp; // 위치 원복
		unit[i].blue = crossblue; // 이전에 파란색 칸에서 출발한경우
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	for (int i = 0; i < 10; i++)
	{
		cin >> dice[i];
	}
	// 맵 세팅
	for (int i = 0; i < 41; i++)
	{
		map[i].red = i + 2;
		map[i].blue = i + 2;
	}
	for (int i = 25; i < 40; i += 5) map[i].blue = i + 5;
	for (int i = 10; i < 19; i += 3) map[i].blue = i + 3;
	for (int i = 28; i >= 26; i--) map[i].blue = i - 1;
	map[19].blue = 25;
	map[24].blue = 25;

	play(0);
	cout << maxscore;

	return 0;
}