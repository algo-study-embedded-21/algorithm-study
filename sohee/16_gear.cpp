/*

아직 톱니바퀴가 돌지 않은 상태에서 돌아갈 톱니바퀴의 번호와 방향을 찾아야 함
vector에 저장 후 한 번에 회전

*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int gear[4][8];
int k;
// 회전할 바퀴의 번호, 회전 방향 저장
vector<pair<int, int>> v;

void toRight(int num) {
	int temp = gear[num][7];
	for (int i = 7; i > 0; i--) {
		gear[num][i] = gear[num][i - 1];
	}
	gear[num][0] = temp;
}

void toLeft(int num) {
	int temp = gear[num][0];
	for (int i = 0; i < 7; i++) {
		gear[num][i] = gear[num][i + 1];
	}
	gear[num][7] = temp;
}

void rotate(int num, int dir) {
	v.clear();
	int n = num;
	int d = dir;
	// 뒷쪽 톱니바퀴 확인
	while (n < 3) {
		if (gear[n][2] != gear[n + 1][6]) v.push_back({ n + 1, d * -1 });
		else break;
		n++;
		// 톱니바퀴마다 방향이 다르게 돌아감
		d *= -1;
	}

	n = num;
	d = dir;
	// 앞쪽 톱니바퀴 확인
	while (n > 0) {
		if (gear[n][6] != gear[n - 1][2]) v.push_back({ n - 1, d * -1 });
		else break;
		n--;
		d *= -1;
	}

	if (dir == 1) toRight(num);
	else toLeft(num);

	for (auto next : v) {
		if (next.second == 1) {
			toRight(next.first);
		}
		else {
			toLeft(next.first);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	for (int i = 0; i < 4; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < 8; j++) {
			gear[i][j] = s[j] - '0';
		}
	}

	cin >> k;
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		rotate(a - 1, b);
	}

	int score = 0;
	for (int i = 0; i < 4; i++) {
		if (gear[i][0]) score += pow(2, i);
	}

	cout << score;

	return 0;
}