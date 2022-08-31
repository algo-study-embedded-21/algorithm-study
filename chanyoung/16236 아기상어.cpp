#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct gps {
	int y;
	int x;
};

bool cmp(gps l, gps r)
{
	if (l.y < r.y)
	{
		return true;
	}
	if (l.y > r.y)
	{
		return false;
	}
	if (l.x < r.x)
	{
		return true;
	}
	if (l.x > r.x)
	{
		return false;
	}
	return false;
}

int n;
int map[20][20];
vector<gps> aqua;
int body = 2;
gps shark;
int totaltime;
int cnt;

int yy[4] = { 1,0,0,-1 }; // �ִ��� ���ʺ���
int xx[4] = { 0,-1,1,0 }; // �ִ��� ���ʺ���

int eat(gps st)
{
	vector<gps> fish; // ��ũ�� ���� ���� ������ ����
	vector<gps> catchfish; // �ּҰŸ� �������� �����Ҽ� �ִ� �����鸸 ����
	for (int i = 0; i < aqua.size(); i++)
	{
		gps g = aqua[i];
		if (map[g.y][g.x] < body && map[g.y][g.x] != 0 && map[g.y][g.x]!=9)  // map[g.y][g.x]!=9 ��� ���Ʋ�ȴ�..... ��
		{
			fish.push_back({ g.y,g.x }); // ������ �ִ� ����� ��ġ ����
		}
	}
	if (fish.size() == 0) // ������ �ִ� ����Ⱑ ���ٸ� ����
	{
		return 0;
	}
	int mindist = 2134567890;
	int use[20][20] = { 0 };
	int hungry = 0;
	queue<gps> q;
	q.push(st);
	use[st.y][st.x] = 1;
	while (!q.empty())
	{
		gps now = q.front();
		q.pop();
		for (int i = 0; i < fish.size(); i++)
		{
			gps fishup = fish[i];
			if (fishup.y == now.y && fishup.x == now.x) // ������ ��ġ�� ������ �ִ� ����� ��ġ�� �ϳ����
			{
				if (use[now.y][now.x] <= mindist) // ���� ���� ����� �������
				{
					mindist = use[now.y][now.x];
					catchfish.push_back({ now.y,now.x }); // ���� �ĺ� ����� ���
				}
				else
				{
					hungry = 1; // ����Ⱑ �ִ� ��ġ������ �� ������Ⱑ �ִ°�� Ž�� �ߴ�
				}
				break;
			}
		}
		if (hungry == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				gps next;
				next.y = now.y + yy[i];
				next.x = now.x + xx[i];
				if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)
				{
					continue;
				}
				if (map[next.y][next.x] > body) // �������� ū ������ ����������
				{
					continue;
				}
				if (use[next.y][next.x] > 0)
				{
					continue;
				}
				q.push(next);
				use[next.y][next.x] = use[now.y][now.x] + 1; // ���������� �Ÿ� ����
			}
		}
		else
		{
			break;
		}
	}
	if (catchfish.size() > 0) // �����ĺ��� �ִٸ�
	{
		sort(catchfish.begin(), catchfish.end(), cmp); // ���ǿ��°� ����
		gps eatfish = catchfish[0]; // ���ǿ� ���� ������ �����
		map[shark.y][shark.x] = 0; // �� �ִ����� ��ĭ����
		shark.y = eatfish.y;
		shark.x = eatfish.x;
		map[shark.y][shark.x] = 9; // ���� ����� ĭ���� �̵�
		cnt++; // ���� ������� �� ����
		if (cnt == body) // ���� ũ�⸸ŭ �Ծ��ٸ� ����
		{
			body++;
			cnt = 0;
		}
		return use[shark.y][shark.x] - 1; // ���������� �Ÿ� = �ɸ� �ð�
	}
	else
	{
		return 0;  // ������ �ִ� ������ ������ ���� ���°��
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a;
			cin >> a;
			map[i][j] = a;
			if (a == 9)
			{
				shark.y = i;
				shark.x = j;
			}
			else if (a > 0)
			{
				aqua.push_back({ i,j });
			}
		}
	}
	int eating = eat({ shark.y,shark.x });
	totaltime = eating;
	while (eating != 0) // �ɸ��ð��� 0�� �ƴҵ��� = ����⸦ ������ �ִ� ����
	{
		eating = eat({ shark.y,shark.x });
		totaltime += eating; // �ð� ������
	}
	cout << totaltime;
	return 0;
}