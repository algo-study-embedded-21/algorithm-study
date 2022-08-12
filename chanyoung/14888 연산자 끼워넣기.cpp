#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

int n;
vector<int> num; // ���� ���� ����
vector<int> process; // �����ڸ� ���� ����
int usepro[10]; // ������ �ߺ� ��� ����
int maxresult = -2134567890;
int minresult = 2134567890;
int cost;

void dfs(int index)
{
	if (index == n) // ������ ���� ����
	{
		if (cost > maxresult)
		{ // �ִ�
			maxresult = cost;
		}
		if (cost < minresult)
		{ // �ּڰ�
			minresult = cost;
		}
		return;
	}
	int next = num[index];
	for (int j = 0; j < n - 1; j++)
	{
		if (usepro[j] == 1)
		{
			continue;
		}
		if (process[j] == 0) // ���� ������
		{
			cost = cost + next;
			usepro[j] = 1;
			dfs(index + 1);
			usepro[j] = 0;
			cost = cost - next;
		}
		else if (process[j] == 1) // ���� ������
		{
			cost = cost - next;
			usepro[j] = 1;
			dfs(index + 1);
			usepro[j] = 0;
			cost = cost + next;
		}
		else if (process[j] == 2) // ���� ������
		{
			cost = cost * next;
			usepro[j] = 1;
			dfs(index + 1);
			usepro[j] = 0;
			cost = cost / next;
		}
		else // ������ ������
		{
			int ex;
			ex = cost % next; // ������ ��Ƶα�
			cost = cost / next;
			usepro[j] = 1;
			dfs(index + 1);
			usepro[j] = 0;
			cost = cost * next+ ex; // ������ ������ ���ϱ�
		}

	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		num.push_back(a);
	}
	for (int i = 0; i < 4; i++)
	{
		int a;
		cin >> a;
		for (int j = 0; j < a; j++)
		{// �Է� ����ŭ ������ ���Ϳ� �ݺ� ���
			process.push_back(i);
		}
	}
	cost = num[0];// ���� ���� �ʱⰪ ����
	dfs(1);// ���� �� index = 1
	cout << maxresult << "\n" << minresult;
	return 0;
}