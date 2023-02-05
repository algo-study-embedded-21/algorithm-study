#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
vector<int> day; // 각 상담의 소요시간
vector<int> pay; // 각 상담의 가격
vector<int> dp; // 해당 일에 얻을수 있는 최대 금액

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int t, p;
        cin >> t >> p;
        day.push_back(t);
        pay.push_back(p);
    }
    dp.push_back(0); // 초기값 설정
    for (int i = 0; i < n; i++)
    {
        int next = i + day[i]; // i일의 상담을 맡으면 끝나는 날
        int nowp = dp[i]; // 현재날짜의 최대금액
        for (int j = i + 1; j < next; j++) // 다음날부터 일이 끝나는 날까지
        {
            if (j > n)break; // 퇴사일을 넘으면 종료
            if (dp.size() - 1 < j) dp.push_back(nowp); // 갱신된적 없는 날이라면 현재 최댓값으로 추가
            else dp[j] = max(dp[j], nowp); // 갱신된적 있다면 비교하여 최댓값으로 추가
        }
        if (next > n)continue; // 끝나는 날이 퇴사날을 넘으면 무시
        if (dp.size() - 1 < next)dp.push_back(nowp + pay[i]); // 끝나는날이 갱신된적 없는경우
        else dp[next] = max(dp[next], nowp + pay[i]); // 끝나는 날이 갱신된적 있는 경우
    }
    cout << dp[n]; // 퇴사하는 날의 최대금액

    return 0;
}
