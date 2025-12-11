#include <functional>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

struct path {
	string node;
	bool dac;
	bool fft;

	bool operator==(const path& other) const {
		return node == other.node && dac == other.dac && fft == other.fft;
	}
};

namespace std {
	template <>
		struct hash<path> {
			size_t operator()(const struct path& p) const {
				return (hash<string>()(p.node) << 2) ^ (p.dac << 1) ^ p.fft;
			}
		};
}

unordered_map<string, vector<string>> graph;
unordered_map<struct path, long> memo;

int find_paths(string start) {
	if (start == "out") return 1;
	int sum = 0;
	for (string path : graph[start]) {
		sum += find_paths(path);
	}
	return sum;
}

long find_paths_2(string start, bool dac, bool fft) {

	if (start == "out") return dac && fft;
	if (start == "dac") dac = true;
	if (start == "fft") fft = true;

	struct path path_memo = { start, dac, fft };
	if (memo.find(path_memo) != memo.end())
		return memo[path_memo];

	long sum = 0;
	for (string path : graph[start]) {
		sum += find_paths_2(path, dac, fft);
	}

	memo[path_memo] = sum;
	return sum;

}

int main() {
	ifstream file("input.txt");
	string line;

	while (getline(file, line)) {
		int space = line.find(" ");
		string node = line.substr(0, space-1);
		int begin = space + 1;
		vector<string> connections;
		while ((space = line.find(" ", begin)) != string::npos) {
			connections.push_back(line.substr(begin, space - begin));
			begin = space + 1;
		}
		connections.push_back(line.substr(begin));
		graph[node] = connections;
	}

	long paths = find_paths("you");
	cout << "Part 1: " << paths << endl;

	paths = find_paths_2("svr", false, false);
	cout << "Part 2: " << paths << endl;

}
