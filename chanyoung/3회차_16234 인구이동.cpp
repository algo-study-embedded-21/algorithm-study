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

int n, l, r;
int map[50][50];
int cnt; // 인구이동이 일어난 일수

void change(vector<gps> openworld, int worldpeople) //이동된 인구를 맵에 기록하는 함수
{
	worldpeople = worldpeople / openworld.size(); // 개방된 국가들의 평균 인구
	for (int i = 0; i < openworld.size(); i++)
	{
		map[openworld[i].y][openworld[i].x] = worldpeople;
	}
}

int open(gps start,int use[50][50])
{
	int end = 0; // 인구이동이 일어났는지 여부 표시를 위한 변수
	int worldpeople = 0;; // 인구이동이 일어날 국가들의 인구수 총합
	vector<gps> openworld; // 인구이동이 일어날 국가 좌표 저장
	queue<gps> q;
	q.push(start);
	use[start.y][start.x] = 1;
	worldpeople += map[start.y][start.x];
	openworld.push_back(start);
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		int yy[4] = { 0,0,1,-1 };
		int xx[4] = { 1,-1,0,0 };
		for (int i = 0; i < 4; i++)
		{
			gps next;
			next.y = now.y + yy[i];
			next.x = now.x + xx[i];
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)
			{
				continue;
			}
			if (use[next.y][next.x] == 1)
			{
				continue;
			}
			int gap = abs(map[next.y][next.x] - map[now.y][now.x]); // 인근 국가와의 인구수 차
			if (gap < l || gap > r) // 주어진 범위 밖이면 무시
			{
				continue;
			}
			openworld.push_back(next);
			worldpeople += map[next.y][next.x];
			use[next.y][next.x] = 1;
			end = 1; // 인구이동을 실시해야함을 표시
			q.push(next);
		}
	}
	if (end == 1) // next가 발생한적이 있다면 인구이동 실시
	{
		change(openworld, worldpeople);
	}
	return end; // 인구이동을 실시했는지 여부를 리턴
}



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> l >> r;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}
	while (1) // 더이상 인구이동이 일어나지 않을때까지 반복
	{
		int end = 0; // 인구이동 실시 여부 초기화
		int use[50][50] = { 0 }; // 매일 국가 방문기록 초기화
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (use[i][j] == 1) // 이미 확인한 국가 패스
				{
					continue;
				}
				end += open({ i,j },use); // 인구이동이 실시되었다면 end > 0
			}
		}
		if (end > 0)
		{
			cnt++; // 인구이동이 실시되었다면 날짜 카운트
		}
		else
		{
			break; // 실시된적이 없다면 탈출
		}
	}
	cout << cnt;

	return 0;
}
