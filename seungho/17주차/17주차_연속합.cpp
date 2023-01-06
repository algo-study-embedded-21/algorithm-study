#include <iostream>
using namespace std;

int sumList[100001];

int main()
{
	int n;
	cin >> n;
	cin >> sumList[1];

	int minSum = min(0,sumList[1]);
	int ans = sumList[1];

	for (int i = 2; i <= n; i++) {
		int num;
		cin >> num;

		sumList[i] = sumList[i - 1] + num;
		ans = max(ans, sumList[i] - minSum);
		minSum = min(minSum, sumList[i]);
	}

	cout << ans;

	return 0;
}
