#include <iostream>
#include <string>
using namespace std;

int LCS[1001][1001] = { 0 };

int main()
{
	string a, b;
	cin >> a >> b;

	a = 'a' + a;
	b = 'b' + b;
	
	for (int i = 1; i < a.length(); i++) {
		for (int j = 1; j < b.length(); j++) {
			if (a[i] == b[j]) LCS[i][j] = LCS[i - 1][j - 1] + 1;
			else LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
		}
	}

	cout << LCS[a.length()-1][b.length()-1];

	return 0;
}
