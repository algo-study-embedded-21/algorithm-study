#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

int a[102][102];
int r, c, k;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> a[i][j];
		}
	}
	int max_r = 3, max_c = 3;
	int time = 0;
	while (true) {
		
		if (a[r][c] == k) {
			break;
		}
		if (max_r >= max_c) {
			for (int i = 1; i <= max_r; i++) {
				map<int, int> num;
				vector<pair<int,int>> v;
				for (int j = 1; j <= max_c; j++) {
					if (a[i][j] == 0)continue;
					num[a[i][j]] += 1;
				}
				for (auto p : num) {
					v.push_back({ p.second,p.first });
				}
				sort(v.begin(), v.end());
				int cnt = 0;
				int val = 0;
				for (int j = 1; j <= 99 ; j += 2) {
					a[i][j] = v[cnt].second;
					a[i][j + 1] = v[cnt].first;
					cnt += 1;
					val = j + 2;
					if (cnt > (int)v.size() - 1)break;
					
				}
				max_c = max(max_c, (int)v.size() * 2);
				for (int j = val; j <= 100; j++) {
					a[i][j] = 0;
				}
			}
		}
		else {
			for (int i = 1; i <= max_c; i++) {
				map<int, int> num;
				vector<pair<int, int>> v;
				for (int j = 1; j <= max_r; j++) {
					if (a[j][i] == 0)continue;
					num[a[j][i]] += 1;
				}
				for (auto p : num) {
					v.push_back({ p.second,p.first });
				}
				sort(v.begin(), v.end());
				
				int cnt = 0;
				int val = 0;
				for (int j = 1; j <= 99; j += 2) {
					a[j][i] = v[cnt].second;
					a[j+1][i] = v[cnt].first;
					cnt += 1;
					val = j + 2;
					if (cnt > (int)v.size() - 1)break;
				}
				for (int j = val; j <= 100; j++) {
					a[j][i] = 0;
				}
				max_r = max(max_r, (int)v.size() * 2);

			}
		}
		if (time == 101)break;
		time++;
	}
	if (time == 101) {
		cout << -1;
		return 0;
	}
	cout << time;
}
