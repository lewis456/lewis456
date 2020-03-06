#include <memory.h>
#include<iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int N, P, W, L, G;
//N:총 게임 횟수, P:플레이어 정보의 수
int score = 0;
pair<string, string> info[1000];
string name, wl;
//<플레이어이름, 승패정보>

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> P;
	cin >> W >> L >> G;
	for (int i = 0; i < P; i++) {
		cin >> name >> wl;
		info[i] = make_pair(name, wl);
	}

	for (int i = 0; i < N; i++) {
		bool win = false;
		cin >> name;
		for (int j = 0; j < P; j++) {				//이기는 경우 점수 +
			if (info[j].first == name) {
				if (info[j].second == "W") {
					score += W;
					win = true;						//이긴거 체크
					break;
				}
			}	
		}

		//나머지는 모두 지는 경기
		if (win ==false) {							
			score -= L;
			if (score < 0) score = 0;
		}
		if (score >= G) {
			cout << "I AM NOT IRONMAN!!\n";
			return 0;
		}
	}
	cout << "I AM IRONMAN!!\n";

	return 0;
}