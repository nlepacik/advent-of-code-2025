#include <fstream>
#include <iostream>
using namespace std;

int main() {
	ifstream file("input.txt");
	string line;
	vector<string> lines;
	int sum = 0;
	int removed = -1;
	bool first = true;
	
	while (getline(file, line)) {
		lines.push_back(line);
	}
	
	while (removed != 0) {
		removed = 0;
		for (int i = 0; i < lines.size(); i++) {
			for (int j = 0; j < lines[0].length(); j++) {
				if (lines[i][j] != '@')
					continue;
				int count = 0;
				for (int k = i - 1; k <= i + 1; k++) {
					for (int l = j - 1; l <= j + 1; l++) {
						if (
								(k != i || l != j) &&
								k >= 0 &&
								k < lines.size() &&
								l >= 0 &&
								l < lines[0].length() &&
								( lines[k][l] == '@' || lines[k][l] == 'x' )
						   )
							count++;
					}
				}
				if (count < 4) {
					sum++;
					lines[i][j] = 'x';
				}
			}
		}
		
		if (first) {
			cout << "Part 1: " << sum << endl;
			first = false;
		}

		for (int i = 0; i < lines.size(); i++) {
			for (int j = 0; j < lines[0].length(); j++) {
				if (lines[i][j] == 'x') {
					lines[i][j] = '.';
					removed++;
				}
			}
		}
	}
	
	cout << "Part 2: " << sum << endl;

	return 0;
}
