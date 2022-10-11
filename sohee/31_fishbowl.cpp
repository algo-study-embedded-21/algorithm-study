#include <iostream>
#include <vector>
using namespace std;

int bowl[101];
int map[101][101];
int n, k;
vector<int> v;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

struct node {
	int x1;
	int y1;
	int x2;
	int y2;
	int d;
};

int check()
{
	// �ּҰ�, �ִ밪 ����, �ּҰ� ����Ʈ �� ���� ó��
	int minval = 2134567890;
	int maxval = 0;
	v.clear();
	for (int i = 0; i < n; i++) {
		if (minval > bowl[i]) {
			minval = bowl[i];
			v.clear();
			v.push_back(i);
		}
		else if (minval == bowl[i]) v.push_back(i);
		maxval = maxval < bowl[i] ? bowl[i] : maxval;
	}

	return maxval - minval;
}

void stack_bowl()
{
	int idx = 0;
	// �ű� �κ��� ����ŷ
	int mask[2] = { 1, 1 };

	for (int i = 0; i < n; i++) {
		map[0][i] = bowl[i];
	}

	while (1) {
		if (idx + mask[0] + mask[1] > n) break;
		for (int i = 0; i < mask[0]; i++) {
			for (int j = 0; j < mask[1]; j++) {
				map[mask[1] - j][idx + mask[1] + i] = map[i][idx + j];
				map[i][idx + j] = -1;
			}
		}
		idx += mask[1];
		// (1, 1), (2, 1), (2, 2), (3, 2) ... ����ŷ �ϴ� ĭ�� �þ�� ��Ģ
		if (mask[0] == mask[1]) mask[0]++;
		else mask[1]++;
	}
}

void stack_bowl2()
{
	int idx = 0;
	int mask[2] = { 1, n/2 };

	for (int i = 0; i < n; i++) {
		map[0][i] = bowl[i];
	}

	for (int t = 0; t < 2; t++) {
		for (int i = 0; i < mask[0]; i++) {
			for (int j = 0; j < mask[1]; j++) {
				map[mask[0] * 2 - i - 1][idx + mask[1] * 2 - j - 1] = map[i][idx + j];
				map[i][idx + j] = -1;
			}
		}
		idx += mask[1];
		mask[0] *= 2;
		mask[1] /= 2;
	}
}

void move_fish()
{
	vector<node> v;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == -1) continue;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (map[nx][ny] == -1) continue;
				if (abs(map[i][j] - map[nx][ny]) < 5) continue;
				// �ݴ��� ���� �ٸ� ĭ���� ó��
				if (map[i][j] > map[nx][ny]) {
					v.push_back({ i, j, nx, ny, (map[i][j] - map[nx][ny]) / 5 });
				}
			}
		}
	}

	for (auto move : v) {
		// 0 ���ϰ� �� ���ɼ��� ����,,
		map[move.x1][move.y1] -= move.d;
		map[move.x2][move.y2] += move.d;
	}
}

void sort()
{
	int idx = 0;
	// ������ �°� �� ĭ�� �ƴ� ���� ����
	for (int j = 0; j < n; j++) {
		if (map[0][j] == -1) continue;
		if (idx >= n)break;
		for (int i = 0; i < n; i++) {
			if (map[i][j] == -1) break;
			bowl[idx++] = map[i][j];
			map[i][j] = -1;
		}
	}
}

void organize()
{
	// 1. ����� �� ������ �ֱ�
	for (int i : v) bowl[i] ++;

	// 2. ���� �ױ�
	stack_bowl();

	// 3. ����� �� ����
	move_fish();

	// 4. �Ϸķ� ����
	sort();

	// 5. ���� �ױ�2
	stack_bowl2();

	// 6. ����� �� ����
	move_fish();

	// 7. �Ϸķ� ����
	sort();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// �ʱ�ȭ
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j] = -1;
		}
	}
	for (int i = 0; i < n; i++) {
		cin >> bowl[i];
	}

	int answer = 0;
	while (1) {
		// k Ȯ��
		if (check() <= k) break;

		// ����
		organize();

		answer++;
	}

	cout << answer;

	return 0;
}