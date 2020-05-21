#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

int n;
vector<int> w;
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int s;
		cin >> s;
		w.push_back(s);
	}
	sort(w.begin(), w.end());
	int ans = 1;
	for (int i = 0; i < w.size(); i++) {
		if (w[i] > ans) break;
		ans += w[i];
	}
	cout << ans << endl;
}