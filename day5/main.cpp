#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream file("input.txt");
	string line;
	vector<pair<long, long>> ranges;
	int sum = 0;
	long sum2 = 0;

	while (getline(file, line)) {
		if (line == "") break;

		int dash = line.find("-");
		long n = stol(line.substr(0, dash));
		long m = stol(line.substr(dash+1));

		// need to deal with overlapping ranges
		for (int i = 0; i < ranges.size(); i++) {
			auto r = ranges[i];
			if (n <= r.second && n >= r.first) {
				i = -1;
				n = r.second + 1;
			}
			if (m <= r.second && m >= r.first) {
				i = -1;
				m = r.first - 1;
			}
			if (m >= r.second && n <= r.first) {
				ranges.erase(ranges.begin() + i);
				i = -1;
			}
		}

		if (m < n) continue;

		ranges.push_back(pair<long, long>(n,m));
	}

	while (getline(file, line)) {
		long n = stol(line);
		for (auto r : ranges) {
			if (n >= r.first && n <= r.second) {
				sum++;
				break;
			}
		}
	}

	for (auto r : ranges) {
		sum2 += (r.second - r.first + 1);
	}

	cout << "Part 1: " << sum << endl;
	cout << "Part 2: " << sum2 << endl;
	
}
