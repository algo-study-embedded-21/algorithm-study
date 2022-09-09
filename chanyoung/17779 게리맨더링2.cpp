// 2�ð� 10��

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

using namespace std;

struct gps
{
	int y;
	int x;
};

int n;
int map[21][21];
int group[5]; // �� ���ű��� �α���
int maxvote = -1; // ���� �α��� ���� ���ű�
int minvote = 2134567890; // ���� �α��� ���� ���ű�
int ans = 2134567890; // ��°�

void vote(gps st, int dl , int dr)
{
	if (st.y + dl + dr > n)
	{
		return; // �Ʒ��� �ε��� �Ѿ
	}
	if (st.x - dl <1)
	{
		return; // �������� �ε��� �Ѿ
	}
	if (st.x + dr > n)
	{
		return; // ���������� �ε��� �Ѿ
	}
	int left=0;
	int right=1;
	for (int i = 1; i < st.y; i++) // ���̾Ƹ� ���κ�
	{
		for (int j = 1; j <= st.x; j++)
		{
			group[0] += map[i][j];
		}
		for (int j = st.x + 1; j <= n; j++)
		{
			group[1] += map[i][j];
		}
	}
	for (int i = st.y; i < st.y + dl; i++)
	{
		for (int j = 0; j < st.x - left; j++)
		{
			group[0] += map[i][j]; // ���̾� ���� �� �κ�
		}
		left++;
	}
	for (int i = st.y; i <= st.y + dr; i++)
	{
		for (int j = st.x + right; j <= n; j++)
		{
			group[1] += map[i][j]; // ���̾� ������ ���κ�
		}
		right++;
	}
	left = 0;
	for (int i = st.y + dl; i <= st.y + dl + dr; i++)
	{
		for (int j = 1; j < st.x - dl + left; j++)
		{
			group[2] += map[i][j]; // ���̾� ���� �Ʒ� �κ�
		}
		left++;
	}
	right = 0;
	for (int i = st.y + dr + 1; i <= st.y + dl + dr; i++)
	{
		for (int j = st.x + dr - right; j <= n; j++)
		{
			group[3] += map[i][j]; // ���̾� ������ �Ʒ��κ�
		}
		right++;
	}
	for (int i = st.y + dr + dl + 1; i <= n; i++) // ���̾� �Ʒ��κ�
	{
		for (int j = 1; j < st.x - dl + dr; j++)
		{
			group[2] += map[i][j];
		}
		for (int j = st.x - dl + dr; j <= n; j++)
		{
			group[3] += map[i][j];
		}
	}
	left = 0;
	right = 0;
	int h = 0;
	while (h<=dr+dl) // ���̾� �κ�
	{
		for (int j = st.x - left; j <= st.x + right; j++)
		{
			group[4] += map[st.y + h][j];
		}
		if (h < dl) // ������ dl�� �������� �������� ���ҷ� ��ȭ
		{
			left++;
		}
		else
		{
			left--;
		}
		if (h < dr) // �������� dr�� �������� �������� ���ҷ� ��ȭ
		{
			right++;
		}
		else
		{
			right--;
		}
		h++;
	}
	for (int i = 0; i < 5; i++) // ���ű� 5���� ���Ͽ�
	{
		maxvote = max(maxvote, group[i]); // ���� �ο��� ���� ���ű�
		minvote = min(minvote, group[i]); // ���� �ο��� ���� ���ű�
		group[i] = 0; // Ž���� ��ģ ���ű� �ʱ�ȭ
	}
	ans = min(ans, maxvote - minvote); // ���̰��� �ּ��� ���� ��� ����
	maxvote = -1;
	minvote = 2134567890;
	vote(st, dl + 1, dr); // dl �� dr�� ���Ͽ� �ι��� dfs �������
	vote(st, dl, dr + 1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 1; i <=n; i++)
	{
		for (int j = 1; j <=n; j++)
		{
			cin >> map[i][j];
		}
	}
	for (int i = 1; i <= n - 2; i++) 
	{ // �������� dl�� dr���� �ּҰ��� 1�� �������� y�� n-2 / x�� 2~n-1 ���� ����
		for (int j = 2; j <= n - 1; j++)
		{
			vote({ i,j },1,1);// ������ dl=dr=1
		}
	}
	cout << ans;
	return 0;
}