#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX 1000

int n, m;
vector<int> h, a;
int rst;

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int tmp;
		cin >> tmp;
		h.push_back(tmp);
	}
	for (int i = 0; i < m; i++) {
		int tmp;
		cin >> tmp;
		a.push_back(tmp);
	}
	sort(h.begin(), h.end());
	sort(a.begin(), a.end());
	rst = h.back() + a.back();
	cout << rst << endl;
}