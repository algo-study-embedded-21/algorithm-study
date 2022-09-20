#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 1:13 ���� �Ϻ� ����
// 2:01 ���� 1,2,3 ����
// 2:15 ����


using namespace std;

struct fire {
	int m;
	int s;
	int d;
	int t; // �ش���ġ�� ���̾ ���� 
};

struct gps {
	int y;
	int x;
};

struct allfire {
	int r;
	int c;
	int m;
	int s;
	int d;
};

int n, m, k;
fire map[50][50];
vector<gps> fireball; // ���� ���̾
vector<allfire> movefire; // �̵��� ���̾ ����(�̵���)

int yy[8] = { -1,-1,0,1,1,1,0,-1 };
int xx[8] = { 0,1,1,1,0,-1,-1,-1 };

void move() // �̵�
{
	fireball.clear();
	for (int i = 0; i < movefire.size(); i++)
	{
		allfire now = movefire[i];
		if (map[now.r][now.c].m == 0) { // �ʿ� ���� ���� ��� ù��
			map[now.r][now.c].d = now.d;
			fireball.push_back({ now.r,now.c });
		}
		else {
			if (map[now.r][now.c].d != -1) // ������ Ȧ¦�� �ٸ��ҵ��� �������ٸ� ������ -1�� ǥ��
			{
				if (map[now.r][now.c].d % 2 != now.d % 2)
				{
					map[now.r][now.c].d = -1;
				}
			}
		}
		map[now.r][now.c].m += now.m;
		map[now.r][now.c].s += now.s;
		map[now.r][now.c].t += 1; // �� ��ġ�� ���̾ ���� ����
	}
}

void div() // �������� ���ÿ� ���� �̵��ϴ��� �ľ�(�̵� �غ�)
{
	movefire.clear();
	for (int i = 0; i < fireball.size(); i++)
	{
		gps st = fireball[i];
		fire now = map[st.y][st.x];
		map[st.y][st.x] = { 0,0,0,0 };
		gps next;
		if (now.t == 1) // ���̾�� �Ѱ���� �������� �ʴ´�
		{
			next.y = st.y + yy[now.d] * now.s;
			next.x = st.x + xx[now.d] * now.s;
			next.y = ((next.y % n) + n) % n; //�������� Ŀ��
			next.x = ((next.x % n) + n) % n;
			movefire.push_back({ next.y,next.x,now.m ,now.s,now.d });
			continue;
		}
		if (now.m / 5 == 0) // ������ ���̾�� ������ ������ 0�̶�� �Ҹ�
		{
			continue;
		}
		if (now.d == -1) // ������ ���̾�� ������ ¦/Ȧ�� �ٸ����
		{
			for (int j = 1; j < 8; j += 2) {
				next.y = st.y + yy[j] * now.s / now.t; // ������ŭ ����
				next.x = st.x + xx[j] * now.s / now.t;
				next.y = ((next.y % n) + n) % n; //�������� Ŀ��
				next.x = ((next.x % n) + n) % n;
				movefire.push_back({ next.y,next.x,now.m / 5,now.s / now.t,j });
			}
		}
		else // ������ ���̾���� ������ ��� ¦or ��� Ȧ�� ���
		{
			for (int j = 0; j < 8; j += 2) {
				next.y = st.y + yy[j] * now.s / now.t;
				next.x = st.x + xx[j] * now.s / now.t;
				next.y = ((next.y % n) + n) % n; //�������� Ŀ��
				next.x = ((next.x % n) + n) % n;
				movefire.push_back({ next.y,next.x,now.m / 5,now.s / now.t,j });
			}
		}
	}
}

int main() // ���� : �̵��غ� > �̵� �� �̵��غ� > �̵� �� �̵��غ� > �ݺ�
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> k;

	for (int i = 0; i < m; i++)
	{
		int r, c, mm, s, d;
		cin >> r >> c >> mm >> s >> d;
		map[r - 1][c - 1] = { mm,s,d,1 };
		fireball.push_back({ r - 1,c - 1 });
	}
	div(); // ���� 1�� �̵��غ� 
	for (int i = 0; i < k; i++)
	{
		move();
		div();
	}
	int ans = 0;
	for (int i = 0; i < movefire.size(); i++)
	{
		ans += movefire[i].m;
	}
	cout << ans;
	return 0;
}