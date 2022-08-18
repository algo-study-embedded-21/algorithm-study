/*

1. ���� ������,, 
2. �ֻ����� ���ڸ� ��� �����ϸ� ������? 
	- ���⿡ ���� ������ �� �� ������ ���踦 �� �� �ִ� ������ �ʿ��� �� ������,,
	- �������� �� ���� dat�� �̿��� ǥ���غ���
3. ������ ���� ���׵� ����

*/
#include <iostream>
using namespace std;

// ���� �迭
// Ŀ�ǵ尡 1���Ͷ� 0�� �ε��� 0���� ��
int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };

// ó���� �������� ���� �κ��� 3���� �׾��µ�
// �׷� �����̳� �������� ȸ�������� ������ �ٴ� ������ ������ �� ����
int row[4];
int col[4];
int n, m, k;
int x, y;
int map[21][21];

// ȸ���ϴ� ���⿡ ���� �迭�� ����
void goToEast() {
	int a = row[3];
	for (int i = 3; i > 0; i--) {
		row[i] = row[i - 1];
	}
	row[0] = a;
	col[1] = row[1];
	col[3] = row[3];
}

void goToWest() {
	int a = row[0];
	for (int i = 0; i < 3; i++) {
		row[i] = row[i + 1];
	}
	row[3] = a;
	col[1] = row[1];
	col[3] = row[3];
}

void goToSouth() {
	int a = col[3];
	for (int i = 3; i > 0; i--) {
		col[i] = col[i - 1];
	}
	col[0] = a;
	row[1] = col[1];
	row[3] = col[3];
}

void goToNorth() {
	int a = col[0];
	for (int i = 0; i < 3; i++) {
		col[i] = col[i + 1];
	}
	col[3] = a;
	row[1] = col[1];
	row[3] = col[3];
}

void playDice(int cmd) {
	int nx = x + dx[cmd];
	int ny = y + dy[cmd];

	// ���̸� ���� ��� ����
	if (nx < 0 || nx >= n || ny < 0 || ny >= m) return;

	x = nx;
	y = ny;

	// �ֻ��� ������
	switch (cmd) {
	case 1: {
		goToEast();
		break;
	}
	case 2: {
		goToWest();
		break;
	}
	case 3: {
		goToNorth();
		break;
	}
	case 4: {
		goToSouth();
		break;
	}
	}

	// ��� ���� ���
	cout << row[1] << '\n';

	// �ٴ� ���� �ٲٱ�
	if (map[x][y] == 0) {
		map[x][y] = col[3];
	}
	else {
		// col �迭�� row �迭�� ������ �ٴ� ���� �Բ� ����
		col[3] = map[x][y];
		row[3] = map[x][y];
		map[x][y] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> x >> y >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		int cmd;
		cin >> cmd;
		playDice(cmd);
	}

	return 0;
}
