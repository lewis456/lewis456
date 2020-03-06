#include<cstdio>
#include <memory.h>
#include<iostream>
#include<queue>
#include <algorithm>

#define MAX 1001
using namespace std;

int m, n;
int map[MAX][MAX];
int dp[MAX][MAX];			//map[i][j]���� ������� �� �ִ� ���� ����
int dx[3] = { 0,1,1 };
int dy[3] = { 1,0,1 };

int method(int, int);
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	memset(dp, -1, sizeof(dp));
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) cin >> map[i][j];
	}
	
	cout << method(1, 1) << endl;
}

int method(int y, int x) {
	if (dp[y][x] != -1) return dp[y][x];
	if (y == n&&x == m) return map[y][x];

	dp[y][x] = map[y][x];
	for (int i = 0; i < 3; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny > n || nx > m) continue;
		dp[y][x] = max(dp[y][x], map[y][x] + method(ny, nx));		//�� �� �ִ� ������ ��� �� �ִ밪 dp�� ����
	}

	return dp[y][x];
}