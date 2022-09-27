#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 50분 컷!

using namespace std;

struct gps {
	int y;
	int x;
};

int n, L;
int map[100][100];

int yy[2] = {1,0}; // 0일때 열검사 / 1일때 행검사
int xx[2] = {0,1};

int pos(int d, gps st)
{
	gps now = st;
	int flag = 1; // 가능 여부
	int stack = 1; // 연결된 같은높이 블록수
	while (now.y + yy[d] != n && now.x + xx[d] != n) // 한줄의 끝까지
	{
		int high = map[now.y][now.x]; // 현재 높이
		gps next = { now.y + yy[d],now.x + xx[d] }; // 다음위치
		int updown = map[next.y][next.x] - high; // 다음높이 - 현재높이
		if (updown == 0) // 같은 높이인경우
		{
			stack++;
			now = next;
			continue;
		}
		else if (updown == 1) // 오르막인경우
		{
			if (stack >= L) // 경사로를 놓기 충분한 길이인 경우
			{
				now = next;
				stack = 1; // 경사로 놓고 초기화
			}
			else
			{
				flag = 0; // 길 성립 불가
				break;
			}
		}
		else if (updown == -1) // 내리막인경우
		{
			int low = 0; // 연속된 낮은 높이의 블록 수
			while (next.y < n && next.x < n && map[next.y][next.x] == high - 1) // 연속되는 동안
			{
				next = { next.y + yy[d],next.x + xx[d] };
				low++;
				if (low == L) // 경사로 놓을 공간이 확보되었다면
				{
					break;
				}
			}
			if (low == L)
			{
				now = { next.y - yy[d],next.x - xx[d] }; // 경사로 끝부분부터 조사 재개
				stack = 0; // 경사로 놓고 초기화
			}
			else // 경사로 놓을 공간이 부족한경우
			{
				flag = 0;
				break;
			}
		}
		else // 오르막 또는 내리막 경사가 1을 초과하는경우
		{
			flag = 0;
			break;
		}
	}
	return flag; // 길인경우 
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> L;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}

	int ans = 0;

	for (int i = 0; i < n; i++)
	{
		ans += pos(0, { 0,i }); // i열 검사
		ans += pos(1, { i,0 }); // i행 검사
	}

	cout << ans;

	return 0;
}