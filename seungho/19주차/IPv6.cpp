#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

int main()
{
	string ip;
	stack<char> holder;	// 입력 ip 뒤에서부터 넣을 스택
	
	cin >> ip;

	int cnt_colon = 0;

	for (int i = 0; i < ip.size(); i++) {
		if (ip[i] == ':') cnt_colon++;
	}

	int group_cnt = 0;	// 방금 holder에 채운 그룹의 숫자 갯수
	for (int i = ip.size() - 1; i >= 0; i--) {
		if (ip[i] == ':') {
			// 연속으로 콜론을 넣는 경우 -> 0으로만 이뤄진 그룹(2번 축약)
			if (!holder.empty() && holder.top() == ':') {	
				holder.pop();
				for (int j = 0; j <= 7 - cnt_colon; j++) {
					holder.push({ ':' });
					for (int k = 0; k < 4; k++) holder.push({ '0' });
				}
			}

			// 숫자 뒤 콜론을 넣는 경우 -> 앞 그룹에서 부족한 0 채운다(1번 축약)
			else {											
				for (int j = 0; j < 4 - group_cnt; j++) {
					holder.push({ '0' });
				}
			}
			group_cnt = 0;
		}
		else group_cnt++;
		holder.push({ ip[i] });
	}

	// 마지막 그룹에서 부족한 0만큼 채운다.
	int size = holder.size();
	for (int i = 0; i < 39 - size; i++) {
		holder.push({ '0' });
	}
	
	while (!holder.empty()) {
		cout << holder.top();
		holder.pop();
	}

	return 0;
}
