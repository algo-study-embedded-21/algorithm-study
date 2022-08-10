#include <iostream>
#include <algorithm> // min 함수 헤더파일
#include <vector>
#include <stdlib.h> // abs 함수 헤더파일
#define MAX 60
using namespace std;

// 좌표 구조체
struct Location {
    int y, x;
};

int N, M; // 도시크기, 치킨집 최대 개수
int map[MAX][MAX];

vector<Location> house;
vector<Location> chicken; // branch
vector<Location> choose;
int minDistance[100];
int choosed[100];
int sumDistance = 0;
int result = 2134567890;;

// 거리 계산을 위한 함수
int calcDistance(Location a, Location b) {
    int distance = abs(a.y - b.y) + abs(a.x - b.x);
    return distance;
}

void dfs (int level, int n) { // idx : 집을 선택하기 위한 인덱스 

    // 기저 조건 -> M개의 치킨집을 선택했다면
    if (level == M) {
        // 거리 계산
        for (int i = 0; i < house.size(); i++) { // 모든 집들에 대해
            for (int j = 0; j < choose.size(); j++) { // 고른 치킨집에 대해
                int d = calcDistance(house[i], choose[j]);
                minDistance[i] = min(minDistance[i], d); // 최소 거리 저장 (가장 가까운 치킨집 고르기)
            }
        }

        // 각 집의 최소 거리의 합
        for (int i = 0; i < house.size(); i++) {
            sumDistance += minDistance[i];
        }
        result = min(result, sumDistance);

        // 최솟값 구한 후 초기화 -> 각 경우마다 최솟값을 계속 구해야해서
        sumDistance = 0;
        for (int i = 0; i < house.size(); i++) {
            minDistance[i] = 2134567890;;
        }

        return;
    }
    
    // 재귀 구성 -> 치킨집 선택하기
    for (int i = n; i < chicken.size(); i++) {

        // 이미 선택한 치킨집이면 배제 -> 배열을 이용해서 처리하면 시간초과가 난다.
        //if (choosed[i] == 1) continue;

        // 치킨집 벡터에서 하나 선택해서 넣음
        choose.push_back(chicken[i]);
        // 선택했다고 표시
        //choosed[i] = 1;
        dfs(level+1, i+1);
        choose.pop_back();
        //choosed[i] = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio;
    cin.tie();
    cout.tie();
    
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {

            // 그래프 구성
            cin >> map[i][j];

            // 집 위치 저장
            if (map[i][j] == 1) {
                house.push_back({ i, j });
            }

            // 치킨집 위치 저장
            if (map[i][j] == 2) {
                chicken.push_back({ i, j });
            }
        }
    }

    for (int i = 0; i < house.size(); i++) {
        minDistance[i] = 2134567890;
    }

    dfs(0, 0);

    cout << result;


    return 0;
}

// 참고 : https://eremo2002.tistory.com/98