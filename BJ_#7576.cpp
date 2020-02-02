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
		for (int i = 0; i < size; i++) {		//�Ϸ絿�� �ʹ� �ֺ� �丶���
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
						q.push(make_pair(ny, nx));	//������ �Ͱ� �Ǵ� �丶�� push
					}
				}
			}
		}
		rst++;									//�Ϸ簡 ����
	}

	if (raw != 0) cout << -1 << endl;
	else cout << rst << endl;

	return 0;
}