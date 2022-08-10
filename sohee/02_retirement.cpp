#include <iostream>
using namespace std;

int n;
int t[16];
int p[16];
int money[17];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		int time, price;
		cin >> time >> price;
		t[i] = time;
		p[i] = price;
	}

	for (int i = 0; i < n; i++) {
		// ������ �� ������ �޴´ٰ� �����ϰ� �� ����
		// ��� �Ⱓ�� ����Ϻ��� �� ��� ����
		if (i + t[i] > n ) continue;
		// ���� ���� �ϴ� �ͺ��� �ٸ� ���� �� ���� ���̰� �� ���ٸ� ����
		money[i + t[i]] = max(money[i] + p[i], money[i+t[i]]);
		// ���� ���� ���� �� �� �ִ� �ּ� �ݾ��� ����
		for (int j = i + t[i] + 1; j <= n; j++) {
			money[j] = max(money[j], money[i + t[i]]);
		}
	}

	cout << money[n];

	return 0;
}