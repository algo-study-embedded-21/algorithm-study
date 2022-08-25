#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

struct Edge {
	int like, empty, x, y;
};

bool cmp(Edge a, Edge b) {
	if (a.like > b.like)return true;
	if (a.like < b.like)return false;
	if (a.empty > b.empty)return true;
	if (a.empty < b.empty)return false;
	if (a.x < b.x)return true;
	if (a.x > b.x)return false;
	if (a.y < b.y)return true;
	if (a.y > b.y)return false;
}

int n;
vector<int> v[401];
vector<int> first;
int a[20][20];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int main() {
	cin >> n;
	for (int i = 0; i < n*n; i++) {
		int num, f1, f2, f3, f4;
		cin >> num >> f1 >> f2 >> f3 >> f4;
		v[num].push_back(f1);
		v[num].push_back(f2);
		v[num].push_back(f3);
		v[num].push_back(f4);
		first.push_back(num);
	}
	for (auto num : first) {
		vector<Edge>info;

		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				if (a[x][y] != 0)continue;
				int cnt = 0;
				int ecnt = 0;
				for (int k = 0; k < 4; k++) {
					int nx = x + dx[k];
					int ny = y + dy[k];
					if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
					if (a[nx][ny] == 0) {
						ecnt += 1;
					}
					for (int p = 0; p < v[num].size(); p++) {
						if (a[nx][ny] == v[num][p]) {
							cnt += 1;
							break;
						}
					}
				}
				info.push_back({ cnt,ecnt,x,y });
			}
		}
		sort(info.begin(), info.end(), cmp);
		a[info[0].x][info[0].y] = num;
	}
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int num = a[i][j];
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
				for (auto p : v[num]) {
					if (p == a[nx][ny]) {
						cnt += 1;
						break;
					}
				}
			}
			if (cnt == 0) {
				continue;
			}
			else {
				sum += pow(10, cnt - 1);
			}
		}
	}
	cout << sum;
}
