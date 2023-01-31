#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

string str;

vector<string> split(string s, char sep) {
	istringstream ss(s);
	vector<string> vec;
	string buffer;

	while (getline(ss, buffer, sep)) {
		vec.push_back(buffer);
	}

	return vec;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> str;
	vector<string> vec = split(str, ':');
	
	for (int i = 0; i < vec.size(); i++) {
		int len = vec[i].length();
		string s = "";
		int vec_len = 0;
		switch (len) {
		case 0:
			vec[i] = "0000";
			vec_len = vec.size();
			for (int j = 0; j < 8 - vec_len; j++) {
				vec.insert(vec.begin() + i, "0000");
			}
			break;
		case 1:
			s = "000" + vec[i];
			vec[i] = s;
			break;
		case 2:
			s = "00" + vec[i];
			vec[i] = s;
			break;
		case 3:
			s = "0" + vec[i];
			vec[i] = s;
			break;
		}
	}

	// ::으로 시작할 경우 1개의 0000이 축약된 것일 수 있음
	// ::1:2:3:4:5:6:7 -> 0000:0001:0002:0003:0004:0005:0006:0007
	int len = vec.size();
	int start = len - 8;

	for (int i = start; i < len; i++) {
		cout << vec[i];
		if (i == len - 1) break;
		cout << ":";
	}

	return 0;
}