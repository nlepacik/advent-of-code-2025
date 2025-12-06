#include <fstream>
#include <iostream>

using namespace std;

int main() {
	ifstream file("input.txt");
	string line;
	vector<string> lines;
	vector<int> p;
	long sum = 0;

	while (getline(file, line)) {
		lines.push_back(line + " ");
		int n = 0;
		while (line[n] == ' ')
			n++;
		p.push_back(n);
	}

	bool ended = false;
	while (!ended) {
		vector<int> ints;
		char op;
		for (int i = 0; i < lines.size(); i++) {
			int space = lines[i].find(" ", p[i]);
			string segment = lines[i].substr(p[i], space - p[i]);
			p[i] = space;
			while (p[i] != -1 && p[i] != lines[i].length() && lines[i][p[i]] == ' ') {
				p[i]++;
			}
			if (p[i] == -1 || p[i] == lines[i].length()) {
				ended = true;
			}
			if (segment == "+" || segment == "*") {
				op = segment[0];
			} else {
				ints.push_back(stoi(segment));
			}
		}
		long s = ints[0];
		for (int i = 1; i < ints.size(); i++) {
			if (op == '+') {
				s += ints[i];
			} else {
				s *= ints[i];
			}
		}
		sum += s;
	}

	cout << "Part 1: " << sum << endl;

	sum = 0;
	int max = 0;
	for (string s : lines)
		if (s.length() > max)
			max = s.length();

	vector<int> ints;
	char op;
	for (int i = 0; i < max; i++) {
		int n = 0;
		for (string line : lines) {
			char c = line[i];
			if (c == ' ')
				continue;
			else if (c == '+' || c == '*')
				op = c;
			else {
				n *= 10;
				n += (int)c - 48;
			}
		}
		if (n == 0) {
			long s = ints[0];
			for (int i = 1; i < ints.size(); i++) {
				if (op == '+') {
					s += ints[i];
				} else {
					s *= ints[i];
				}
			}
			sum += s;
			ints.clear();
		} else {
			ints.push_back(n);
		}
	}

	cout << "Part 2: " << sum << endl;
}
