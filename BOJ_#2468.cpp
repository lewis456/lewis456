#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 101

int map[MAX][MAX];
int tmp[MAX][MAX];
int max_height = 0;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int n, rst = 1;
queue<pair<int, int>> q;


void copy();

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			max_height = max(max_height, map[i][j]);
		}
	}

	for (int rain = 1; rain <= max_height; rain++) {
		copy();			//tmp에 max를 복사

						//잠기는 곳 0으로 설정
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (tmp[i][j] > rain) continue;
				tmp[i][j] = 0;
			}
		}

		int safe = 0;
		/**********안전영역 구하기*************/
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (tmp[i][j] != 0) {
					tmp[i][j] = 0;
					safe++;
					q.push(make_pair(i, j));
					//하나의 안전영역에 해당하는 곳을 돌며 0으로 설정
					while (!q.empty()) {
						int y = q.front().first;
						int x = q.front().second;
						q.pop();
						for (int k = 0; k < 4; k++) {
							int ny = y + dy[k];
							int nx = x + dx[k];
							if (ny<1 || ny>n || nx<1 || nx>n) continue;
							if (tmp[ny][nx] == 0) continue;
							tmp[ny][nx] = 0;
							q.push(make_pair(ny, nx));
						}
					}
				}
			}
		}
		rst = max(rst, safe);

	}
	cout << rst << endl;


	return 0;
}

void copy() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) tmp[i][j] = map[i][j];
	}
}