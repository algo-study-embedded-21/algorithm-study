/*

backtracking + dat�� Ǯ �� ���� �� ����.
1. ġŲ�� ������ ���� ��
2. �ּ� ġŲ �Ÿ��� ���� �� dat ���

*/

#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int x;
	int y;
};

vector<Node> home;
vector<Node> chicken;
vector<int> arr;

int n, m;
int chArr[14];
int minDist = 2134567890;

void getChickenDistance() {
	// �� ���� ġŲ �Ÿ� �ʱ�ȭ
	int dist[100];
	for (int i = 0; i < 100; i++) dist[i] = 2134567890;

	// �� ������ ���� ª�� ġŲ �Ÿ� ����
	int len = home.size();
	for (int i = 0; i < len; i++) {
		Node now = home[i];
		for (int a : arr) {
			Node c = chicken[a];

			int d = abs(now.x - c.x) + abs(now.y - c.y);

			if (d < dist[i]) dist[i] = d;
		}
	}

	// ġŲ �Ÿ��� ��
	int cnt = 0;
	for (int i = 0; i < len; i++) {
		cnt += dist[i];
	}

	// �ּ� ġŲ �Ÿ� ����
	minDist = min(minDist, cnt);
}

void dfs(int start, int depth){
	if (depth == m) {
		getChickenDistance();
		return;
	}

	int len = chicken.size();
	// ġŲ ���� ���� ������ ��� ����
	// �ߺ����� �ʰ� ���� ��
	for (int i = start; i < len; i++) {
		if (chArr[i]) continue;
		chArr[i] = 1;
		arr.push_back(i);
		dfs(i + 1, depth + 1);
		arr.pop_back();
		chArr[i] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// �Է�
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int a;
			cin >> a;
			if (a == 1) home.push_back({ i, j });
			if (a == 2) chicken.push_back({ i, j });
		}
	}
	
	// ġŲ �� ���� �� ġŲ �Ÿ� ���ϱ�
	dfs(0, 0);
	cout << minDist;

	return 0;
}