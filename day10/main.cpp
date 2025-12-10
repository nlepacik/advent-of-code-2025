#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>

using namespace std;

struct presser {
	int constant;
	vector<int> vars;
};

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

		// put the buttons in a matrix and compute the rref
		vector<vector<double>> matrix;
		for (int i = 0; i < joltages.size(); i++) {
			matrix.push_back(vector<double>());
		}
		for (vector<bool> col : buttons) {
			for (int i = 0; i < col.size(); i++) {
				matrix[i].push_back(col[i]);
			}
		}
		for (int i = 0; i < joltages.size(); i++) {
			matrix[i].push_back(joltages[i]);
		}

		// ref
		int pivot = 0;
		unordered_set<int> free_vars;
		for (int col = 0; col < matrix[0].size() - 1; col++) {

			// find pivot
			bool found = false;
			for (int i = pivot; i < matrix.size(); i++) {
				if (matrix[i][col] != 0) {
					
					// swap rows
					vector<double> temp = matrix[i];
					matrix[i] = matrix[pivot];
					matrix[pivot] = temp;

					found = true;
					break;
				}
			}
			if (!found) {
				free_vars.insert(col);
				continue;
			}

			// make the pivot 1
			double factor = matrix[pivot][col];
			for (int i = col; i < matrix[0].size(); i++) {
				matrix[pivot][i] /= factor;
			}

			// zero out all other rows
			for (int i = pivot + 1; i < matrix.size(); i++) {
				double factor = matrix[i][col];
				for (int j = 0; j < matrix[i].size(); j++) {
					matrix[i][j] = matrix[i][j] - matrix[pivot][j] * factor;
				}
			}
			
			pivot++;
		}

		// rref
		for (int row = matrix.size() - 1; row >= 0; row--) {
			for (int col = 0; col < matrix[row].size() - 1; col++) {
				if (matrix[row][col] == 0)
					continue;
				
				for (int i = row - 1; i >= 0; i--) {
					double factor = matrix[i][col];
					for (int j = col; j < matrix[i].size(); j++) {
						matrix[i][j] -= matrix[row][j] * factor;
					}
				}
				break;
			}
		}

		if (free_vars.size() == 0) {
			int sum = 0;
			for (int i = 0; i < matrix.size(); i++) {
				sum += matrix[i][matrix[i].size() - 1];
			}
			return sum;
		}

		// need to solve for free variables
		vector<struct presser> solution;
		for (int row = 0; row < matrix.size(); row++) {
			struct presser p;
			p.constant = matrix[row][matrix[row].size() - 1];
			for (int v : free_vars) {
				p.vars.push_back(-matrix[row][v]);
			}
			solution.push_back(p);
		}

		for (struct presser p : solution) {
			int var = 1;
			cout << p.constant << " ";
			for (int v : p.vars) {
				cout << v << "x" << var << " ";
				var++;
			}
			cout << endl;
		}

		// TODO: i have to sleep ill finish this tomorrow

		return 0;
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
		// cout << line << endl << endl;
		struct machine m = parse_machine(line);
		count += m.find_least_presses_lights();
		// count2 += m.find_least_presses_joltages();
	}
	cout << "Part 1: " << count << endl;
	// cout << "Part 2: " << count2 << endl;
}
