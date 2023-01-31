#include<iostream>
#include<cstring>
using namespace std;
long long d[101][21];
int a[101];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	d[0][a[0]] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 21; j++) {
			if (j >= a[i]) {
				d[i][j] += d[i - 1][j - a[i]];
			}
			if (j + a[i] <= 20) {
				d[i][j] += d[i - 1][j + a[i]];
			}
		}
	}
	cout << d[n - 2][a[n - 1]]<<'\n';
}
