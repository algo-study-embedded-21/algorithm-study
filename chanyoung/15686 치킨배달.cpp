#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

struct chicken {
	int y;
	int x;
};

int n, m;
int cost;
int t;
int tsave;
int mincost = 2134567890;
vector<int> use;
vector<chicken> store;  // ġŲ�� ��ǥ ���� ����
vector<chicken> home;  // �� ��ǥ ���� ����
vector<chicken> storecheck; // ���õ� ġŲ�� ��ǥ ���庤��

void bfs(chicken house)
{
	int mindist = 2134567890;
	int dist = 0;
	for (int j = 0; j < storecheck.size(); j++) // Ȯ���� ġŲ���� ��������
	{
		int xx, yy;
		// y��Ÿ� ���
		if (storecheck[j].y > house.y)
		{
			yy = storecheck[j].y - house.y;
		}
		else
		{
			yy = house.y - storecheck[j].y;
		}
		// x��Ÿ� ���
		if (storecheck[j].x > house.x)
		{
			xx = storecheck[j].x - house.x;
		}
		else
		{
			xx = house.x - storecheck[j].x;
		}
		dist = yy + xx; // y��Ÿ� + x��Ÿ� = �ѰŸ�
		if (dist < mindist) // �ּҰŸ� = ġŲ�Ÿ�
		{
			mindist = dist;
		}
	}
	cost = cost + mindist;  // �� ���� ġŲ�Ÿ� ������
}

void dfs(int s) // m���� ġŲ���� ���� ��� ����Ǽ�
{
	if (s == m) // m���� ġŲ���� ����ٸ� ���
	{
		cost = 0;
		for (int i = 0; i < home.size(); i++)
		{
			// m���� ġŲ�� ������ ġŲ�Ÿ� ���
			bfs(home[i]);
		}
		if (cost < mincost)
		{  // ������ ġŲ�Ÿ����� �۴ٸ� ����
			mincost = cost;
		}
		return;
	}
	for (int i = t; i < store.size(); i++)
	{
		if (use[i] == 1) // �̹� ������ ġŲ���̶�� ����
		{
			continue;
		}
		storecheck.push_back({ store[i].y,store[i].x }); // ���õ� ġŲ�� ��ǥ ����
		use[i] = 1;
		tsave = t;
		t = i;
		dfs(s + 1);
		t = tsave;
		use[i] = 0;
		storecheck.pop_back();
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			int a;
			cin >> a; // ���� �Է� ����
			if (a == 2)
			{
				// ġŲ�� ��ǥ����
				store.push_back({ i,j });
				use.push_back(0);  // ġŲ���� �� ����ŭ use ���� ���� Ȯ��
			}
			if (a == 1)
			{
				// ������ ��ǥ ����
				home.push_back({ i,j });
			}
		}
	}

	dfs(0);
	cout << mincost;

	return 0;
}