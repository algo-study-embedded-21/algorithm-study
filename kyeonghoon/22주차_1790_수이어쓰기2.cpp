#include<iostream>
#include<string>
using namespace std;

int n, k;

long long cal_len(int n) {
	long long ans = 0;
	for (int num = 1, len = 1; num <= n; num *= 10, len += 1) {
		int end = num * 10 - 1;
		if (end >= n) {
			end = n;
		}
		int tmp = (end - num + 1) * len;
		ans += tmp;
	}
	return ans;
}

int search_binary(int left, int right) {
	if (left >= right) {
		return right;
	}
	int mid = (left + right) / 2;
	if (cal_len(mid) < k) {
		return search_binary(mid + 1, right);
	}
	else {
		return search_binary(left, mid);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	if (cal_len(n) < k) {
		cout << -1;
		return 0;
	}
	int num = search_binary(1, n);
	string s_num = to_string(num);
	cout << s_num[k - cal_len(num - 1) - 1];
}
