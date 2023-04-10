#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> A;

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		A.push_back(num);
	}

	sort(A.begin(), A.end());

	int left = 0;
	int right = 0;

	int ans = 2134567890;

	while (left <= right) {
		if (right >= N) break;
		if (A[right] - A[left] == M) {
			cout << M;
			return 0;
		}
		if (A[right] - A[left] < M) right++;
		else {
			ans = min(ans, A[right] - A[left]);
			left++;
		}
	}

	cout << ans;
	
	return 0;
}
