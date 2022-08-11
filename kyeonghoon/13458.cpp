#include<iostream>
#include<vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	vector<int> a(n); 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int b, c;
	cin >> b >> c;
	long long ans = 0;
	for (auto x : a) { 
		ans += 1;
		if (x > b) {
			int tmp = x - b;
			if (tmp % c == 0) {
				ans += (tmp / c);
			}
			else {
				ans += (tmp / c) + 1;
			}
		}
		else {
			continue;
		}
	}
	cout << ans;
}
