#include <iostream>
using namespace std;

int n;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
int map[500][500];
int answer;

void diffusion(int r, int c, int d) {
	// y �ڸ��� �� ����
	int total = map[r][c];
	int a = total;
	double sand[5][5] = {
		{0, 0, 0.02, 0, 0},
		{0, 0.1, 0.07, 0.01, 0},
		{0.05, 0, 0, 0, 0},
		{0, 0.1, 0.07, 0.01, 0},
		{0, 0, 0.02, 0, 0}
	};

	// y��ǥ �������� Ȯ��� �� �� ���
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int s = sand[i][j] * total;
			sand[i][j] = s;
			a -= s;
		}
	}
	sand[2][1] = a;

	// ���⿡ ���� Ȯ�� ���� ��ȯ
	for (int k = 0; k < d; k++) {
		int new_sand[5][5] = { 0 };
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 5; j++) {
				new_sand[4 - j][i] = sand[i][j];
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				sand[i][j] = new_sand[i][j];
			}
		}
	}

	// ���� ������ ���� ��� answer�� ���ϱ�
	// ���� ���� ��� map�� ���ϱ�
	for (int i = -2; i < 3; i++) {
		for (int j = -2; j < 3; j++) {
			int x = r + i;
			int y = c + j;
			if (x < 0 || x >= n || y < 0 || y >= n) {
				answer += sand[i + 2][j + 2];
				continue;
			}
			map[x][y] += sand[i + 2][j + 2];
		}
	}
}

// 1 -> 1 -> 2 -> 2 -> 3 -> 3 -> ...
// ���� ���̷� �� �� �����̰� ���̰� 1 ������
void tornado(int r, int c) {
	int dir = 0;
	int cnt = 0;
	int len = 1;

	while (1) {
		if (r <= 0 && c <= 0) break;

		// ���̸�ŭ �����̸鼭 Ȯ��
		for (int i = 0; i < len; i++) {
			if (r == 0 && c == 0) break;
			r += dx[dir];
			c += dy[dir];
			diffusion(r, c, dir);
		}

		if (cnt == 0) {
			cnt++;
		}
		else {
			len++;
			cnt = 0;
		}

		// ���� �̵� ����
		dir = (dir + 1) % 4;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	tornado(n / 2, n / 2);

	cout << answer;

	return 0;
}