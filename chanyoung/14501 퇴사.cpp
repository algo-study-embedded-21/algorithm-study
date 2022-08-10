#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

struct sch  // 입력에 맞춘 데이터 타입
{
	int day;
	int cost;
};

int n;
vector<sch> meet; // 입력을 받을 벡터
int costs;
int maxcost = -1;
vector<int> path;

void dfs(int day) //  0<= day <=n-1
{
	if (costs > maxcost) // 얻을수 있는 최대수익 저장
	{
		maxcost = costs;
	}
	for (int i = day; i < n; i++) // 다음 일을 맡을수 있는 날부터 탐색
	{
		if (i + meet[i].day >= n + 1) // 해당 일을 맡으면 퇴사일이 넘어서 끝나는경우 무시
		{
			continue;
		}
		// i + meet[i].day = n >> 퇴사날에 딱 맞춰 끝나는경우 >> 맡을수 있다

		if (i == n - 1) //sch의 인덱스가 n-1 >> 마지막 근무날인 경우
		{
			if (meet[i].day != 1) // 맡을 일을 오늘 끝낼수 없다면 무시
			{
				continue;
			}
		}
		day = i + meet[i].day; // 지금의 날짜 + 내가 맡은 일이 걸리는 날짜 = 다음 일을 맡을수 있는 날짜
		costs = costs + meet[i].cost; // 지금 까지 얻은 수익
		dfs(day); // 다음 일로 이동
		costs = costs - meet[i].cost; // DFS 수익 초기화
		day = day - meet[i].day; // DFS 날짜 초기화
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		meet.push_back({ a,b });
	}
	dfs(0);
	cout << maxcost;

	return 0;
}