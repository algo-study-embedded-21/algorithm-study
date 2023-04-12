#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int arr[100001];
int sub_val;
int min_val = 2134567890;

void input() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + n);

}

void find() {
	int left = 0;
	int right = 0;

	while (right <= n) {

		sub_val = arr[right] - arr[left];
		
		if (sub_val >= m) {
			min_val = min(sub_val, min_val);
			left++;
		}
		else {
			right++;
		}
	}
}

void output() {
	cout << min_val;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	input();
	find();
	output();

}