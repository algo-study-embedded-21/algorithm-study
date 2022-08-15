#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

struct gps {  // ��ǥ ����ü
	int y;
	int x;
};

int n, m, x, y, k;
int map[20][20]; // ��
int dice[6]; // �ֻ��� ������ ���� �迭
/*0
1 2 3    5�� �ٴڸ� 2�� ����
  4
  5*/
int save; // �ֻ����� ��ü�� ���� ���庯��
vector<int> go; // ��� ���� ����

void change(gps now) // ������ ���� ���ڿ� ���� �ֻ��� �ظ� ���� �ٲ� �Լ�
{
	if (map[now.y][now.x] == 0)
	{ // ���� 0�̸� �ֻ��� �ظ� ���ڸ� �����ؿ´�
		map[now.y][now.x] = dice[5];
	}
	else
	{ // ���� 0�� �ƴϸ� �� ���ڸ� �ֻ��� �ظ鿡 �����ϰ� ���� 0���� �����
		dice[5] = map[now.y][now.x];
		map[now.y][now.x] = 0;
	}
}

void roll(gps start)
{
	queue<gps> q;
	q.push(start);
	/*change(start);*/
	for (int i = 0; i < k; i++) // ��ɼ� ��ŭ �ݺ�
	{
		gps now = q.front();
		q.pop();
		gps next;
		if (go[i] == 1) // ����� 1 >> �������� ����
		{
			next.y = now.y;
			next.x = now.x + 1;
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)
			{ // ���� ����� ��� �����ϰ� �ٽ� ������ġ�� ����
				q.push(now);
				continue;
			}
			save = dice[2];
			dice[2] = dice[1];
			dice[1] = dice[5];
			dice[5] = dice[3];
			dice[3] = save;
			change(next); // ������ ĭ���� �ֻ��� �ظ� �ٲ�
			q.push(next); // ���� ��ġ ����
			cout << dice[2] << "\n"; // ���� ���

		}
		else if (go[i] == 2) // ����� 2 >> �������� ����
		{
			next.y = now.y;
			next.x = now.x - 1;
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)
			{
				q.push(now);
				continue;
			}
			save = dice[2];
			dice[2] = dice[3];
			dice[3] = dice[5];
			dice[5] = dice[1];
			dice[1] = save;
			change(next);
			q.push(next);
			cout << dice[2] << "\n";

		}
		else if (go[i] == 3) // ����� 3 >> �������� ����
		{
			next.y = now.y - 1;
			next.x = now.x;
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)
			{
				q.push(now);
				continue;
			}
			save = dice[2];
			dice[2] = dice[4];
			dice[4] = dice[5];
			dice[5] = dice[0];
			dice[0] = save;
			change(next);
			q.push(next);
			cout << dice[2] << "\n";

		}
		else if (go[i] == 4) // ����� 4 >> �������� ����
		{
			next.y = now.y + 1;
			next.x = now.x;
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)
			{
				q.push(now);
				continue;
			}
			save = dice[2];
			dice[2] = dice[0];
			dice[0] = dice[5];
			dice[5] = dice[4];
			dice[4] = save;
			change(next);
			q.push(next);
			cout << dice[2] << "\n";
		}

	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> x >> y >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < k; i++)
	{
		int a;
		cin >> a;
		go.push_back(a);
	}
	roll({ x,y });

	return 0;
}