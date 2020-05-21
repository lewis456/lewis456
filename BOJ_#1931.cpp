#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
vector<pair<int, int>> v;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int	start, end;
		cin >> start >> end;
		v.push_back(make_pair(end, start));
	}
	sort(v.begin(), v.end());		//종료시간 기준 오름차순 정렬
									//빨리 끝나는 회의들을 사용하여 결과 도출

	int current = 0, rst = 0;
	for (int i = 0; i < n; i++) {
		if (current <= v[i].second) {		//시작이 가능한 회의일 경우
			current = v[i].first;
			rst++;
		}
	}

	cout << rst << endl;

	return 0;
}