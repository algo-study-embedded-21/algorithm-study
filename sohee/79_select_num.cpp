#include <iostream>
#include <algorithm>
using namespace std;

int n;
long long m;
long long arr[100000];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> arr[i];

	int left = 0, right = 0;
	sort(arr, arr + n);

	int ans = 2134567890;
	while (left <= right) {
		if (right >= n) break;
		long long sub = arr[right] - arr[left];
		if(sub >= m){
			ans = ans > sub ? sub : ans;
			left++;
		}
		else {
			right++;
		}
	}

	cout << ans;

	return 0;
}
