#include<cstdio>
#include<iostream>
#include<queue>
#include <algorithm>

using namespace std;

int n;
int time[16], pay[16];
int dp[16];					//i번째 날 부터 시작할 때 버는 최대 금액

int method(int);
int main() {
	cin >> n;
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= n; i++) cin >> time[i] >> pay[i];

	cout << method(1) << endl;
}

int method(int day) {		//day=현재 날짜
	if (day > n) return 0;
	if (dp[day] != -1) return dp[day];
	
	if ((day + time[day] - 1) <= n) 		//이날 일을 해도 퇴사 전이라면
		dp[day] = max(pay[day] + method(day + time[day]), method(day + 1));		//이날 일하기 vs 이날 일 안하기
	else									//퇴사 전까지 일을 못끝낸다면
		dp[day] = method(day + 1);			

	return dp[day];
}