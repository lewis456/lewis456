#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int t, n, cnt;

void sum(int s) {
	if (s == n) {
		cnt++;
		return;
	}
	if (s > n) return;		//±âÀú
	sum(s + 1);
	sum(s + 2);
	sum(s + 3);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> n;
		sum(0);
		cout << cnt << endl;
		cnt = 0;
	}

	return 0;
}