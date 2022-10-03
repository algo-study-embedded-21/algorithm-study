// 2시간 10분

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

using namespace std;

struct gps
{
	int y;
	int x;
};

int n;
int map[21][21];
int group[5]; // 각 선거구의 인구합
int maxvote = -1; // 가장 인구가 많은 선거구
int minvote = 2134567890; // 가장 인구가 적은 선거구
int ans = 2134567890; // 출력값

void vote(gps st, int dl , int dr)
{
	if (st.y + dl + dr > n)
	{
		return; // 아래로 인덱스 넘어감
	}
	if (st.x - dl <1)
	{
		return; // 왼쪽으로 인덱스 넘어감
	}
	if (st.x + dr > n)
	{
		return; // 오른쪽으로 인덱스 넘어감
	}
	int left=0;
	int right=1;
	for (int i = 1; i < st.y; i++) // 다이아몬 위부분
	{
		for (int j = 1; j <= st.x; j++)
		{
			group[0] += map[i][j];
		}
		for (int j = st.x + 1; j <= n; j++)
		{
			group[1] += map[i][j];
		}
	}
	for (int i = st.y; i < st.y + dl; i++)
	{
		for (int j = 0; j < st.x - left; j++)
		{
			group[0] += map[i][j]; // 다이아 왼쪽 위 부분
		}
		left++;
	}
	for (int i = st.y; i <= st.y + dr; i++)
	{
		for (int j = st.x + right; j <= n; j++)
		{
			group[1] += map[i][j]; // 다이아 오른쪽 위부분
		}
		right++;
	}
	left = 0;
	for (int i = st.y + dl; i <= st.y + dl + dr; i++)
	{
		for (int j = 1; j < st.x - dl + left; j++)
		{
			group[2] += map[i][j]; // 다이아 왼쪽 아래 부분
		}
		left++;
	}
	right = 0;
	for (int i = st.y + dr + 1; i <= st.y + dl + dr; i++)
	{
		for (int j = st.x + dr - right; j <= n; j++)
		{
			group[3] += map[i][j]; // 다이아 오른쪽 아래부분
		}
		right++;
	}
	for (int i = st.y + dr + dl + 1; i <= n; i++) // 다이아 아래부분
	{
		for (int j = 1; j < st.x - dl + dr; j++)
		{
			group[2] += map[i][j];
		}
		for (int j = st.x - dl + dr; j <= n; j++)
		{
			group[3] += map[i][j];
		}
	}
	left = 0;
	right = 0;
	int h = 0;
	while (h<=dr+dl) // 다이아 부분
	{
		for (int j = st.x - left; j <= st.x + right; j++)
		{
			group[4] += map[st.y + h][j];
		}
		if (h < dl) // 왼쪽은 dl을 기준으로 증가에서 감소로 변화
		{
			left++;
		}
		else
		{
			left--;
		}
		if (h < dr) // 오른쪽은 dr을 기준으로 증가에서 감소로 변화
		{
			right++;
		}
		else
		{
			right--;
		}
		h++;
	}
	for (int i = 0; i < 5; i++) // 선거구 5곳에 대하여
	{
		maxvote = max(maxvote, group[i]); // 가장 인원이 많은 선거구
		minvote = min(minvote, group[i]); // 가장 인원이 적은 선거구
		group[i] = 0; // 탐색을 마친 선거구 초기화
	}
	ans = min(ans, maxvote - minvote); // 차이값이 최소인 경우로 출력 갱신
	maxvote = -1;
	minvote = 2134567890;
	vote(st, dl + 1, dr); // dl 과 dr에 대하여 두번씩 dfs 해줘야함
	vote(st, dl, dr + 1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 1; i <=n; i++)
	{
		for (int j = 1; j <=n; j++)
		{
			cin >> map[i][j];
		}
	}
	for (int i = 1; i <= n - 2; i++) 
	{ // 기준점은 dl과 dr값이 최소값인 1을 기준으로 y는 n-2 / x는 2~n-1 까지 가능
		for (int j = 2; j <= n - 1; j++)
		{
			vote({ i,j },1,1);// 최초의 dl=dr=1
		}
	}
	cout << ans;
	return 0;
}
