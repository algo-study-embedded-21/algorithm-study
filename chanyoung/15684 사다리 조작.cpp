#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 1:14 ���� ���� >> �ð��ʰ� >> �� ���ٿ��� �� �������� ����
// 1:48 PASS (������ 9% �������� �ð��ʰ� ����)

using namespace std;

struct gps
{
	int y;
	int x;
};

int n, m, h;
int block[32][10]; // ���μ� ������ ���μ��� ��Ÿ��
int ans = 10;

int down(int num) // num��° ���μ��� �������� ���ϱ�
{
	gps now = { 1,num };
	while (now.y != h+1)
	{
		if (now.x<n && block[now.y][now.x] == 1)
		{
			now.x += 1;
		}
		else if (now.x > 1 && block[now.y][now.x - 1] == 1)
		{
			now.x -= 1;
		}
		now.y += 1;
	}
	return now.x;
}

int check() // ���ϴ� ��ٸ� �ϼ��� 1 ����
{
	int flag = 1;
	for (int i = 1; i <= n; i++)
	{
		if (i != down(i))
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

void put(int level,int num)
{
	if (level > ans) // �̹� ������ Ƚ������ �� ���� �õ� �ʿ� X
	{
		return;
	}
	if (level > 3) // 3�� �̻� �õ� X
	{
		return;
	}
	if (check() == 1) // ��ٸ� �ϼ��� Ƚ�� ����
	{
		ans = min(ans, level);
		return;
	}
	for (int i = num; i <= h; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (block[i][j] > 0) //�̹� ��ٸ� ������pass
			{
				continue;
			}
			block[i][j] = 1;
			put(level + 1, i); // �ߺ� ����Ǽ� ���� ���� i���� Ž��
			block[i][j] = 0;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> h;
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		block[a][b] = 1;
	}
	put(0,1);
	if (ans == 10) // 3�� �̳��� �Ұ����Ѱ�� -1 ���
	{
		ans = -1;
	}
	cout << ans;

	return 0;
}