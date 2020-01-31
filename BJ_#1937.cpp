#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, map[501][501] = { 0 }, dp[501][501] = { 0 }, k = 0;
//dp: (x,y)에서 시작했을 때 최대 k
int mv_x[4] = { 0,1,0,-1 };
int mv_y[4] = { 1,0,-1,0 };

int method(int y, int x) {
	if (dp[y][x] > 0) 
		return dp[y][x]+1;

	for (int i = 0; i < 4; i++) {
		int nx = x + mv_x[i];
		int ny = y + mv_y[i];
		if (nx > 0 && nx <= n&&ny > 0 && ny <= n) {
			if (map[y][x] < map[ny][nx]) {
				dp[y][x] = max(dp[y][x], method(ny, nx));
			}
		}
	}
	return dp[y][x]+1;		//일단 하루는 살기 때문에 +1
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			k = max(k, method(i, j));
		}
	}
	cout << k << endl;
	return 0;
}