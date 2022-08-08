#include <iostream>
#include <vector>
using namespace std;

int n, b, c;
vector<int> v;
// 100�� �����忡 ��� 100���� ����ְ�, �������� �� ���ۿ� ���ø� ���Ѵٸ�
// int�� ������ ��� �� ����
long long cnt;

void getSupervisor(int people) {
	// �Ѱ����� 1���� ������ �� �ִ� ��� ����
	people -= b;
	cnt++;

	// ������ ��� �Ÿ���
	if (people <= 0) return;

	// �ΰ������� �� �� �ʿ����� ����
	cnt += people / c;
	if (people % c > 0) cnt++;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		v.push_back(a);
	}
	cin >> b >> c;

	for (int a : v) {
		getSupervisor(a);
	}
	cout << cnt;

	return 0;
}
