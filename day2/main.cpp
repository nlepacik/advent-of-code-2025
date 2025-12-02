#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
	ifstream file("input.txt");
	string input;
	getline(file, input);

	long sum = 0;
	long sum2 = 0;
	stringstream ss(input);
	string range;
	while (getline(ss, range, ',')) {
		int dash = range.find('-');
		long first = stol(range.substr(0, dash));
		long last = stol(range.substr(dash+1));

		for (long n = first; n <= last; n++) {
			string ns = to_string(n);
			int len = ns.length();

			for (int i = len/2; i >= 1; i--) {
				if (len % i != 0) 
					continue;
				
				bool valid = false;
				for (int s = 0; s < len - i; s += i) {
					// cout << ns.substr(s, i) << " and " << ns.substr(s+i, i) << endl;
					if (ns.substr(s, i) != ns.substr(s+i, i)) {
						valid = true; 
						break;
					}
				}
				// cout << ns << " " << valid << endl;
				if (!valid) {
					sum2 += n;
					if (len/i == 2)
						sum += n;
					break;
				}
			}
		}
	}
	
	cout << "Part 1: " << sum << endl;
	cout << "Part 2: " << sum2 << endl;

	return 0;
}
