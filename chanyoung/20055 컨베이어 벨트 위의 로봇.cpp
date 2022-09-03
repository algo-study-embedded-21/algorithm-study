#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct gps
{
	int num;
	int sit;
};

bool down(gps l, gps r) // 먼저올려놓은것일수록 뒤쪽칸에 위치한다
{
	if (l.sit < r.sit)
	{
		return true;
	}
	if (l.sit > r.sit)
	{
		return false;
	}
	return false;
}

int n, k;
int cnt = 1; // 횟수저장
gps line[200]; // num이 로봇 존재 여부 sit이 칸의 내구도
vector<gps> robott; // num이 로봇번호 (클수록 먼저놓은 로봇) sit이 로봇이 있는 칸의 번호

void turn() // 컨베이어벨트 돌리기
{
	int end = 2 * n - 1;
	gps temp = line[end];
	for (int i = end; i >0; i--)
	{
		line[i].sit = line[i-1].sit;
		line[i].num = line[i-1].num;
	}
	line[0].sit = temp.sit;
	line[0].num = temp.num;

}
void robotturn() // 로봇위치도 컨베이어벨트가 돌면 같이 돈다
{
	for (int i = robott.size()-1; i >=0; i--)
	{
		robott[i].sit++;
		if (robott[i].sit == n - 1) // 내리는 위치에 도달하면 로봇 내리기
		{
			line[n - 1].num = 0;
			robott.pop_back();
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i < 2 * n; i++)
	{
		cin >> line[i].sit;
		line[i].num = 0;
	}
	int age = 200;
	while (1)
	{
		turn(); // 컨베이어 벨트 돌림
		sort(robott.begin(), robott.end(), down); // 로봇을 올리는 위치에서 가까운순으로 정렬
		robotturn();
		for (int i = robott.size() - 1; i >= 0; i--) // 가장 먼 로봇(가장 먼저 올린 로봇) 부터 시작
		{
			int robotsit = robott[i].sit;
			if (line[robotsit + 1].sit > 0 && line[robotsit + 1].num == 0) // 다음칸에 로봇이 없고 내구도가 남아있다면
			{
				robott[i].sit++; // 로봇을 옮기고
				line[robotsit].num = 0; // 로봇이 있던칸을 비우고
				line[robotsit + 1].num = 1; // 로봇을 옮긴칸을 채우고
				line[robotsit + 1].sit--; // 옮긴칸의 내구도를 감소시킨다
			}
			if (robott[i].sit == n - 1) // 옮긴 로봇이 내리는 칸에 도착하면 로봇 내림
			{
				line[n - 1].num = 0;
				robott.pop_back();
			}
		}
		if (line[0].sit != 0 && line[0].num == 0) // 올리는 칸에 로봇이 없고 내구도가 남았다면 로봇 올리기
		{
			robott.push_back({ age, 0 });
			line[0].num = 1; // 칸 채우기
			line[0].sit--; // 내구도 감소
			age--;
		}
		int brokesit = 0; // 내구도가 0인 칸의 갯수
		for (int i = 0; i < 2 * n; i++)
		{
			if (line[i].sit == 0)
			{
				brokesit++;
			}
		}
		if (brokesit >= k)
		{
			break;
		}
		cnt++; // 횟수 올리기
	}
	cout << cnt;

	return 0;
}