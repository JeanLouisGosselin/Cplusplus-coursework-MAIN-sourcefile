#pragma once

#ifndef TABLE_H
#define TABLE_H

#include "record.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>


class table {

private:

	std::map<std::string, record> mainMap;

public:

	//assessment functions:
	table();
	void add_score(const std::string&, double);
	int num_players() const;
	std::vector<std::string> print_best_recent(int) const;
	double average_best() const;
	std::string best_overall() const;
	int novice_count() const;

	//added functions:
	void setMap(std::map<std::string, record>&);
	void printAllData();
	void printNamesScoresAverages() const;
	bool findNameInList(const std::string&) const;
	bool compareNames(const std::string&, const std::string&) const;
	double findBestScore(const std::string&) const;
	double getAverageOfPlayer(const std::string&);
	double getAvgTenLastScores(const std::string& s);
	bool isPlayerNovice(const std::string& s) const;
	
};

#endif
