/*

1. cctv�� ��� ���ϱ�
2. �� cctv�� ���� (0~3���� ����) ���� ���ϱ�
3. ���� �� �簢���� ���� ��, �ּڰ� ����

*/

#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int x;
	int y;
	int id;
};

int n, m;
int arr[8][8];
vector<Node> cctv;
vector<int> direction;

// cctv�� �ٶ� �� �ִ� ������ ��ǥ
int dArr[4][2] = {
	// up
	{-1, 0},
	// down
	{1, 0},
	// left
	{0, -1},
	// right
	{0, 1}
};

int minsize = 2134567890;

void getArea() {
	// ��� cctv�� ���� ���� ���� Ȯ��
	int len = cctv.size();

	// map  ����
	int map[8][8] = { 0 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			map[i][j] = arr[i][j];
		}
	}

	// ������ ������ �������� cctv ����
	for (int i = 0; i < len; i++) {
		Node now = cctv[i];

		switch (now.id)
		{
		case 1: {
			// 1�� ī�޶�� �� ���⸸ 
			int x = now.x;
			int y = now.y;

			// ������ �������� ���� ��Ÿ�� ������ Ȯ��
			while (x < n && y < m && x >= 0 && y >= 0) {
				if (map[x][y] == 6) break;

				map[x][y] = -1;
				x += dArr[direction[i]][0];
				y += dArr[direction[i]][1];
			}

			break;
		}
		case 2: {
			// ���� Ȥ�� �¿츸 ���� �� �ֵ��� Ȯ���� ���� ����
			int selectD[4][2] = {
				{0, 1},
				{0, 1},
				{2, 3},
				{2, 3}
			};

			for (int j : selectD[direction[i]]) {
				int x = now.x;
				int y = now.y;

				while (x < n && y < m && x >= 0 && y >= 0) {
					if (map[x][y] == 6) break;

					map[x][y] = -1;
					x += dArr[j][0];
					y += dArr[j][1];
				}
			}

			break;
		}
		case 3: {
			// ����, ���, ����, �Ͽ� ���� ����
			int selectD[4][2] = {
				{0, 2},
				{0, 3},
				{1, 2},
				{1, 3}
			};

			for (int j : selectD[direction[i]]) {
				int x = now.x;
				int y = now.y;

				while (x < n && y < m && x >= 0 && y >= 0) {
					if (map[x][y] == 6) break;

					map[x][y] = -1;
					x += dArr[j][0];
					y += dArr[j][1];
				}
			}

			break;
		}
		case 4: {
			// �� ���� ���� �� Ȯ��
			for (int j = 0; j < 4; j++) {
				if (j == direction[i]) continue;
				int x = now.x;
				int y = now.y;

				while (x < n && y < m && x >= 0 && y >= 0) {
					if (map[x][y] == 6) break;

					map[x][y] = -1;
					x += dArr[j][0];
					y += dArr[j][1];
				}
			}

			break;
		}
		case 5: {
			// �׳� �� Ȯ��
			for (int j = 0; j < 4; j++) {
				int x = now.x;
				int y = now.y;

				while (x < n && y < m && x >= 0 && y >= 0) {
					if (map[x][y] == 6) break;

					map[x][y] = -1;
					x += dArr[j][0];
					y += dArr[j][1];
				}
			}
			break;

		}
		}
	}

	// ���� ������ �簢���� ���ϱ�
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) cnt++;
		}
	}

	// �� ���� �簢���밡 ������ ����
	minsize = min(cnt, minsize);
}

void dfs(int depth) {
	// cctv ��� �� ���� ���� ��
	if (depth == cctv.size()) {
		// ���պ� �簢���� ���ϱ�
		getArea();
		return;
	}

	// 2�� 5�� cctv�� ��� �ߺ��� �� �� ������ �� ������
	// n�� ũ�Ⱑ 8�� �����Ƿ� �׳� �� ���
	for (int j = 0; j < 4; j++) {
		direction.push_back(j);
		dfs(depth + 1);
		direction.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
			// cctv�� ��ġ, ���� ����
			if (arr[i][j] == 1 || arr[i][j] == 2 || arr[i][j] == 3 || arr[i][j] == 4 || arr[i][j] == 5)
				cctv.push_back({ i, j, arr[i][j] });
		}
	}

	// cctv�� ���� ���� ���ϱ�
	// ���� ����, �ߺ� ����
	dfs(0);

	cout << minsize;

	return 0;
}