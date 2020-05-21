#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

int n, k;
long long rst = 0;
vector<pair<int, int>> jam;
vector<int> bag;
priority_queue<int> pq;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		jam.push_back(make_pair(a, b));
	}
	for (int i = 0; i < k; i++) {
		int w;
		cin >> w;
		bag.push_back(w);
	}

	sort(jam.begin(), jam.end());			//보석 무게순 오름차순 정렬
	sort(bag.begin(), bag.end());			//가방 무게순 오름차순 정렬
											//낮은 가방에 가장 비싼 보석 넣기

	//i번째 가방에 들어갈 수 있는 보석은 i+n번째 가방에도 들어갈 수 있음
	//i번째 가방에 가능한 보석을 우선순위큐에 넣고 가장비싼것 pop
	//이후 가방에서는 그보다 무거운 보석만 고려하며 큐에 넣으면 됨

	for (int i = 0, j = 0; i < k; i++) {
		while (bag[i] >= jam[j].first && j < n)
			pq.push(jam[j++].second);

		if (!pq.empty()) {
			rst += pq.top();
			pq.pop();
		}
	}
	cout << rst << endl;
	return 0;
}