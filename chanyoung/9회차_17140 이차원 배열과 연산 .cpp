#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// 1:10 ����

struct arr { int num, cnt; };

bool cmp(arr l, arr r) // ����Ƚ�� ��������, ��ȣ�� �������� ������ ����
{
	if (l.cnt < r.cnt) return true;
	if (l.cnt > r.cnt) return false;
	if (l.num < r.num) return true;
	if (l.num > r.num) return false;
	return false;
}

int r, c, k;
vector<int> RRR[101]; // ����� �迭
vector<int> CCC[101]; // ������ �迭
int maxR, maxC; // �ִ� �� ��ȣ, �ִ� �� ��ȣ

void flow()
{
	if (maxR >= maxC)
	{
		int maxline = 0;
		for (int i = 0; i < maxR; i++)
		{
			int num[101] = { 0 };
			for (int j = 0; j < maxC; j++) // �� ��ȣ�� ����Ƚ�� ����
			{
				if (RRR[i].size() <= j)break;
				if (RRR[i][j] == 0)continue;
				num[RRR[i][j]]++;
			}
			vector<arr> v;
			for (int j = 1; j < 101; j++) // ��ȣ�� ����Ƚ�� �迭�� ����
			{
				if (num[j] == 0)continue;
				v.push_back({ j,num[j] });
			}
			sort(v.begin(), v.end(), cmp); // ����
			RRR[i].clear();
			for (int j = 0; j < v.size(); j++) // �迭�� �ű��
			{
				arr now = v[j];
				RRR[i].push_back(now.num);
				RRR[i].push_back(now.cnt);
			}
			maxline = max(maxline, int(RRR[i].size())); // �ִ��ȣ ����
		}
		maxC = maxline;
		for (int j = 0; j < maxC; j++) // ������ �迭�� �����Ű��
		{
			CCC[j].clear();
			for (int i = 0; i <maxR; i++)
			{
				if (RRR[i].size() <= j) CCC[j].push_back(0); // ��ĭ 0���� ä��
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