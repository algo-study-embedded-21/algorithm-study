#include <iostream>
#include <queue>
using namespace std;

int main()
{
	int n, b, c;
	cin >> n;
	queue<int> q;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		q.push(a);
	}
	cin >> b >> c;
	long long cnt = 0;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		if (now > b) {
			now -= b;
			cnt++;
		}
		else {
			cnt++;
			continue;
		}
		if (now % c == 0) {
			cnt += now / c;
		}
		else {
			cnt += now / c + 1;
		}
	}
	cout << cnt;

	return 0;

}
