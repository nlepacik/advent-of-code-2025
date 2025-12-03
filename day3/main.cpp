#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream file("input.txt");
	string line;
	
	int sum = 0;
	long sum2 = 0;

	while (getline(file, line)) {
		int largest = 0;
		int second_largest = 0;
		for (int i = 0; i < line.length(); i++) {
			if (line[i] > line[largest]) {
				largest = i;
			}
		}

		if (largest == line.length() - 1) {
			for (int i = 0; i < largest; i++) {
				if (line[i] > line[second_largest]) {
					second_largest = i;
				}
			}
			sum += 10*(line[second_largest]-48) + line[largest] - 48;
		} else {
			second_largest = largest + 1;
			for (int i = largest + 1; i < line.length(); i++) {
				if (line[i] > line[second_largest]) {
					second_largest = i;
				}
			}
			sum += 10*(line[largest]-48) + line[second_largest] - 48;
		}

		while (line.length() != 12) {
			string largest = "0";
			for (int j = 0; j < line.length(); j++) {
				string removed = line.substr(0, j) + line.substr(j+1, line.length()-j-1);
				if (removed > largest) {
					largest = removed;
				}
			}
			line = largest;
		}
		
		sum2 += stol(line);

	}

	cout << "Part 1: " << sum << endl;
	cout << "Part 2: " << sum2 << endl;

	return 0;
}
