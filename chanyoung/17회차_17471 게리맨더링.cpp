#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n;
int team[10]; // 0이면 1번 선거구 1이면 2번 선거구
int num[10]; // 각 지역의 시민 수
vector<int> node[10]; // 각 지역별 인접 지역 리스트
int region[2]; // 각 선거구에 속한 지역 수
int citizen[2]; // 각 선거구의 시민 수
int ans = 213456789;

int teamcheck(int st) // 선거구가 내부적으로 연결되어있는지 여부확인
{
	queue<int> q;
	int visit[10] = { 0 };
	int teamnum = team[st]; //체크할 선거구 번호
	q.push(st);
	visit[st] = 1;
	int cnt = 1; // 선거구내 연결된 지역 수
	while (!q.empty())
	{
		int now = q.front();
		q.pop();
		for (int i = 0; i < node[now].size(); i++)
		{
			int next = node[now][i];
			if (teamnum != team[next])continue; // 다른 선거구면 무시
			if (visit[next] == 1)continue;
			visit[next] = 1;
			q.push(next);
			cnt++;
		}
	}
	if (cnt == region[teamnum]) return 1; // 연결된 지역수 == 선거구내 지역수 인경우 모두 연결됨
	else return 0;
}

void dfs(int level)
{
	if (level == n)
	{
		int T_one = 0, T_two = 0;
		for (int i = 0; i < n; i++)
		{
			if (team[i] == 0) // 1번 선거구가 모두 연결되어 있는 지 체크
			{
				if (teamcheck(i))
				{
					T_one = 1;
					break;
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (team[i] == 1)// 2번 선거구가 모두 연결되어 있는 지 체크
			{
				if (teamcheck(i))
				{
					T_two = 1;
					break;
				}
			}
		}
		if (T_one && T_two) // 모든 선거구가 연결된경우
		{
			ans = min(ans, abs(citizen[0] - citizen[1]));
		}
		return;
	}
	for (int i = 0; i < 2; i++)
	{
		region[i] += 1;
		citizen[i] += num[level];
		team[level] = i;
		dfs(level + 1);
		team[level] = 0;
		citizen[i] -= num[level];
		region[i] -= 1;
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
		cin >> num[i];
	}
	for (int i = 0; i < n; i++)
	{
		int t;
		cin >> t;
		for (int j = 0; j < t; j++)
		{
			int a;
			cin >> a;
			node[i].push_back(a - 1);
		}
	}
	dfs(0);
	if (ans == 213456789) cout << "-1";
	else cout << ans;

	return 0;
}