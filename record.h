#pragma once

#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <deque>


class record {

private:

	double value;
	std::deque<double> listScores;

public:

	//assessment functions:
	record();
	record(double);
	void add_score(double);
	double best_score() const;
	double overall_average() const;
	double recent_average() const;
	bool novice() const;

	//added functions:
	void printRecord();
	int getSizeOfDeque() const;
	double getScoreFromList(const int) const;

};

#endif

