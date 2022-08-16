/*

1. 사용 가능한 연산자 개수를 파악한다 (dat 이용)
2. dfs로 연산자 조합을 구한다
	1) 순서 고려
	2) 중복 고려 (개수 내에서)
3. 각 조합별로 수식 계산을 한다
4. 최소와 최대를 구한다

*/

#include <iostream>
#include <vector>
using namespace std;

int n;
int nums[12];
int operators[4];
int maxValue = -2134567890;
int minValue = 2134567890;
vector<int> v;

void check() {
	int value = nums[0];
	for (int i = 0; i < n - 1; i++) {
		switch (v[i]) {
		case 0: {
			value += nums[i + 1];
			break;
		}
		case 1: {
			value -= nums[i + 1];
			break;
		}
		case 2: {
			value *= nums[i + 1];
			break;
		}
		case 3: {
			value /= nums[i + 1];
			break;
		}
		}
	}

	maxValue = max(value, maxValue);
	minValue = min(value, minValue);
}

void dfs(int level) {
	if (level == n - 1) {
		check();
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (operators[i] == 0) continue;
		v.push_back(i);
		operators[i] --;
		dfs(level + 1);
		v.pop_back();
		operators[i] ++;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		nums[i] = a;
	}

	for (int i = 0; i < 4; i++) {
		int a;
		cin >> a;
		operators[i] = a;
	}

	dfs(0);

	cout << maxValue << '\n' << minValue;

	return 0;
}