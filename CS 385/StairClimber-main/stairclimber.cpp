/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Jason Rossi
 * Date        : 10/2/20
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
	vector<vector<int>> a;
	vector<vector<int>> b;
	vector<int> c;
	if (num_stairs <= 0) {
		a.push_back(c);
	}
	else {
		for (int i = 1; i < 4; i++) {
			if (num_stairs >= i) {
				b = get_ways(num_stairs - i);
				for (int j = 0, k = b.size(); j < k; j++) {
					b[j].insert(b[j].begin(), i);
				}
				a.insert(a.end(), b.begin(), b.end());
			}
		}
	}
	return a;
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
}

int num_digits(int num) {
	int count = 0;
	while (num > 0) {
		num = num / 10;
		count++;
	}
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    return count;
}

void display_ways(const vector< vector<int> > &ways) {
	int width = num_digits(ways.size());
	for (int i = 0, f = ways.size(); i <= f; i++) {
		int abc = 0;
		int extra = ways[i].size();
		cout << setw(width) << i + 1 << ". [";
		while (abc < extra - 1)
		{
			cout << ways[i][abc] << ", ";
			abc++;
		}
		cout << ways[i][abc] << "]" << endl;
	}
	cout << endl;
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
}

int main(int argc, char * const argv[]) {
	vector< vector<int> > ways;
	if (argc != 2) {
		cout << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}
	istringstream iss;
	float num_stairs = 0;
	iss.str(argv[1]);
	if (!(iss >> num_stairs) || num_stairs < 0 || (int)num_stairs != num_stairs) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	ways = get_ways(num_stairs);

	if(num_stairs > 1) {
		cout << ways.size() << " ways to climb " << num_stairs << " stairs." << endl;
		display_ways(ways);
	}
	else {
		cout << ways.size() << " way to climb " << num_stairs << " stair." << endl;
		display_ways(ways);
	}

	return 0;
}
