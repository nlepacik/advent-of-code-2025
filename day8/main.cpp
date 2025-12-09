#include <climits>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

struct point {
	int x;
	int y;
	int z;

	int distance_to(point other) {
		return pow(x-other.x, 2) + pow(y-other.y, 2) + pow(z-other.z, 2);
	}

	bool operator<(const point& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }
};

struct connection {
	point a;
	point b;
	int distance;

	bool operator<(const connection& other) const {
		return distance < other.distance;
	}
};

set<struct point> graph;
set<struct connection> connections;

int part_one() {
	vector<set<struct point>> circuits;
	int counter = 0;
	for (struct connection c : connections) {
		if (++counter == 1000) break;
		vector<int> added;
		for (int i = 0; i < circuits.size(); i++) {
			if (circuits[i].find(c.a) != circuits[i].end()) {
				if (circuits[i].find(c.b) == circuits[i].end())
					circuits[i].insert(c.b);
				added.push_back(i);
			} else if (circuits[i].find(c.b) != circuits[i].end()) {
				if (circuits[i].find(c.a) == circuits[i].end())
					circuits[i].insert(c.a);
				added.push_back(i);
			}
		}
		if (added.empty()) {
			set<struct point> circuit;
			circuit.insert(c.a);
			circuit.insert(c.b);
			circuits.push_back(circuit);
		} else if (added.size() > 1) {
			// need to merge two circuits
			for (struct point p : circuits[added[1]]) {
				circuits[added[0]].insert(p);
			}
			circuits[added[1]].clear();
		}
	}

	sort(circuits.begin(), circuits.end(), [](const set<struct point>& a, const set<struct point>& b) {
			return a.size() > b.size();
			});

	return circuits[0].size() * circuits[1].size() * circuits[2].size();
}

int main() {
	ifstream file("input.txt");
	string line;
	vector<struct point> points;

	while (getline(file, line)) {
		int comma1 = line.find(",");
		int comma2 = line.find(",", comma1 + 1);
		int a = stoi(line.substr(0, comma1));
		int b = stoi(line.substr(comma1 + 1, comma2 - comma1 - 1));
		int c = stoi(line.substr(comma2 + 1));
		points.push_back({a, b, c});
	}
	
	for (int i = 0; graph.size() < points.size(); i++) {
		struct connection shortest;
		shortest.distance = INT_MAX;
		for (int p1 = 0; p1 < points.size(); p1++) {
			for (int p2 = p1+1; p2 < points.size(); p2++) {
				struct connection c = {points[p1], points[p2], points[p1].distance_to(points[p2])};
				if (connections.find(c) != connections.end()) {
					continue;
				}
				if (points[p1].distance_to(points[p2]) < shortest.distance) {
					shortest = c;
				}
			}
		}
		graph.insert(shortest.a);
		graph.insert(shortest.b);
		connections.insert(shortest);

		if (i == 999) {
			cout << "Part 1: " << part_one() << endl;
			break;
		}
	}
}
