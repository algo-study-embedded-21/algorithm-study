#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

long long n, k;

long long get_length()
{
    long long length = 0;
    int res = n;
    long long N = 9;
    int i = 1;
    while (res - N >= 0)
    {
        res -= N;
        length += i * N;
        N *= 10;
        i++;
    }
    length += i * res;
    return length;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> k;
    long long length = get_length();
    if (length < k) cout << "-1";
    else
    {
        long long N = 9; 
        int i = 1;
        long long next = 0;
        while (k >= i * N) // N을 long long으로 하지 않는경우 i*N 연산 자체가 int가 되어 터진다
        {
            k -= i * N;
            next += N;
            N *= 10;
            i++;
        }
        next += k / i;
        int last = k % i;
        if (last == 0)
        {
            cout << next % 10;
        }
        else
        {
            next++;
            next = next / pow(10, i - last);
            cout << next % 10;
        }
    }

    return 0;
}
