#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

string s;

string go_4(string s) {
	string ans = s;
	while (ans.length() != 4) {
		ans = "0" + ans;
	}
	return ans;
}

int main() {
	cin >> s;
	vector<string> parts; // 부분 문자열 담는 곳
	istringstream str(s); //파싱 준비
	string part; //파싱된 부분 문자열
	while (getline(str, part, ':')) {
		parts.push_back(part);
	}
	if (count(parts.begin(), parts.end(), "") > 1) { // ::1 대비
		parts.erase(find(parts.begin(), parts.end(), ""));
	}
	if (parts.size() < 8) { //8묶음이 안 된다.
		auto it = find(parts.begin(), parts.end(),"");
		it = parts.erase(it);
		parts.insert(it, 8 - parts.size(), "0"); // 8묶음이 될 때까지 0을 넣음 
	}
	for (int i = 0; i < parts.size(); i++) {
		cout << go_4(parts[i]);
		if (i != 7) {
			cout << ":";
		}
	}

}
