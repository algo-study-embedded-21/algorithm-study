#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

struct sch  // �Է¿� ���� ������ Ÿ��
{
	int day;
	int cost;
};

int n;
vector<sch> meet; // �Է��� ���� ����
int costs;
int maxcost = -1;
vector<int> path;

void dfs(int day) //  0<= day <=n-1
{
	if (costs > maxcost) // ������ �ִ� �ִ���� ����
	{
		maxcost = costs;
	}
	for (int i = day; i < n; i++) // ���� ���� ������ �ִ� ������ Ž��
	{
		if (i + meet[i].day >= n + 1) // �ش� ���� ������ ������� �Ѿ �����°�� ����
		{
			continue;
		}
		// i + meet[i].day = n >> ��糯�� �� ���� �����°�� >> ������ �ִ�

		if (i == n - 1) //sch�� �ε����� n-1 >> ������ �ٹ����� ���
		{
			if (meet[i].day != 1) // ���� ���� ���� ������ ���ٸ� ����
			{
				continue;
			}
		}
		day = i + meet[i].day; // ������ ��¥ + ���� ���� ���� �ɸ��� ��¥ = ���� ���� ������ �ִ� ��¥
		costs = costs + meet[i].cost; // ���� ���� ���� ����
		dfs(day); // ���� �Ϸ� �̵�
		costs = costs - meet[i].cost; // DFS ���� �ʱ�ȭ
		day = day - meet[i].day; // DFS ��¥ �ʱ�ȭ
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