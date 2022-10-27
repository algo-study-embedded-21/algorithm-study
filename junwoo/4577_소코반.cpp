#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

struct node {
	int x;
	int y;
};

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
char MAP[16][16];
int R, C;
vector<int> v;
node player;
string route;

void init() {
	route.clear();
	v.clear();
	memset(MAP, 0, sizeof(MAP));
}

int isPosibble(int x, int y, int dir) {
	if (MAP[x][y] == '#') return 1;
	if (MAP[x][y] == 'b' || MAP[x][y] == 'B') {
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		if (MAP[nx][ny] == 'b' || MAP[nx][ny] == '#' || MAP[nx][ny] == 'B') return 1;
	}
	return 0;
}

string check() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] == 'b') return "incomplete\n";
		}

	return "complete\n";
}
void move() {
	for (auto i : v) {
		if (check() == "complete\n") return;

		int nx = player.x + dx[i];
		int ny = player.y + dy[i];

		if (!isPosibble(nx, ny, i)) {
			if (MAP[player.x][player.y] == 'W') MAP[player.x][player.y] = '+';
			else MAP[player.x][player.y] = '.';

			if (MAP[nx][ny] == 'b' || MAP[nx][ny] == 'B') {
				int bnx = nx + dx[i];
				int bny = ny + dy[i];

				if (MAP[bnx][bny] == '+') MAP[bnx][bny] = 'B';
				else MAP[bnx][bny] = 'b';
			}

			if (MAP[nx][ny] == '+' || MAP[nx][ny] == 'B') MAP[nx][ny] = 'W';
			else MAP[nx][ny] = 'w';

			player.x = nx;
			player.y = ny;
		}
	}
}

int main() {
	int GM = 1;
	while (1) {
		cin >> R >> C;

		if (R == 0 && C == 0) return 0;

		cout << "Game " << GM << ": ";

		init();

		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++) {
				cin >> MAP[i][j];
				if (MAP[i][j] == 'w' || MAP[i][j] == 'W') {
					player.x = i;
					player.y = j;
				}
			}

		cin >> route;

		if (check() == "complete\n") {
			cout << "complete\n";
			GM++;
			continue;
		}

		for (int i = 0; i < route.length(); i++) {
			switch (route[i]) {
			case 'U':
				v.push_back(0);
				break;
			case 'D':
				v.push_back(1);
				break;
			case 'L':
				v.push_back(2);
				break;
			case 'R':
				v.push_back(3);
				break;
			}
		}

		move();
		cout << check();

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cout << MAP[i][j];
			}
			cout << '\n';
		}
		GM++;
	}

	return 0;
}