#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
int a[20][20];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	vector<int> v(n);
	for (int i = 0; i < n / 2; i++) {
		v[i] = 1;
	}
	int gap = 1e9;
	sort(v.begin(), v.end());
	do {
		int red = 0, blue = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (v[i] == v[j] && i!=j) {
					if (v[i] == 1) {
						blue += a[i][j];
					}
					else {
						red += a[i][j];
					}
				}
			}
		}
		if (abs(red - blue) < gap) {
			gap = abs(red - blue);
		}
	} while (next_permutation(v.begin(), v.end()));
	cout << gap;
}
