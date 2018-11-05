// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	double isolated = number.at(0);
	double difference = 0;

	// Find the largest difference
	for (int i = 1; i < number.size()-1; i++) {

		// Calculate the difference between the two neighbors
		double tempDiff1 = fabs(number.at(i-1) - number.at(i));
		double tempDiff2 = fabs(number.at(i) - number.at(i+1));

		// Determine if the smaller difference is greater than the difference
		if (tempDiff1 <= tempDiff2) {
			if (tempDiff1 > difference) {
				isolated = number.at(i);
				difference = tempDiff1;
			}
		}

		if (tempDiff2 <= tempDiff1) {
			if (tempDiff2 > difference) {
				isolated = number.at(i);
				difference = tempDiff2;
			}
		}
	}

	return isolated;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	unordered_set<string> uset;
	int difference = 0;

	// Load the list of B into the set
	for (list<string>::iterator bIndex = B.begin(); bIndex != B.end(); ++bIndex) {
		uset.insert(*bIndex);
	}

	// Check for values of A that dont appear in the set
	for (list<string>::iterator aIndex = A.begin(); aIndex != A.end(); ++aIndex) {
		if (uset.find(*aIndex) == uset.end()) {
			difference++;	// key not found in set
		}
	}

	return difference;

	// list<string>::iterator aIndex = A.begin();
	// list<string>::iterator bIndex = B.begin();
	// int difference = 0;
	//
	// // Iterate over both lists to find the differences
	// while (true) {
	// 	string stringA = *aIndex;
	// 	string stringB = *bIndex;
	//
	// 	// Compare the strings and move the iterators
	// 	if (stringA.compare(stringB) == 0) {	//A equal to B
	// 		++aIndex;
	// 		++bIndex;
	// 	} else if (stringA.compare(stringB) < 0) {	// A is smaller than B
	// 		++aIndex;
	// 		difference++;
	// 	} else if (stringA.compare(stringB) > 0) {	// A is greater than B
	// 		++bIndex;
	// 		difference++;
	// 	}
	//
	// 	cout << stringA << " compared to " << stringB << " : " << "diff = " << difference << endl;
	//
	// 	// End case
	// 	if (aIndex == A.end() && bIndex == B.end()) {
	// 		return difference;
	// 	}
	// }
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
