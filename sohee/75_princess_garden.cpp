#include<iostream>
#include<algorithm>
using namespace std;

struct Flower {
	int start_month;
	int start_day;
	int end_month;
	int end_day;
};

bool cmp(const Flower& f1, const Flower& f2) {
	if (f1.start_month < f2.start_month) return true;
	if (f1.start_month > f2.start_month) return false;
	if (f1.start_day < f2.start_day) return true;
	if (f1.start_day > f2.start_day) return false;
	if (f1.end_month < f1.end_month) return true;
	if (f1.end_month > f1.end_month) return false;
	if (f1.end_day < f2.end_day) return true;
	if (f1.end_day > f2.end_day) return false;
	return false;
}

int n, ans;
Flower flowers[100001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> flowers[i].start_month >> flowers[i].start_day >> flowers[i].end_month >> flowers[i].end_day;
	}

	sort(flowers, flowers + n, cmp);
	int end_month = 3;
	int end_day = 1;
	int next_end_month = 3;
	// 3으로 오타내서 틀렸었음
	int next_end_day = 1;

	if (flowers[0].start_month < 3 || (flowers[0].start_month == 3 && flowers[0].start_day == 1)) {
		for (int i = 0; i < n; i++) {
			// 11월 30일까지 꽃이 피어있으려면 12월 1일까지 표시된 꽃이 있어야 함
			if (next_end_month >= 12) break;
			if (flowers[i].end_month < 3) continue;

			if (flowers[i].start_month < end_month || (flowers[i].start_month == end_month && flowers[i].start_day <= end_day)) {
				if (next_end_month < flowers[i].end_month || next_end_month == flowers[i].end_month && next_end_day < flowers[i].end_day) {
					next_end_month = flowers[i].end_month;
					next_end_day = flowers[i].end_day;
				}
			}
			else {
				if (next_end_month < flowers[i].start_month || (next_end_month == flowers[i].start_month && next_end_day < flowers[i].start_day)) break;
				ans++;
				end_month = next_end_month;
				end_day = next_end_day;
				if (next_end_month < flowers[i].end_month || (next_end_month == flowers[i].end_month && next_end_day < flowers[i].end_day)) {
					next_end_month = flowers[i].end_month;
					next_end_day = flowers[i].end_day;
				}
			}
		}

		if (next_end_month < 12) ans = 0;
		else ans++;
	}

	cout << ans;


	return 0;
}