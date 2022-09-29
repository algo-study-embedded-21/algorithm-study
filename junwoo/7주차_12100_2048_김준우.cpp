#include <iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int N;
int MAP[20][20];
int maxval = -2134567890;
int cnt = -2134567890;

void copy_map(int aa[20][20], int bb[20][20]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			bb[i][j] = aa[i][j];
		}
	}
}

void turn(int xx[20][20], int k) {
	int tmp[20][20];
	for (int p = 0; p < k; p++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				tmp[i][j] = xx[N - j - 1][i];
			}
		}
		copy_map(tmp, xx);
	}
}

void pulldown() {
    for (int i = 0; i < 10; i++) {
        int height = 0;
        for (int j = N - 1; j >= 0; j--) {
            if (MAP[j][i] == 0)
                height++;
            else {
                if (height > 0) {
                    MAP[j + height][i] = MAP[j][i];
                    MAP[j][i] = 0;
                }
            }
        }
    }
}

void sumVal(){
    for(int i = N-1; i >= 0; i--){
        for(int j = 0; j < N; j++){
            if(MAP[i][j]){
                for(int k = i-1; k >= 0; k--){
                    if(MAP[k][j] != 0 && MAP[i][j] == MAP[k][j]){
                            MAP[i][j] += MAP[k][j];
                            MAP[k][j] = 0;
                            break;
                    }
                }
            }
        }
    }
    pulldown();
}

void dfs(int level,int xx[20][20]){
    if(level == 5){
        for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++){
                cnt = max(cnt,MAP[i][j]);
            }

        maxval = max(cnt,maxval);
        return;
    }
    int copy[20][20] = { 0 };

    for(int i = 0; i < 4; i++){
        copy_map(xx, copy);
		turn(copy, i);
        sumVal();

        dfs(level + 1,copy);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin >> N;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
            cin >> MAP[i][j];
        }

    dfs(0,MAP);

    

    cout << maxval << '\n';
}