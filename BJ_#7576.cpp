#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int m, n, map[1001][1001];
int mx[4] = { 0,1,0,-1 };
int my[4] = { 1,0,-1,0 };
int rst = 0, raw = 0;
queue<pair<int, int>> q;

int main() {
	cin >> m >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) q.push(make_pair(i, j));
			if (map[i][j] == 0) raw++;
		}
	}
	while (!q.empty()) {
		int size = q.size();
		if (raw == 0) break;
		for (int i = 0; i < size; i++) {		//하루동안 익는 주변 토마토들
			int y = q.front().first;
			int x = q.front().second;
			q.pop();
			for (int j = 0; j < 4; j++) {
				int ny = y + my[j];
				int nx = x + mx[j];
				if (ny >= 1 && ny <= n && nx >= 1 && nx <= m) {
					if (map[ny][nx] == 0) {
						map[ny][nx] = 1;
						raw--;
						q.push(make_pair(ny, nx));	//다음날 익게 되는 토마토 push
					}
				}
			}
		}
		rst++;									//하루가 지남
	}

	if (raw != 0) cout << -1 << endl;
	else cout << rst << endl;

	return 0;
}