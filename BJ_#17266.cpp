#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int map[100001];
int longest = 0;
int dim = 0;
bool first = true;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	memset(map, 0, sizeof(map));
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int loc;
		cin >> loc;
		map[loc] = 1;					//비춰진 곳은 1
	}

	//가장 긴 연속된 어두운 곳 길이 찾기
	for (int i = 0; i <= n; i++) {		//시작점부터 탐색
		if (map[i] == 0) {				//가로등 없는곳
			dim++;						//어두운곳++
		}
		else if (map[i] == 1) {			//가로등 있는곳
			if (first) {					//첫 가로등
				longest = dim;
				first = false;
			}
			else {						//그 이후의 가로등
				if ((dim+1) % 2 == 0 && (dim+1) / 2 > longest)
					longest = (dim+1) / 2;
				else if ((dim+1) % 2 == 1 && (dim+1) / 2 + 1 > longest)
					longest = (dim+1) / 2 + 1;
			}
			dim = 0;
		}
	}
	if (dim > longest) longest = dim;
	cout << longest << endl;
}