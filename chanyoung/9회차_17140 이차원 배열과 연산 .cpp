#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// 1:10 정답

struct arr { int num, cnt; };

bool cmp(arr l, arr r) // 등장횟수 적을수록, 번호가 작을수록 앞으로 정렬
{
	if (l.cnt < r.cnt) return true;
	if (l.cnt > r.cnt) return false;
	if (l.num < r.num) return true;
	if (l.num > r.num) return false;
	return false;
}

int r, c, k;
vector<int> RRR[101]; // 행기준 배열
vector<int> CCC[101]; // 열기준 배열
int maxR, maxC; // 최대 행 번호, 최대 열 번호

void flow()
{
	if (maxR >= maxC)
	{
		int maxline = 0;
		for (int i = 0; i < maxR; i++)
		{
			int num[101] = { 0 };
			for (int j = 0; j < maxC; j++) // 각 번호의 등장횟수 조사
			{
				if (RRR[i].size() <= j)break;
				if (RRR[i][j] == 0)continue;
				num[RRR[i][j]]++;
			}
			vector<arr> v;
			for (int j = 1; j < 101; j++) // 번호와 등장횟수 배열로 만듦
			{
				if (num[j] == 0)continue;
				v.push_back({ j,num[j] });
			}
			sort(v.begin(), v.end(), cmp); // 정렬
			RRR[i].clear();
			for (int j = 0; j < v.size(); j++) // 배열에 옮기기
			{
				arr now = v[j];
				RRR[i].push_back(now.num);
				RRR[i].push_back(now.cnt);
			}
			maxline = max(maxline, int(RRR[i].size())); // 최대번호 갱신
		}
		maxC = maxline;
		for (int j = 0; j < maxC; j++) // 열기준 배열에 적용시키기
		{
			CCC[j].clear();
			for (int i = 0; i <maxR; i++)
			{
				if (RRR[i].size() <= j) CCC[j].push_back(0); // 빈칸 0으로 채움
				else CCC[j].push_back(RRR[i][j]);
			}
		}
	}
	else
	{
		int maxline = 0;
		for (int i = 0; i < maxC; i++)
		{
			int num[101] = { 0 };
			for (int j = 0; j < maxR; j++)
			{
				if (CCC[i].size() <= j)break;
				if (CCC[i][j] == 0)continue;
				num[CCC[i][j]]++;
			}
			vector<arr> v;
			for (int j = 1; j < 101; j++)
			{
				if (num[j] == 0)continue;
				v.push_back({ j,num[j] });
			}
			sort(v.begin(), v.end(), cmp);
			CCC[i].clear();
			for (int j = 0; j < v.size(); j++)
			{
				arr now = v[j];
				CCC[i].push_back(now.num);
				CCC[i].push_back(now.cnt);
			}
			maxline = max(maxline, int(CCC[i].size()));
		}
		maxR = maxline;
		for (int j = 0; j < maxR; j++)
		{
			RRR[j].clear();
			for (int i = 0; i < maxC; i++)
			{
				if (CCC[i].size() <= j) RRR[j].push_back(0);
				else RRR[j].push_back(CCC[i][j]);
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> r >> c >> k;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int n;
			cin >> n;
			RRR[i].push_back(n);
		}
	}
	for (int j = 0; j< 3; j++){
		for (int i = 0; i < 3; i++){
			CCC[j].push_back(RRR[i][j]);
		}
	}
	maxR = 3,maxC = 3;
	int time = 0;
	while (time <= 100)
	{
		if (RRR[r - 1].size() > c - 1 && RRR[r - 1][c - 1] == k) break;
		flow();
		time++;
	}
	if (time == 101)cout << "-1";
	else cout << time;

	return 0;
}