#include <iostream>
using namespace std;

char cube[6][3][3] = {
	{{'w','w','w'},
	{'w','w','w'},
	{'w','w','w'}},
	{{'r','r','r'},
	{'r','r','r'},
	{'r','r','r'}},
	{{'y','y','y'},
	{'y','y','y'},
	{'y','y','y'}},
	{{'o','o','o'},
	{'o','o','o'},
	{'o','o','o'}},
	{{'g','g','g'},
	{'g','g','g'},
	{'g','g','g'}},
	{{'b','b','b'},
	{'b','b','b'},
	{'b','b','b'}},
};

int sequence[3][4] = {
	{1,5,2,4},
	{0,5,2,4},
	{0,1,2,3}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	int test_case;
	cin >> test_case;
	for (int t = 0; t < test_case; t++) {
		int n;
		cin >> n;

		for (int c = 0; c < n; c++) {
			char a[2];
			cin >> a;
			int s, r;
			if (a[0] == 'U') {
				s = 0;   // sequence 행
				r = 0;  // 돌리는 행(열)
			}
			else if (a[0] == 'D') {
				s = 0;
				r = 2;
			}
			else if (a[0] == 'F') {
				s = 1;  
			}
			else if (a[0] == 'B') {

			}
			else if (a[0] == 'L') {

			}
			else if (a[0] == 'R') {

			}
		}
	}

	




	return 0;
}
