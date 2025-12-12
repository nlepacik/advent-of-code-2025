#include <fstream>
#include <iostream>

using namespace std;

int main() {
	ifstream file("input.txt");
	string line;

	int sum = 0;
	while (getline(file, line)) {
		int x;
		if ((x = line.find("x")) == string::npos) {
			continue;
		}
		
		int a = stoi(line.substr(0, x));
		int b = stoi(line.substr(x+1, line.find(":") - x - 1));

		int boxes = 0;
		while ((x = line.find(" ", x + 1)) != string::npos) {
			boxes += stoi(line.substr(x+1, 2)) * 8;
		}

		if (a*b >= boxes) sum++;

	}
	
	cout << "Part 1: " << sum << endl;

	// there was no part 2 :(
}
