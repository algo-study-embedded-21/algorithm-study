#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 1:13 예제 일부 맞춤
// 2:01 예제 1,2,3 맞춤
// 2:15 정답


using namespace std;

struct fire {
	int m;
	int s;
	int d;
	int t; // 해당위치에 파이어볼 갯수 
};

struct gps {
	int y;
	int x;
};

struct allfire {
	int r;
	int c;
	int m;
	int s;
	int d;
};

int n, m, k;
fire map[50][50];
vector<gps> fireball; // 실제 파이어볼
vector<allfire> movefire; // 이동할 파이어볼 정보(이동전)

int yy[8] = { -1,-1,0,1,1,1,0,-1 };
int xx[8] = { 0,1,1,1,0,-1,-1,-1 };

void move() // 이동
{
	fireball.clear();
	for (int i = 0; i < movefire.size(); i++)
	{
		allfire now = movefire[i];
		if (map[now.r][now.c].m == 0) { // 맵에 불이 없는 경우 첫불
			map[now.r][now.c].d = now.d;
			fireball.push_back({ now.r,now.c });
		}
		else {
			if (map[now.r][now.c].d != -1) // 방향의 홀짝이 다른불들이 합쳐졌다면 방향을 -1로 표시
			{
				if (map[now.r][now.c].d % 2 != now.d % 2)
				{
					map[now.r][now.c].d = -1;
				}
			}
		}
		map[now.r][now.c].m += now.m;
		map[now.r][now.c].s += now.s;
		map[now.r][now.c].t += 1; // 그 위치에 파이어볼 갯수 누적
	}
}

void div() // 나눠짐과 동시에 어디로 이동하는지 파악(이동 준비)
{
	movefire.clear();
	for (int i = 0; i < fireball.size(); i++)
	{
		gps st = fireball[i];
		fire now = map[st.y][st.x];
		map[st.y][st.x] = { 0,0,0,0 };
		gps next;
		if (now.t == 1) // 파이어볼이 한개라면 나눠지지 않는다
		{
			next.y = st.y + yy[now.d] * now.s;
			next.x = st.x + xx[now.d] * now.s;
			next.y = ((next.y % n) + n) % n; //음수까지 커버
			next.x = ((next.x % n) + n) % n;
			movefire.push_back({ next.y,next.x,now.m ,now.s,now.d });
			continue;
		}
		if (now.m / 5 == 0) // 합쳐진 파이어볼이 나눠진 질량이 0이라면 소멸
		{
			continue;
		}
		if (now.d == -1) // 합쳐진 파이어볼들 방향의 짝/홀이 다른경우
		{
			for (int j = 1; j < 8; j += 2) {
				next.y = st.y + yy[j] * now.s / now.t; // 갯수만큼 나눔
				next.x = st.x + xx[j] * now.s / now.t;
				next.y = ((next.y % n) + n) % n; //음수까지 커버
				next.x = ((next.x % n) + n) % n;
				movefire.push_back({ next.y,next.x,now.m / 5,now.s / now.t,j });
			}
		}
		else // 합쳐진 파이어볼들의 방향이 모두 짝or 모두 홀인 경우
		{
			for (int j = 0; j < 8; j += 2) {
				next.y = st.y + yy[j] * now.s / now.t;
				next.x = st.x + xx[j] * now.s / now.t;
				next.y = ((next.y % n) + n) % n; //음수까지 커버
				next.x = ((next.x % n) + n) % n;
				movefire.push_back({ next.y,next.x,now.m / 5,now.s / now.t,j });
			}
		}
	}
}

int main() // 과정 : 이동준비 > 이동 후 이동준비 > 이동 후 이동준비 > 반복
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> k;

	for (int i = 0; i < m; i++)
	{
		int r, c, mm, s, d;
		cin >> r >> c >> mm >> s >> d;
		map[r - 1][c - 1] = { mm,s,d,1 };
		fireball.push_back({ r - 1,c - 1 });
	}
	div(); // 최초 1번 이동준비 
	for (int i = 0; i < k; i++)
	{
		move();
		div();
	}
	int ans = 0;
	for (int i = 0; i < movefire.size(); i++)
	{
		ans += movefire[i].m;
	}
	cout << ans;
	return 0;
}
