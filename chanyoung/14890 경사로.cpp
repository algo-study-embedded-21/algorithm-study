#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 50�� ��!

using namespace std;

struct gps {
	int y;
	int x;
};

int n, L;
int map[100][100];

int yy[2] = {1,0}; // 0�϶� ���˻� / 1�϶� ��˻�
int xx[2] = {0,1};

int pos(int d, gps st)
{
	gps now = st;
	int flag = 1; // ���� ����
	int stack = 1; // ����� �������� ��ϼ�
	while (now.y + yy[d] != n && now.x + xx[d] != n) // ������ ������
	{
		int high = map[now.y][now.x]; // ���� ����
		gps next = { now.y + yy[d],now.x + xx[d] }; // ������ġ
		int updown = map[next.y][next.x] - high; // �������� - �������
		if (updown == 0) // ���� �����ΰ��
		{
			stack++;
			now = next;
			continue;
		}
		else if (updown == 1) // �������ΰ��
		{
			if (stack >= L) // ���θ� ���� ����� ������ ���
			{
				now = next;
				stack = 1; // ���� ���� �ʱ�ȭ
			}
			else
			{
				flag = 0; // �� ���� �Ұ�
				break;
			}
		}
		else if (updown == -1) // �������ΰ��
		{
			int low = 0; // ���ӵ� ���� ������ ��� ��
			while (next.y < n && next.x < n && map[next.y][next.x] == high - 1) // ���ӵǴ� ����
			{
				next = { next.y + yy[d],next.x + xx[d] };
				low++;
				if (low == L) // ���� ���� ������ Ȯ���Ǿ��ٸ�
				{
					break;
				}
			}
			if (low == L)
			{
				now = { next.y - yy[d],next.x - xx[d] }; // ���� ���κк��� ���� �簳
				stack = 0; // ���� ���� �ʱ�ȭ
			}
			else // ���� ���� ������ �����Ѱ��
			{
				flag = 0;
				break;
			}
		}
		else // ������ �Ǵ� ������ ��簡 1�� �ʰ��ϴ°��
		{
			flag = 0;
			break;
		}
	}
	return flag; // ���ΰ�� 
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> L;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}

	int ans = 0;

	for (int i = 0; i < n; i++)
	{
		ans += pos(0, { 0,i }); // i�� �˻�
		ans += pos(1, { i,0 }); // i�� �˻�
	}

	cout << ans;

	return 0;
}