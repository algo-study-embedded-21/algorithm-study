#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N, B, C;
	cin >> N;
	vector<int> v;
	for (int i = 0; i < N; i++) {
		int A;
		cin >> A; 
		v.push_back(A);
	}
	cin >> B >> C;
	int cnt = 0;
	while (!v.empty()) {
		int now = v.front();
		v.pop_back();
		now -= B;
		cnt++;
		if (now % C == 0) {
			cnt += now / C;
		}
		else {
			cnt += now / C +1;
		}
	}
	cout << cnt;
	return 0;

}
