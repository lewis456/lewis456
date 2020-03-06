#include<cstdio>
#include <memory.h>
#include<iostream>
#include<queue>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int map[26][26];
queue<pair<int, int>> q;
int n, total_num = 0;
vector<int> v;

int bfs();
int main() {
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			scanf("%1d", &map[i][j]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 1) {			//집 발견
				map[i][j] = 0;				//중복 피하기 위해 0으로 변경
				q.push(make_pair(i, j));	//집 좌표를 큐에 push
				total_num++;				//단지수++
				v.push_back(bfs());			//bfs()함수로 구한 단지 내 집의 수 벡터에 push
			}
		}
	}
	cout << total_num << endl;
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) cout << v[i] << endl;
	return 0;
}

int bfs() {
	int cnt = 1;
	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny >= n || ny < 0 || nx >= n || nx < 0) continue;
			if (map[ny][nx] == 1) {				//집 주변에 다른 집이 있다면
				cnt++;							//단지 내 집의 수 ++
				map[ny][nx] = 0;				//중복 피하기 위해 0으로 변경
				q.push(make_pair(ny, nx));		//주변 집 좌표를 큐에 push
			}
		}
	}
	return cnt;
}