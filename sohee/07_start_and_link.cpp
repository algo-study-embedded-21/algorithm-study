/*

1. dfs를 이용해 팀이 될 수 있는 조합 찾기
	- 선수 중복 선택 불가능
	- 선수를 뽑는 순서는 상관 없음
2. 각 팀의 수치를 합하기 (dat에 팀 별로 번호를 저장하면 간단하게 계산 가능 할 듯)

*/

#include <iostream>
using namespace std;

int n;
int arr[21][21];
int people[21];
int minval = 2134567890;

void check() {
	int start = 0;
	int link = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (people[i] && people[j]) start += arr[i][j];
			if (!people[i] && !people[j]) link += arr[i][j];
		}
	}

	minval = min(minval, abs(start - link));
}

void dfs(int depth, int start) {
	if (depth == n / 2) {
		check();
		return;
	}

	for (int i = start; i < n; i++) {
		if (people[i]) continue;
		people[i] = 1;
		dfs(depth + 1, i + 1);
		people[i] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	dfs(0, 0);

	cout << minval;

	return 0;
}