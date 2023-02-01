#include<iostream>
#include<vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	vector<int> d(n, -1);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	d[0] = 0;
	for (int i = 0; i < n - 1; i++) {
		if (d[i] == -1)continue;
		for (int j = 1; j <= a[i]; j++) {
			if (i + j >= n)break;
			if (d[i + j] == -1 || d[i + j] > d[i] + 1) {
				d[i + j] = d[i] + 1;
			}
		}
	}
	cout << d[n - 1] << '\n';
	return 0;

}
