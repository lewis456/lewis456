#include <memory.h>
#include<iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int N, P, W, L, G;
//N:�� ���� Ƚ��, P:�÷��̾� ������ ��
int score = 0;
pair<string, string> info[1000];
string name, wl;
//<�÷��̾��̸�, ��������>

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
		for (int j = 0; j < P; j++) {				//�̱�� ��� ���� +
			if (info[j].first == name) {
				if (info[j].second == "W") {
					score += W;
					win = true;						//�̱�� üũ
					break;
				}
			}	
		}

		//�������� ��� ���� ���
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