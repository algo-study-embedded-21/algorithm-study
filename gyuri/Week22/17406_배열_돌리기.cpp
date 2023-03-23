#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 2134567890
using namespace std;

struct MOVE {
	int r, c, s;
};

int n, m, k;
int arr[51][51], cpArr[51][51];
int visited[7];
MOVE memo[7];
int answer = MAX;
vector<MOVE> vec;

void input() {

	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		int r, c, s;
		cin >> r >> c >> s;
		vec.push_back({ r, c, s });
	}
}

void rotate(MOVE v) {
	
	int y1 = v.r - v.s - 1, x1 = v.c - v.s - 1;
	int y2 = v.r + v.s - 1, x2 = v.c + v.s - 1;
	int tmp[51][51] = { 0 };

	while (v.s > 0) {
		// аб
		for (int i = y1; i < y2; i++) {
			tmp[i][x1] = cpArr[i + 1][x1];
		}

		// го
		for (int i = x1; i < x2; i++) {
			tmp[y2][i] = cpArr[y2][i + 1];
		}

		// ©Л
		for (int i = y2; i > y1; i--) {
			tmp[i][x2] = cpArr[i - 1][x2];
		}

		// ╩С
		for (int i = x2; i > x1; i--) {
			tmp[y1][i] = cpArr[y1][i - 1];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (tmp[i][j] > 0) cpArr[i][j] = tmp[i][j];
			}
		}

		y1++, x1++;
		y2--, x2--;
		v.s--;
	}

	 
}


void dfs(int level) {

	if (level == k) {

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cpArr[i][j] = arr[i][j];
			}
		}

		for (int i = 0; i < k; i++) {
			rotate(memo[i]);
		}

		for (int i = 0; i < n; i++) {
			int sum = 0;
			for (int j = 0; j < m; j++) {
				sum += cpArr[i][j];
			}
			answer = min(sum, answer);
		}
	}
	for (int i = 0; i < vec.size(); i++) {
		if (visited[i] == 1) continue;
		visited[i] = 1;
		memo[level] = vec[i];
		dfs(level + 1);
		visited[i] = 0;
	}
}

void output() {

	cout << answer;
}

int main() {

	input();
	dfs(0);
	output();


	return 0;
}