/*

���� ���� ����
pair<int, int> �迭�� �������� �κ��� ���� ����

*/
#include <iostream>
#include <vector>
using namespace std;

// N�� ������ 100�����ε�
// �迭�� 111�� �����ߴ� ��Ÿ�� ���� ��
pair<int, int> arr[205];
int n, k;
int cnt;

void rotate(){
	pair<int, int> temp = arr[2*n];
	for (int i = 2*n; i > 1; i--) {
		arr[i] = arr[i - 1];
	}
	arr[1] = temp;
	if (arr[n].second == 1) {
		arr[n].second = 0;
	}
}

void moveRobot() {
	for (int i = n - 1; i > 0; i--) {
		if (arr[i].second == 0) continue;
		if (arr[i + 1].first == 0) continue;
		if (arr[i + 1].second == 1) continue;
		arr[i].second = 0;
		arr[i + 1].first--;
		arr[i + 1].second = 1;
		if (arr[i + 1].first == 0) cnt++;
	}
	// ������ �κ��� N��°�� ���� �����ٴ� �κ��� ���ƾ���
	if (arr[n].second == 1) {
		arr[n].second = 0;
	}
}

void setRobot() {
	if (arr[1].first == 0) return;
	arr[1].first--;
	arr[1].second = 1;
	if (arr[1].first == 0) cnt++;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 1; i <= 2 * n; i++) {
		int x;
		cin >> x;
		arr[i] = { x, 0 };
		if (x == 0) cnt++;
	}

	int step = 0;
	while (1) {
		step++;
		rotate();

		moveRobot();

		setRobot();

		if (cnt >= k) {
			cout << step;
			break;
		}
	}

	return 0;
}