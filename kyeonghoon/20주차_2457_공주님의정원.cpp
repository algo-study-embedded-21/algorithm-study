#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, ans;
vector<pair<int, int>> flower;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int sm, sd, em, ed;
		cin >> sm >> sd >> em >> ed;
		flower.push_back({ sm * 100 + sd,em * 100 + ed });
	}
	sort(flower.begin(), flower.end());
	int date = 301;
	while (date < 1201) {
		int next_date = date;
		//cout << next_date << '\n';
		for (int i = 0; i < flower.size(); i++) {
			if (flower[i].first <= date && flower[i].second > next_date) {
				next_date = flower[i].second;
			}
		}
		if (next_date == date) {
			cout << 0;
			return 0;
		}
		date = next_date;
		ans += 1;
	}
	cout << ans;
}
