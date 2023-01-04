#include <iostream>
using namespace std;

int n;
int arr[100000];
int ans = -2134567890;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
		ans = max(ans, sum);
		if (sum < 0) sum = 0;
	}

	cout << ans;

	return 0;
}