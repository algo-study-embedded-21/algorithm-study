/*

���� ��Ϲ����� ���� ���� ���¿��� ���ư� ��Ϲ����� ��ȣ�� ������ ã�ƾ� ��
vector�� ���� �� �� ���� ȸ��

*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int gear[4][8];
int k;
// ȸ���� ������ ��ȣ, ȸ�� ���� ����
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
	// ���� ��Ϲ��� Ȯ��
	while (n < 3) {
		if (gear[n][2] != gear[n + 1][6]) v.push_back({ n + 1, d * -1 });
		else break;
		n++;
		// ��Ϲ������� ������ �ٸ��� ���ư�
		d *= -1;
	}

	n = num;
	d = dir;
	// ���� ��Ϲ��� Ȯ��
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