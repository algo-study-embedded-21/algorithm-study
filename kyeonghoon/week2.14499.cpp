#include<iostream>
using namespace std;

int map[20][20];
int dice[6];

int main() {
	int n, m, x, y, k;
	cin >> n >> m >> x >> y >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	while (k--) {
		int op;
		cin >> op;
		int n_dice[6] = { 0, };
		if (op == 1) {
			y += 1;
			if (x < 0 || x >= n || y < 0 || y >= m) {y -= 1; continue;}
			n_dice[0] = dice[0];
			n_dice[1] = dice[5];
			n_dice[2] = dice[1];
			n_dice[3] = dice[2];
			n_dice[4] = dice[4];
			n_dice[5] = dice[3];
		}
		else if (op == 2) {
			y -= 1;
			if (x < 0 || x >= n || y < 0 || y >= m) { y += 1; continue; }
			n_dice[0] = dice[0];
			n_dice[1] = dice[2];
			n_dice[2] = dice[3];
			n_dice[3] = dice[5];
			n_dice[4] = dice[4];
			n_dice[5] = dice[1];
		}
		else if (op == 3) {
			x -= 1;
			if (x < 0 || x >= n || y < 0 || y >= m) { x += 1; continue; }
			n_dice[0] = dice[2];
			n_dice[1] = dice[1];
			n_dice[2] = dice[4];
			n_dice[3] = dice[3];
			n_dice[4] = dice[5];
			n_dice[5] = dice[0];
		}
		else {
			x += 1;
			if (x < 0 || x >= n || y < 0 || y >= m) { x -= 1; continue; }
			n_dice[0] = dice[5];
			n_dice[1] = dice[1];
			n_dice[2] = dice[0];
			n_dice[3] = dice[3];
			n_dice[4] = dice[2];
			n_dice[5] = dice[4];
		}
		for (int i = 0; i < 6; i++) {
			dice[i] = n_dice[i];
		}
		if (map[x][y] == 0)map[x][y] = dice[5];
		else{dice[5] = map[x][y];map[x][y] = 0;}
		cout << dice[2] << '\n';
	}
}
