/*******************************************************************************
 * Name    : sieve.cpp
 * Author  : Jason Rossi
 * Version : 1.0
 * Date    : September 18, 2020
 * Description : Computes the number of primes from 2 to n.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    //Use at the end of the main
    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
	const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
	int totalrows = num_primes_/primes_per_row;
	if (num_primes_ % primes_per_row > 0) {
		totalrows++;
	}
	cout << endl;
	cout << "Number of primes found: " << count_num_primes() << endl;
	cout << "Primes up to " << limit_ << ":" << endl;
	int count = 0;
	if (num_primes_ < primes_per_row)
	{
		for (int j = 0; j <= limit_; j++) {
			if (is_prime_[j] == true) {
				if (max_prime_ == j) {
					cout << j << endl;
				}
				else {
					cout << j << " ";
				}
			}
		}
		cout<<endl;
	}
	else
	{
		for (int j = 0; j <= limit_; j++) {
			if (is_prime_[j] == true)
			{
				if (count == primes_per_row - 1){
					count = 0;
					cout << setw(max_prime_width) << j << endl;
				}
				else
				{
					if (j != max_prime_)
					{
						cout << setw(max_prime_width) << j << " ";
						count++;
					}
					else
					{
						cout << setw(max_prime_width) << j << endl;
					}
				}
			}
		}
		cout<<endl;
	}
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
}

int PrimesSieve::count_num_primes() const {
	int tempCount = 0;
	for (int i = 2; i<=limit_; i++) {
		if (*(is_prime_+i) == true) {
			tempCount++;
		}
	}
    // TODO: write code to count the number of primes found
    return tempCount;
}

void PrimesSieve::sieve() {
	is_prime_[0] = false;
	is_prime_[1] = false;
	if (limit_ == 0) {
		*(is_prime_+0) = false;
	}
	if (limit_ == 1) {
		*(is_prime_+1) = false;
	}
	for (int i = 2; i<=limit_; i++) {
		*(is_prime_+i) = true;
	}
	for (int i = 2; i<= sqrt(limit_); i++)
	{
		if (*(is_prime_+i) == true) {
			for (int j = pow(i, 2); j<=limit_; j+=i) {
				*(is_prime_+j) = false;
			}
		}
	}
	for (int i = 2; i<=limit_; i++) {
		if (*(is_prime_+i) == true) {
			max_prime_ = i;
		}
	}
	num_primes_ = count_num_primes();
    // TODO: write sieve algorithm
}

int PrimesSieve::num_digits(int num) {
	int count = 0;
	while (num > 0) {
		num = num / 10;
		count++;
	}
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve ps = PrimesSieve(limit);
    ps.display_primes();
    return 0;
}
