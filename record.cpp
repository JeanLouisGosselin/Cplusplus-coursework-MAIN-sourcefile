#include "record.h"
#include "table.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>


//assessment functions:
record::record() {}

record::record(double score) : value(score) {
	listScores.push_front(value);
}

void record::add_score(double score) {
	listScores.push_front(score);
}

double record::best_score() const {

	double highestValue = 0;

	typedef std::deque<double>::const_iterator itr;
	for (itr p = listScores.cbegin(); p != listScores.cend(); p++) {
		if ((*p) > highestValue) {
			highestValue = (*p);
		}
	}

	return highestValue;
}

double record::overall_average() const {

	double average = 0;
	int dequeSize = static_cast<int>(listScores.size());

	if (dequeSize > 0) {

		typedef std::deque<double>::const_iterator itr;
		for (itr p = listScores.cbegin(); p != listScores.cend(); p++)
			average += (*p);

		return average / dequeSize;
	}
	else
		return average;
}

double record::recent_average() const {

	double val = 0;

	std::deque<double>temp = listScores;

	for (unsigned i = 0; i < 10; i++) {
		val += temp.front();
		temp.pop_front();
	}

	return val / 10;
}

bool record::novice() const {

	int dequeSize = static_cast<int>(listScores.size());

	if (dequeSize < 10)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

//added functions:

void record::printRecord() {

	std::cout << std::endl;
	typedef std::deque<double>::const_iterator itr;
	for (itr p = listScores.cbegin(); p != listScores.cend(); p++)
		std::cout << "\t\t" << (*p) << "\n";

	return;
}

int record::getSizeOfDeque() const {

	int dequeSize = static_cast<int>(listScores.size());

	return dequeSize;
}

double record::getScoreFromList(const int n) const {
	return listScores[n];
}
