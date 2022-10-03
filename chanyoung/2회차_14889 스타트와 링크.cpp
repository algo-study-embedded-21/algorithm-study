#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

struct node {
	int y;
	int x;
};

int n;
int soccer[21][21]; // 관계도
int start; // 스타트 팀 능력치
int link; // 링크 팀 능력치
int use[21]; // 중복방지
int minvs = 2134567890;

void dfs(int s, int num)
{
	if (num == n / 2) // 절반히 뽑혔다면 계산
	{
		vector<int> vlink; // 링크 팀원 리스트
		vector<int> vstart; // 스타트 팀원 리스트
		for (int i = 0; i < n; i++)
		{
			if (use[i] == 0) 
			{
				vlink.push_back(i); // 뽑히지 않은 사람을 링크 팀으로
			}
			else
			{
				vstart.push_back(i); // 뽑힌 사람을 스타트 팀으로
			}
		}
		link = 0;
		for (int i = 0; i < vlink.size(); i++)
		{
			for (int j = 0; j < vlink.size(); j++)
			{
				link = link + soccer[vlink[i]][vlink[j]]; // 링크팀 능력치 계산
			}
		}
		start = 0;
		for (int i = 0; i < vstart.size(); i++)
		{
			for (int j = 0; j < vstart.size(); j++)
			{
				start = start + soccer[vstart[i]][vstart[j]]; // 스타트팀 능력치 계산
			}
		}
		int vs = abs(link - start);
		if (vs < minvs)
		{
			minvs = vs;
		}
		return;
	}
	for (int i = s; i < n; i++)
	{   // 스타트 팀에 들어갈 팀원 뽑기
		int team = i;
		if (use[team] == 1)
		{
			continue;
		}
		use[team] = 1;
		dfs(team, num + 1);
		use[team]=0;
	}
}

int main()
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> soccer[i][j];
		}
	}
	dfs(0,0);
	cout << minvs;
	
	return 0;
}
