#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int n,m;
vector<int> A;
int ans = 2134567890;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        A.push_back(a);
    }
    int left = 0;
    int right = 0;
    sort(A.begin(), A.end());
    while (right < n)
    {
        if (A[right] - A[left] >= m && left <= right)
        {
            ans = min(ans, A[right] - A[left]);
            if (left == right)right++;
            else left++;
        }
        else right++;
    }
    cout << ans;

    return 0;
}
