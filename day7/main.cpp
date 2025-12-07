#include <fstream>
#include <iostream>
using namespace std;

int main() {
	ifstream file("input.txt");
	string line;
	int splits = 0;

	getline(file, line);
	int len = line.length();
	bool* beams = new bool[len];
	long* timelines = new long[len];
	int s = line.find("S");
	beams[s] = true;
	timelines[s] = 1;
	
	while (getline(file, line)) {
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == '^' && beams[i]) {
				// part 1
				beams[i] = false;
				beams[i+1] = true;
				beams[i-1] = true;
				splits++;
				
				// part 2
				timelines[i+1] += timelines[i];
				timelines[i-1] += timelines[i];
				timelines[i] = 0;
			}
		}
	}

	cout << "Part 1: " << splits << endl;

	long sum = 0;
	for (int i = 0; i < len; i++) {
		sum += timelines[i];
	}

	cout << "Part 2: " << sum << endl;
}
