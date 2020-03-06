#include<cstdio>
#include <memory.h>
#include<iostream>
#include<queue>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n, m;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int map[300][300], n_map[300][300];
int year = 0;
bool visited[300][300];
queue<pair<int, int>> q;

void count_mass();				//빙산덩어리 개수 카운트
int count_melt(int, int);		//녹을 빙산 높이 계산
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	memset(map, 0, sizeof(map));
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	while (1) {
		int mass = 0;
		memset(n_map, 0, sizeof(n_map));
		memset(visited, false, sizeof(visited));

		//빙산 덩어리 개수 카운트
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] != 0 && visited[i][j] == false) {
					mass++;
					q.push(make_pair(i, j));
					visited[i][j] = true;
					count_mass();
				}
			}
		}

		if (mass >= 2) {
			cout << year << endl;
			break;
		}
		if (mass == 0) {
			cout << 0 << endl;
			break;
		}

		//1년 뒤 녹는 높이 계산 후 내년 지도를 n_map에 저장
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] != 0) {
					n_map[i][j] = map[i][j] - count_melt(i,j);
					if (n_map[i][j] < 0) n_map[i][j] = 0;
				}
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				map[i][j] = n_map[i][j];
		}
		year++;
	}
	return 0;
}

void count_mass() {
	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (map[ny][nx] != 0 && visited[ny][nx] == false) {
				visited[ny][nx] = true;
				q.push(make_pair(ny, nx));
			}
		}
	}
}

int count_melt(int y, int x) {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (map[ny][nx] == 0) cnt++;
	}
	return cnt;
}