#include<cstdio>
#include<iostream>
#include<queue>
#include <algorithm>

using namespace std;

int N;
int cost[1001][3];
int dp[1001][3];		//i번째 집을 j색으로 칠했을 때 최소비용

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 3; j++) cin >> cost[i][j];
	}

	for (int i = 1; i <= N; i++) {
		dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + cost[i][0];
		dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + cost[i][1];
		dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + cost[i][2];
	}

	int ans = min(dp[N][0], min(dp[N][1], dp[N][2]));
	cout << ans << endl;
}