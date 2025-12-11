#include <climits>
#include <iostream>
#include <fstream>
#include <queue>
#include <stdexcept>
#include <unordered_set>
#include <z3++.h>

using namespace std;

struct machine {
	vector<bool> lights;
	vector<vector<bool>> buttons;
	vector<int> joltages;

	long find_least_presses_lights() {
		queue<vector<bool>> q;
		q.push(vector<bool>(lights.size()));
		int presses = 0;
		int counter = q.size();

		unordered_set<vector<bool>> checked;

		while (q.front() != lights) {
			vector<bool> front = q.front();
			q.pop();
			for (vector<bool> button : buttons) {
				vector<bool> newlights;
				for (int i = 0; i < lights.size(); i++) {
					newlights.push_back(front[i] ^ button[i]);
				}
				if (checked.find(newlights) == checked.end()) {
					q.push(newlights);
					checked.insert(newlights);
				}
			}
			if (--counter == 0) {
				presses++;
				counter = q.size();
			}
		}
		return presses;
	}

	long find_least_presses_joltages() {
		z3::context c;
		z3::optimize opt(c);

		vector<z3::expr> presses;
		for (int i = 0; i < buttons.size(); i++) {
			presses.push_back(c.int_const(("x" + to_string(i)).c_str()));
			opt.add(presses[i] >= 0);
		}

		for (int i = 0; i < joltages.size(); i++) {
			z3::expr sum = c.int_val(0);
			for (int j = 0; j < buttons.size(); j++) {
				if (buttons[j][i] == true) {
					sum = sum + presses[j];
				}
			}
			opt.add(sum == c.int_val(joltages[i]));
		}

		z3::expr total = c.int_val(0);
		for (z3::expr& p : presses) {
			total = total + p;
		}
		opt.minimize(total);

		if (opt.check() != z3::sat) {
			throw new runtime_error("unsat");
		}

		z3::model m = opt.get_model();
		int result = 0;
		for (z3::expr& p : presses) {
			result += m.get_const_interp(p.decl()).get_numeral_int();
		}

		return result;
	}
};

struct machine parse_machine(string line) {
	struct machine m;
	int space = line.find(" ");

	// lights
	for (int i = 1; i < space - 1; i++) {
		m.lights.push_back(line[i] == '#');
	}

	// buttons
	int begin = space + 1; 
	while ((space = line.find(" ", begin)) != string::npos) {
		vector<bool> button(m.lights.size());
		for (int i = begin + 1; i < space - 1; i += 2) {
			button[(int) line[i] - 48] = true;
		}
		m.buttons.push_back(button);
		begin = space + 1;
	}

	// joltages
	begin++;
	while ((space = line.find(",", begin)) != string::npos) {
		m.joltages.push_back(stoi(line.substr(begin, space - begin)));
		begin = space + 1;
	}
	m.joltages.push_back(stoi(line.substr(begin, line.size() - 1 - begin)));

	return m;
}

int main() {
	ifstream file("input.txt");
	string line;

	long count = 0;
	long count2 = 0;
	while (getline(file, line)) {
		struct machine m = parse_machine(line);
		count += m.find_least_presses_lights();
		count2 += m.find_least_presses_joltages();
	}
	cout << "Part 1: " << count << endl;
	cout << "Part 2: " << count2 << endl;
}
