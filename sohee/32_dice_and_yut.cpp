#include <iostream>
#include <vector>
using namespace std;

int cmd[10];
int arr[10];
int maxvalue;
int map[4][21] = {
	{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40},
	{10, 13, 16, 19, 25, 30, 35, 40},
	{0, 20, 22, 24, 25, 30, 35, 40},
	{30, 28, 27, 26, 25, 30, 35, 40}
};
int n[4] = { 20, 7, 7, 7 };

void check()
{
	int visited[4][21] = {0};
	// ���� ��ġ <row, column>
	pair<int, int> player[4];
	for (int i = 0; i < 4; i++) player[i] = { 0, 0 };
	int value = 0;
	
	for (int i = 0; i < 10; i++) {
		// �̹� �̵��� ��ģ ���� �� �� ����
		if (player[arr[i]].first == -1) return;
		// �̵��� ��ģ ĭ
		int next = player[arr[i]].second + cmd[i];

		// ���� ������ ����
		if (next > n[player[arr[i]].first]) {
			// ���� ��ġ ����� �����
			if (map[player[arr[i]].first][player[arr[i]].second] == 40) {
				visited[0][20] = 0;
				for (int j = 1; j < 4; j++) {
					visited[j][7] = 0;
				}
			}
			else if (player[arr[i]].first != 0 && player[arr[i]].second > 3) {
				for (int j = 1; j < 4; j++) {
					visited[j][player[arr[i]].second] = 0;
				}
			}
			else {
				visited[player[arr[i]].first][player[arr[i]].second] = 0;
			}
			// ������ ���̶�� ǥ��
			player[arr[i]].first = -1;
			continue;
		}
		// �̵��� ��ģ ĭ�� �ٸ� ���� ������ �� �� ����
		if (visited[player[arr[i]].first][next]) return;
		if (player[arr[i]].first == 0) {
			if (map[player[arr[i]].first][next] == 10) {
				if (visited[1][0]) return;
			}
			else if (map[player[arr[i]].first][next] == 20) {
				if (visited[2][1]) return;
			}
			else if (map[player[arr[i]].first][next] == 30) {
				if (visited[3][0]) return;
			}
		}

		// �̵��� ĭ�� �� +
		value += map[player[arr[i]].first][next];

		// ���� ��ǥ ��� �����
		if (map[player[arr[i]].first][player[arr[i]].second] == 40) {
			visited[0][20] = 0;
			for (int j = 1; j < 4; j++) {
				visited[j][7] = 0;
			}
		}
		else if (player[arr[i]].first != 0 && player[arr[i]].second > 3) {
			for (int j = 1; j < 4; j++) {
				visited[j][player[arr[i]].second] = 0;
			}
		}
		else {
			visited[player[arr[i]].first][player[arr[i]].second] = 0;
		}

		// ���ο� ��ǥ�� �� ������
		if (player[arr[i]].first == 0) {
			if (map[player[arr[i]].first][next] == 10) {
				player[arr[i]] = { 1, 0 };
			}
			else if (map[player[arr[i]].first][next] == 20) {
				player[arr[i]] = { 2, 1 };
			}
			else if (map[player[arr[i]].first][next] == 30) {
				player[arr[i]] = { 3, 0 };
			}
			else {
				player[arr[i]].second = next;
			}
		}	
		else {
			player[arr[i]].second = next;
		}
		
		// ��ġ ǥ��
		if (map[player[arr[i]].first][player[arr[i]].second] == 40) {
			visited[0][20] = 1;
			for (int j = 1; j < 4; j++) {
				visited[j][7] = 1;
			}
		}
		else if (player[arr[i]].first != 0 && player[arr[i]].second > 3) {
			for (int j = 1; j < 4; j++) {
				visited[j][player[arr[i]].second] = 1;
			}
		}
		else {
			visited[player[arr[i]].first][player[arr[i]].second] = 1;
		}
	}

	maxvalue = max(maxvalue, value);
}

void dfs(int level)
{
	if (level == 10) {
		check();
		return;
	}

	for (int i = 0; i < 4; i++) {
		arr[level] = i;
		dfs(level + 1);
		arr[level] = 0;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	for (int i = 0; i < 10; i++) {
		cin >> cmd[i];
	}

	dfs(1);

	cout << maxvalue;

	return 0;
}