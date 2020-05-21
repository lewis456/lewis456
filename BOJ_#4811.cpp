#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

long long dp[31][31];
//������w��, ������h�� ���� �� ������ ����� ��
int n;

long long method(int, int);

int main() {
	for (int i = 0; i < 1000; i++) {
		memset(dp, -1, sizeof(dp));
		cin >> n;
		if (n == 0) break;
		cout << method(n, 0)<<endl;
	}
	return 0;
}

long long method(int w, int h) {
	if (dp[w][h] != -1) return dp[w][h];

	//������ ¥���� ���ٸ� �������� �Դ� ����
	if (w == 0) return 1;				

	dp[w][h] = method(w - 1, h + 1);		//������¥���� �Դ� ���
	if (h > 0) {							//������¥�� �Դ� ���
		dp[w][h] += method(w, h - 1);
	}
	
	return dp[w][h];
}