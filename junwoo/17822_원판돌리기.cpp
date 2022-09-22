#include <iostream>
#include <vector>
using namespace std;

int n, m, t;
int x, d, k;
vector<vector<int>> a;
void rotate(vector<int>& v)
{
	int cnt = k;

    if(d == 0){
	    while (cnt--) {
		    int temp = v[m];
		    for (int i = m; i >= 2; --i) {
		    	v[i] = v[i - 1];
		    }
		    v[1] = temp;
	    }
    }
    else{
        while (cnt--) {

            int temp = v[1];
            for (int i = 1; i <= m - 1; ++i) {
                v[i] = v[i + 1];
            }
            v[m] = temp;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> t;
	a = vector<vector<int>>(n + 1, vector<int>(m + 1));

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> a[i][j];

	while (t--){

		cin >> x >> d >> k;

		//회전시키기
		for (int i = 1; i <= n; ++i) {
			if (i % x == 0)
				rotate(a[i]);
		}

		//인접한 것 지우기
		vector<vector<int>> cop(a);
		bool flag = false;

		for (int i = 1; i <= n; ++i)
		{
			if (a[i][1] != 0 && a[i][1] == a[i][2]) {
				flag = true;
				cop[i][1] = 0;
				cop[i][2] = 0;
			}

			if (a[i][1] != 0 && a[i][1] == a[i][m]) {
				flag = true;
				cop[i][1] = 0;
				cop[i][m] = 0;
			}
			if (a[i][m] != 0 && a[i][m] == a[i][m - 1]) {
				flag = true;
				cop[i][m] = 0;
				cop[i][m - 1] = 0;
			}
			if (a[i][m] != 0 && a[i][m] == a[i][1]) {
				flag = true;
				cop[i][m] = 0;
				cop[i][1] = 0;
			}
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 2; j <= m - 1; ++j) {
				if (a[i][j] != 0 && a[i][j] == a[i][j - 1]) {
					flag = true;
					cop[i][j] = 0;
					cop[i][j - 1] = 0;
				}
				if (a[i][j] != 0 && a[i][j] == a[i][j + 1]) {
					flag = true;
					cop[i][j] = 0;
					cop[i][j + 1] = 0;
				}
			}

		for (int j = 1; j <= m; ++j) {
			if (a[1][j] != 0 && a[1][j] == a[2][j]) {
				flag = true;
				cop[1][j] = 0;
				cop[2][j] = 0;
			}
		}

		for (int j = 1; j <= m; ++j)
		{
			if (a[n][j] != 0 && a[n][j] == a[n - 1][j]) {
				flag = true;
				cop[n][j] = 0;
				cop[n - 1][j] = 0;
			}
		}

		for (int i = 2; i <= n - 1; ++i)
			for (int j = 1; j <= m; ++j)
			{
				if (a[i][j] != 0 && a[i][j] == a[i - 1][j]) {
					flag = true;
					cop[i][j] = 0;
					cop[i - 1][j] = 0;
				}

				if (a[i][j] != 0 && a[i][j] == a[i + 1][j]) {
					flag = true;
					cop[i][j] = 0;
					cop[i + 1][j] = 0;
				}
			}

		a = cop;

		// 합 구하기
		int sum = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				sum += a[i][j];

		//변한게 없다
		if (!flag) {

			double avg = 0;
			int cnt = 0;
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= m; ++j) {
					if (a[i][j] > 0)
						cnt++;
				}

			avg = (double)sum / (double)cnt;

			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= m; ++j) {
					if (a[i][j] > 0) {

						if (a[i][j] > avg)
							a[i][j] -= 1;
						else if (a[i][j] < avg)
							a[i][j] += 1;
					}
				}
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			ans += a[i][j];

	cout << ans << "\n";
	return 0;
}