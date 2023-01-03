#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n;
int team[10]; // 0�̸� 1�� ���ű� 1�̸� 2�� ���ű�
int num[10]; // �� ������ �ù� ��
vector<int> node[10]; // �� ������ ���� ���� ����Ʈ
int region[2]; // �� ���ű��� ���� ���� ��
int citizen[2]; // �� ���ű��� �ù� ��
int ans = 213456789;

int teamcheck(int st) // ���ű��� ���������� ����Ǿ��ִ��� ����Ȯ��
{
	queue<int> q;
	int visit[10] = { 0 };
	int teamnum = team[st]; //üũ�� ���ű� ��ȣ
	q.push(st);
	visit[st] = 1;
	int cnt = 1; // ���ű��� ����� ���� ��
	while (!q.empty())
	{
		int now = q.front();
		q.pop();
		for (int i = 0; i < node[now].size(); i++)
		{
			int next = node[now][i];
			if (teamnum != team[next])continue; // �ٸ� ���ű��� ����
			if (visit[next] == 1)continue;
			visit[next] = 1;
			q.push(next);
			cnt++;
		}
	}
	if (cnt == region[teamnum]) return 1; // ����� ������ == ���ű��� ������ �ΰ�� ��� �����
	else return 0;
}

void dfs(int level)
{
	if (level == n)
	{
		int T_one = 0, T_two = 0;
		for (int i = 0; i < n; i++)
		{
			if (team[i] == 0) // 1�� ���ű��� ��� ����Ǿ� �ִ� �� üũ
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
			if (team[i] == 1)// 2�� ���ű��� ��� ����Ǿ� �ִ� �� üũ
			{
				if (teamcheck(i))
				{
					T_two = 1;
					break;
				}
			}
		}
		if (T_one && T_two) // ��� ���ű��� ����Ȱ��
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