#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// 59�� ���� 1,2,3 ����
// 1:05 ����

struct gps { int y, x; };
struct unit { int num, d; }; // num = ������ ���� , d = ����
struct info { gps g; int stack; }; // gps = ��ġ , stack = �׿��� ����

int n, k;
int color[12][12]; // �� ��ġ�� �� ����
vector<unit> map[12][12];
vector<info> chess;

int yy[4] = { 0,0,-1,1 };
int xx[4] = { 1,-1,0,0 };

int back(int d) // �ݴ���� ��ȯ �Լ�
{
	if (d == 0 || d == 2) return d + 1;
	else return d - 1;
}

int game()
{
	int turn = 1;
	int flag = 0;
	while (turn <= 1000)
	{
		for (int i = 0; i < k; i++)
		{
			info ch = chess[i]; // ���� ������ �� ����
			gps now = ch.g; // ���� �����̴� ���� ��ġ
			int d = map[now.y][now.x][ch.stack].d; // ������ ���� ����
			gps next = { now.y + yy[d],now.x + xx[d] }; // ������ ��ġ
			if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1 || color[next.y][next.x] == 2) // ������ �ٲ�� �ϴ°��
			{
				d = back(d);
				next = { now.y + yy[d],now.x + xx[d] };
				map[now.y][now.x][ch.stack].d = d;
				if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1 || color[next.y][next.x] == 2) continue;// �������̴� ���
			}
			if (color[next.y][next.x] == 1) // ������
			{
				int size = map[now.y][now.x].size();
				for (int j = size - 1; j >= ch.stack; j--) // �� �������� �ش� ������ ��������
				{
					unit top = map[now.y][now.x][j];
					map[next.y][next.x].push_back(top);
					chess[top.num] = { next, int(map[next.y][next.x].size() - 1) };
					map[now.y][now.x].pop_back();
					if (map[next.y][next.x].size() >= 4){
						flag = 1;
						break;
					}
				}
			}
			else // ���
			{
				int size = map[now.y][now.x].size();
				for (int j = ch.stack; j < size; j++) // �ش� ������ �� �������� �״��
				{
					unit top = map[now.y][now.x][j];
					map[next.y][next.x].push_back(top);
					chess[top.num] = { next, int(map[next.y][next.x].size() - 1) };
					if (map[next.y][next.x].size() >= 4) {
						flag = 1;
						break;
					}
				}
				if (!flag) // ���������� pop������ ���� ����
				{
					for (int a = 0; a < size - ch.stack; a++)
					{
						map[now.y][now.x].pop_back();
					}
				}
			}
			if (flag) break;
		}
		if (flag) break;
		turn++;
	}
	return turn;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> color[i][j];
		}
	}
	for (int i = 0; i < k; i++)
	{
		int y, x, d;
		cin >> y >> x >>d;
		map[y - 1][x - 1].push_back({ i ,d-1 });
		chess.push_back({ { y - 1,x - 1 }, 0 });
	}
	int turn = game();
	if (turn > 1000) cout << "-1";
	else cout << turn;

	return 0;
}