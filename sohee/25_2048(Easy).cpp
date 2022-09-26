/*

1 : 30

1. 4^5���� ����� �� -> �� dfs�� �� ������ ����
2. ������ ��ġ�� �κ� / �� ������ �ű�� �κ����� ������ ����
2-1. �� ��ġ��
	- ��ĥ �� �ִ� ��(0�� �ƴ� ���) ���� �ε����� ���
	- ��ĥ �� �ִ� ��찡 �ƴϸ� ���ο� ������ ����

*/
#include <iostream>
using namespace std;

int original[21][21];
int map[21][21];
int n;

// ��, ��, ��, ��
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
int nums[5];
int answer = 0;

// ���� ������ ��ġ��
void merge(int dir) {
	int x = 0;
	int y = 0;
	int idx = 0;
	// ��, �Ϸ� �����̴� ���
	if (dir == 0 || dir == 1) {
		// ��� ���� ���� 
		for (int i = 0; i < n; i++) {
			// ���� ��� �� ������, ���� ��� �� �Ʒ����� Ȯ��
			x = dir == 1 ? n - 1 : 0;
			idx = dir == 1 ? n - 1 : 0;
			
			// ù��° ĭ�� �� ����
			int pre = map[idx][i];
			// ������ �࿡ ���� Ȯ��
			for (int j = 1; j < n; j++) {
				x += dx[dir];
				// ���� ���� 0�� ��� : ������ �� ���� -> ���ο� ������ ����
				if (pre == 0) {
					pre = map[x][i];
					idx = x;
				}
				else {
					// ������ Ȯ���� ĭ�� ���� ĭ�� ���� ���� ���
					// ��ģ �� pre�� 0 ���� (�� �� ��ģ ĭ�� �� ��ĥ �� ���� ����)
					if (pre == map[x][i]) {
						map[idx][i] *= 2;
						map[x][i] = 0;
						pre = 0;
					}
					// �ٸ� ��� ���� ���� 0�̸� pass
					// 0�� �ƴϸ� ���ο� ������ ����
					else {
						if (map[x][i] == 0) continue;
						pre = map[x][i];
						idx = x;
					}
				}
			}
		}
	}
	// ��, ��� �����̴� ���
	else if (dir == 2 || dir == 3) {
		// ��� �࿡ ���� Ȯ��
		for (int i = 0; i < n; i++) {
			y = dir == 3 ? n - 1 : 0;
			idx = dir == 3 ? n - 1 : 0;

			int pre = map[i][idx];
			for (int j = 1; j < n; j++) {
				y += dy[dir];
				if (pre == 0) {
					pre = map[i][y];
					idx = y;
				}
				else {
					if (pre == map[i][y]) {
						map[i][idx] *= 2;
						map[i][y] = 0;
						pre = 0;
					}
					else {
						if (map[i][y] == 0) continue;
						pre = map[i][y];
						idx = y;
					}
				}
			}
		}
	}
}

// �� �� �������� ����
void sort(int dir) {
	int x = 0;
	// ��, �Ϸ� ������ ���
	if (dir == 0 || dir == 1) {
		// ��� ���� ���� ����
		for (int i = 0; i < n; i++) {
			x = dir == 1 ? n - 1 : 0;
			int line[21] = { 0 };
			int idx = 0;
			// n���� ĭ Ȯ��
			for (int j = 0; j < n; j++) {
				if (map[x][i] != 0) line[idx++] = map[x][i];
				map[x][i] = 0;
				x += dx[dir];
			}
			x = dir == 1 ? n - 1 : 0;
			// 0�� �ƴ� ����ĭ�� ������ŭ
			for (int j = 0; j < idx; j++) {
				map[x][i] = line[j];
				x += dx[dir];
			}
		}
	}
	// ��, ��� ������ ���
	else if (dir == 2 || dir == 3) {
		// ��� �࿡ ���� ����
		for (int i = 0; i < n; i++) {
			x = dir == 3 ? n - 1 : 0;
			int line[21] = { 0 };
			int idx = 0;
			for (int j = 0; j < n; j++) {
				if (map[i][x] != 0) line[idx++] = map[i][x];
				map[i][x] = 0;
				x += dy[dir];
			}
			x = dir == 3 ? n - 1 : 0;
			for (int j = 0; j < idx; j++) {
				map[i][x] = line[j];
				x += dy[dir];
			}
		}
	}
}

void calc() {
	// �� �� �ʱ�ȭ���ֱ�!!!!
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j] = original[i][j];
		}
	}

	for (int i = 0; i < 5; i++) {
		merge(nums[i]);
		sort(nums[i]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			answer = max(answer, map[i][j]);
		}
	}
}

// �ִ� 5�������� ���� ã��
void dfs(int depth) {
	if (depth == 5) {
		calc();
		return;
	}

	for (int i = 0; i < 4; i++) {
		nums[depth] = i;
		dfs(depth + 1);
		nums[depth] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> original[i][j];
		}
	}

	dfs(0);
	cout << answer;

	return 0;
}