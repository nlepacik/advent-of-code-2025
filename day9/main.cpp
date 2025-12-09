#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream file("input.txt");
	string line;

	vector<pair<int, int>> coords;

	while (getline(file, line)) {
		int comma = line.find(",");
		int x = stoi(line.substr(0, comma));
		int y = stoi(line.substr(comma+1));
		coords.push_back(pair<int, int>(x, y));
	}

	long largest = 0;
	for (int i = 0; i < coords.size(); i++) {
		for (int j = i + 1; j < coords.size(); j++) {
			long x = abs(coords[i].first - coords[j].first + 1);
			long y = abs(coords[i].second - coords[j].second + 1);
			if (x*y > largest) {
				largest = x*y;
			}
		}
	}
	
	cout << "Part 1: " << largest << endl;

	vector<int> x_coords = {0, 9999999};
	vector<int> y_coords = {0, 9999999};
	vector<vector<char>> map = vector<vector<char>>(x_coords.size() + coords.size());
	for (vector<char> &l : map) {
		l = vector<char>(y_coords.size() + coords.size());
	}

	for (pair<int, int> p : coords) {
		x_coords.push_back(p.first);
		y_coords.push_back(p.second);
	}

	sort(x_coords.begin(), x_coords.end());
	sort(y_coords.begin(), y_coords.end());

	for (int i = 0; i < coords.size(); i++) {
		int x1= find(x_coords.begin(), x_coords.end(), coords[i].first) - x_coords.begin();
		int y1= find(y_coords.begin(), y_coords.end(), coords[i].second) - y_coords.begin();
		int x2= find(x_coords.begin(), x_coords.end(), coords[(i+1)%coords.size()].first) - x_coords.begin();
		int y2= find(y_coords.begin(), y_coords.end(), coords[(i+1)%coords.size()].second) - y_coords.begin();
		for (int x = min(x1, x2); x <= max(x1, x2); x++) {
			for (int y = min(y1, y2); y <= max(y1, y2); y++) {
				map[x][y] = '#';
			}
		}
	}

	map[0][0] = 'x';
	bool changed = true;
	while (changed) {
		changed = false;
		for (int x = 0; x < map.size(); x++) {
			for (int y = 0; y < map[x].size(); y++) {
				if (map[x][y] == 'x') {
					if (x-1 >= 0 && map[x-1][y] == 0)
						map[x-1][y] = 'c';
					if (x+1 < map.size() && map[x+1][y] == 0)
						map[x+1][y] = 'c';
					if (y-1 >= 0 && map[x][y-1]  == 0)
						map[x][y-1] = 'c';
					if (y+1 < map[x].size() && map[x][y+1] == 0)
						map[x][y+1] = 'c';
				}
			}
		}
		for (int x = 0; x < map.size(); x++)
			for (int y = 0; y < map[x].size(); y++)
				if (map[x][y] == 'x')
					map[x][y] = '.';
		for (int x = 0; x < map.size(); x++)
			for (int y = 0; y < map[x].size(); y++)
				if (map[x][y] == 'c') {
					map[x][y] = 'x';
					changed = true;
				}
	}

	largest = 0;
	for (int i = 0; i < coords.size(); i++) {
		for (int j = i+1; j < coords.size(); j++) {
			pair<int, int> a = coords[i];
			pair<int, int> b = coords[j];
			int size = (abs(a.first-b.first)+1)*(abs(a.second-b.second)+1);
			if (size < largest) continue;

			pair<int, int> ul;
			ul.first = find(x_coords.begin(), x_coords.end(), min(a.first, b.first)) - x_coords.begin();
			ul.second = find(y_coords.begin(), y_coords.end(), min(a.second, b.second)) - y_coords.begin();
			pair<int, int> lr;
			lr.first = find(x_coords.begin(), x_coords.end(), max(a.first, b.first)) - x_coords.begin();
			lr.second = find(y_coords.begin(), y_coords.end(), max(a.second, b.second)) - y_coords.begin();

			bool contained = true;
			for (int x = ul.first; x <= lr.first; x++) {
				for (int y = ul.second; y <= lr.second; y++) {
					if (map[x][y] == '.') {
						contained = false;
						break;
					}
				}
			}
			if (contained)
				largest = size;
		}
	}

	cout << "Part 2: " << largest << endl;
}
