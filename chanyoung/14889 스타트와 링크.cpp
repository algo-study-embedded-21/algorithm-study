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
int soccer[21][21]; // ���赵
int start; // ��ŸƮ �� �ɷ�ġ
int link; // ��ũ �� �ɷ�ġ
int use[21]; // �ߺ�����
int minvs = 2134567890;

void dfs(int s, int num)
{
	if (num == n / 2) // ������ �����ٸ� ���
	{
		vector<int> vlink; // ��ũ ���� ����Ʈ
		vector<int> vstart; // ��ŸƮ ���� ����Ʈ
		for (int i = 0; i < n; i++)
		{
			if (use[i] == 0) 
			{
				vlink.push_back(i); // ������ ���� ����� ��ũ ������
			}
			else
			{
				vstart.push_back(i); // ���� ����� ��ŸƮ ������
			}
		}
		link = 0;
		for (int i = 0; i < vlink.size(); i++)
		{
			for (int j = 0; j < vlink.size(); j++)
			{
				link = link + soccer[vlink[i]][vlink[j]]; // ��ũ�� �ɷ�ġ ���
			}
		}
		start = 0;
		for (int i = 0; i < vstart.size(); i++)
		{
			for (int j = 0; j < vstart.size(); j++)
			{
				start = start + soccer[vstart[i]][vstart[j]]; // ��ŸƮ�� �ɷ�ġ ���
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
	{   // ��ŸƮ ���� �� ���� �̱�
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