#include <iostream>
using namespace std;

int n;
int map[21][21];

// �ݽð�������� ���ٰ� ����
int dx[] = { 1, 1, -1, -1 };
int dy[] = { -1, 1, 1, -1 };
int all;
int answer = 2134567890; 

void divide(int x, int y, int d1, int d2) {
	int arr[] = { d1, d2, d1, d2 };
	// �� ������ �α���
	int people[5] = { 0 };

	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < arr[k]; i++) {
			int nx = x + dx[k] * i;
			int ny = y + dy[k] * i;
			// �� ������ �°� x, y ��ǥ ����
			if (k == 1) {
				nx += d1;
				ny -= d1;
			}
			if (k == 2) {
				nx += (d1 + d2);
				ny += (d2 - d1);
			}
			if (k == 3) {
				nx += d2;
				ny += d2;
			}

			// �� ������ �α� ���
			if (k == 0 || k == 1) {
				for (int j = 0; j < ny; j++) {
					people[k] += map[nx][j];
				}
			}
			else if (k == 2 || k == 3) {
				for (int j = ny + 1; j < n; j++) {
					people[k] += map[nx][j];
				}
			}
		}
	}

	// x, y �̿��� ���� ���
	for (int i = 0; i < x; i++) {
		for (int j = 0; j <= y; j++) people[0] += map[i][j];
		for (int j = y + 1; j < n; j++) people[3] += map[i][j];
	}
	for (int j = y + 1; j < n; j++) people[3] += map[x][j];
	for (int i = x + d1 + d2 + 1; i < n; i++) {
		for (int j = 0; j < y - d1 + d2; j++) people[1] += map[i][j];
		for (int j = y - d1 + d2; j < n; j++) people[2] += map[i][j];
	}
	for (int j = 0; j < y - d1 + d2; j++) people[1] += map[x + d1 + d2][j];

	// 5�� �������� �� �α� - ������ ������ �α��� ���
	people[4] = all - people[0] - people[1] - people[2] - people[3];

	int minval = 2134567890;
	int maxval = 0;
	for (int i = 0; i < 5; i++) {
		// ���ű��� ��� �� ������ �����ؾ� ��
		if (people[i] == 0) return;
		minval = min(minval, people[i]);
		maxval = max(maxval, people[i]);
	}

	// ���� ���� ���� ���� �� ����
	answer = min(answer, maxval - minval);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			// ��� ������ �α� �� ���ϱ�
			all += map[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int d1 = 1; d1 < n - 1; d1++) {
				for (int d2 = 1; d2 < n - 1; d2++) {
					// ������ ����� ��츦 �����ϰ� ���
					if (i + d1 + d2 >= n) continue;
					if (j - d1 < 0 || j + d2 >= n) continue;
					divide(i, j, d1, d2);
				}
			}
		}
	}

	cout << answer;

	return 0;
}