#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

struct gps
{
	int y;
	int x;
};

int n, l, r;
int map[50][50];
int cnt; // �α��̵��� �Ͼ �ϼ�

void change(vector<gps> openworld, int worldpeople) //�̵��� �α��� �ʿ� ����ϴ� �Լ�
{
	worldpeople = worldpeople / openworld.size(); // ����� �������� ��� �α�
	for (int i = 0; i < openworld.size(); i++)
	{
		map[openworld[i].y][openworld[i].x] = worldpeople;
	}
}

int open(gps start,int use[50][50])
{
	int end = 0; // �α��̵��� �Ͼ���� ���� ǥ�ø� ���� ����
	int worldpeople = 0;; // �α��̵��� �Ͼ �������� �α��� ����
	vector<gps> openworld; // �α��̵��� �Ͼ ���� ��ǥ ����
	queue<gps> q;
	q.push(start);
	use[start.y][start.x] = 1;
	worldpeople += map[start.y][start.x];
	openworld.push_back(start);
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		int yy[4] = { 0,0,1,-1 };
		int xx[4] = { 1,-1,0,0 };
		for (int i = 0; i < 4; i++)
		{
			gps next;
			next.y = now.y + yy[i];
			next.x = now.x + xx[i];
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)
			{
				continue;
			}
			if (use[next.y][next.x] == 1)
			{
				continue;
			}
			int gap = abs(map[next.y][next.x] - map[now.y][now.x]); // �α� �������� �α��� ��
			if (gap < l || gap > r) // �־��� ���� ���̸� ����
			{
				continue;
			}
			openworld.push_back(next);
			worldpeople += map[next.y][next.x];
			use[next.y][next.x] = 1;
			end = 1; // �α��̵��� �ǽ��ؾ����� ǥ��
			q.push(next);
		}
	}
	if (end == 1) // next�� �߻������� �ִٸ� �α��̵� �ǽ�
	{
		change(openworld, worldpeople);
	}
	return end; // �α��̵��� �ǽ��ߴ��� ���θ� ����
}



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> l >> r;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}
	while (1) // ���̻� �α��̵��� �Ͼ�� ���������� �ݺ�
	{
		int end = 0; // �α��̵� �ǽ� ���� �ʱ�ȭ
		int use[50][50] = { 0 }; // ���� ���� �湮��� �ʱ�ȭ
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (use[i][j] == 1) // �̹� Ȯ���� ���� �н�
				{
					continue;
				}
				end += open({ i,j },use); // �α��̵��� �ǽõǾ��ٸ� end > 0
			}
		}
		if (end > 0)
		{
			cnt++; // �α��̵��� �ǽõǾ��ٸ� ��¥ ī��Ʈ
		}
		else
		{
			break; // �ǽõ����� ���ٸ� Ż��
		}
	}
	cout << cnt;

	return 0;
}