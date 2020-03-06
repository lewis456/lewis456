#include<cstdio>
#include <memory.h>
#include<iostream>
#include<queue>
#include <algorithm>

#define MAX 500
using namespace std;

int m, n;
int map[MAX][MAX];
int dp[MAX][MAX];			//map[i][j]에서 출발했을 때 도착할 경로의 수
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int method(int, int);
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> m >> n;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) cin >> map[i][j];
	}
	memset(dp, -1, sizeof(dp));

	cout << method(0, 0) << endl;
}

int method(int y, int x) {

	if (dp[y][x] != -1) return dp[y][x];
	if (y == m - 1 && x == n - 1) return 1;							//도착하면 1반환
	dp[y][x] = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= m || nx >= n || ny < 0 || nx < 0) continue;			//map을 넘어갈 경우 skip
		if (map[ny][nx] < map[y][x])									//내리막길이면
			dp[y][x] += method(ny, nx);
	}
	return dp[y][x];
}
