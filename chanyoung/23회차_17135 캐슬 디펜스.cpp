#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

struct gps { int y; int x; };

int n, m, di;
int ans;

vector<vector<int>> map;
vector<int> zero_line; // 초기화용
vector<gps> archer; // 궁수들의 위치

int get_dist(gps arc, gps ene)
{
    return abs(arc.y - ene.y) + abs(arc.x - ene.x);
}

bool is_enemy(vector<vector<int>> v) // 남은 적이 있는지 체크
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (v[i][j])return true;
        }
    }
    return false;
}

int attack()
{
    vector<vector<int>> tmp;
    tmp = map;
    int cnt = 0;
    while (is_enemy(tmp)) // 모든 적이 죽을때 까지
    {
        vector<gps> remove; // 죽일 적 모음
        for (int d = 0; d < 3; d++)
        {
            int dist = 300;
            gps target; // 가장 가까운 적
            gps now = archer[d];
            int flag = 0; // 죽일수 있는 적이 있는지
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (tmp[i][j] == 0)continue;
                    int now_dist = get_dist(now, { i,j });
                    if (now_dist > di)continue; // 유효 사거리 검사
                    if (dist < now_dist)continue; // 최소 거리 검사
                    if (dist == now_dist)
                    {
                        if (target.x < j)continue; // 같은 최소거리면 더 왼쪽인 적을 공격
                    }
                    dist = now_dist;
                    target = { i,j };
                    flag = 1;
                }
            }
            if (flag && tmp[target.y][target.x]==1) // 처음 공격받는 경우
            {
                tmp[target.y][target.x] = 2; // 공격받는다고 표시
                remove.push_back(target); // 죽일 리스트에 추가
                cnt++; // 카운트
            }
        }
        for (int i = 0; i < remove.size(); i++)
        {
            gps now = remove[i];
            tmp[now.y][now.x] = 0;
        }
        for (int i = n - 1; i > 0; i--)
        {
            tmp[i] = tmp[i - 1]; // 한줄씩 밀기
        }
        tmp[0] = zero_line; // 맨 윗줄은 초기화
    }
    return cnt;
}

void put_archer(int level, int st) // 궁수위치 조합으로 고르기
{
    if (level == 3)
    {
        ans = max(ans, attack());
        return;
    }
    for (int i = st; i < m; i++)
    {
        archer.push_back({ n,i });
        put_archer(level + 1, i + 1);
        archer.pop_back();
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    
    cin >> n >> m >> di;
    for (int i = 0; i < n; i++)
    {
        vector<int> v;
        for (int j = 0; j < m; j++)
        {
            int a;
            cin >> a;
            v.push_back(a);
        }
        map.push_back(v);
    }
    for (int i = 0; i < m; i++) zero_line.push_back(0); // 사이즈 맞춰 초기화 벡터 만들기
    put_archer(0, 0);
    cout << ans;
   
    return 0;
}
