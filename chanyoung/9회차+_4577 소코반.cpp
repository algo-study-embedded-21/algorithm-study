#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
using namespace std;

//40�� ����

struct gps { int y; int x; };

char map[15][15];
vector<char> command;
int r, c;
gps ch;
int goalcnt;
int complete;
int gamecnt = 1;

int yy[4] = { 0,0,1,-1 };
int xx[4] = { 1,-1,0,0 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	while (1) {
		cin >> r >> c;
		if (r == 0 && c == 0) break; // ������ �� ó��
		command.clear();
		goalcnt = 0;
		complete = 0;
		for (int i = 0; i < r; i++)
		{
			string line;
			cin >> line;
			for (int j = 0; j < c; j++)
			{
				map[i][j] = line[j];
				if (map[i][j] == 'w')
				{
					ch = { i,j };
					map[i][j] = '.';
				}
				else if (map[i][j] == 'W')
				{
					ch = { i,j };
					map[i][j] = '+';
				}
				if (map[i][j] == 'W' || map[i][j] == '+')
				{
					goalcnt++; // ������ ���� ����
				}
				else if (map[i][j] == 'B')
				{
					goalcnt++; // ������ ���� ����
					complete++; // �̹� ������ �ڽ� ���� ����
				}
			}
		}
		string commandline;
		cin >> commandline;
		for (int i = 0; i < commandline.size(); i++)
		{
			command.push_back(commandline[i]);
		}
		for (int i = 0; i < command.size(); i++)
		{
			int direc;
			char move = command[i];
			if (move == 'U')
			{
				direc = 3;
			}
			else if (move == 'D')
			{
				direc = 2;
			}
			else if (move == 'R')
			{
				direc = 0;
			}
			else
			{
				direc = 1;
			}
			gps next = { ch.y + yy[direc],ch.x + xx[direc] };
			if (next.y<0 || next.y>r - 1 || next.x<0 || next.x>c - 1)continue;
			if (map[next.y][next.x] == '#')continue;
			if (map[next.y][next.x] == 'b' || map[next.y][next.x] == 'B') // �̵���ġ�� �ڽ��ϰ��
			{
				gps box = { next.y + yy[direc],next.x + xx[direc] }; // �ڽ��� �з����� ��ġ
				if (box.y<0 || box.y>r - 1 || box.x<0 || box.x>c - 1)continue;
				if (map[box.y][box.x] == '#' || map[box.y][box.x] == 'b' || map[box.y][box.x] == 'B')continue;
				if (map[box.y][box.x] == '+') { // ��ǥ���ϰ��
					complete++;
					map[box.y][box.x] = 'B';
				}
				else map[box.y][box.x] = 'b'; // ������ΰ��
				if (map[next.y][next.x] == 'B') { // �и��� ���ڰ� ��ǥ������ �־��ٸ�
					complete--;
					map[next.y][next.x] = '+';
				}
				else map[next.y][next.x] = '.';
			}
			ch = next;
			if (complete == goalcnt)break; // ���� �����ΰ��
		}
		if (map[ch.y][ch.x] == '+') map[ch.y][ch.x] = 'W';
		else map[ch.y][ch.x] = 'w';
		cout << "Game " << gamecnt << ": ";
		if (complete == goalcnt) cout << "complete\n";
		else cout << "incomplete\n";
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				cout << map[i][j];
			}
			cout << "\n";
		}
		gamecnt++;
	}

	return 0;
}