#include<iostream>
using namespace std;

int ans;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string a, b;
	cin >> a >> b;
	int lev2 = 0;
	for (int i = 0; i < a.size(); i++) {
		int len = 0;
		for (int j = i; j < a.size(); j++) {
			for (int k = lev2; k < b.size(); k++) {
				if (a[j] == b[k]) {
					len += 1;
					lev2 = k + 1;
					break;
				}
				else {
					continue;
				}
			}
		}
		lev2 = 0;
		if (len > ans) {
			ans = len;
		}
	}
	cout << ans;
}
