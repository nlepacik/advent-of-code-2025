#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream file("input.txt");
	string line;

	int dial = 50;
	int count = 0;
	int count2 = 0;

	while (getline(file, line)) {
		int num = stoi(line.substr(1));
		switch (line[0]) {
			case 'L':
				for (int i = 0; i < num; i++) {
					dial -= 1;
					dial = dial % 100;
					if (dial == 0) {
						count2++;
					}
				}
				break;
			case 'R':
				for (int i = 0; i < num; i++) {
					dial += 1;
					dial = dial % 100;
					if (dial == 0) {
						count2++;
					}
				}
				break;
			default:
				cout << "bad line\n";
				return 1;
		}
		if (dial == 0) {
			count++;
		}
	}

	cout << "Part 1: " << count << endl;
	cout << "Part 2: " << count2 << endl;

	return 0;
}
