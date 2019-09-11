#include "record.h"
#include "table.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>

//all assessment functions:
table::table() {}

void table::add_score(const std::string& name, double score) {

	bool nameFound = false;
	record temp;

	std::map<std::string, record>::iterator itr;
	for (itr = mainMap.begin(); itr != mainMap.end(); ++itr) {

		std::string n = itr->first;

		if (compareNames(name, n) == true) {

			nameFound = true;
			temp = itr->second;
			temp.add_score(score);
			itr->second = temp;
			break;
		}
	}

	if (nameFound == true) {
		std::cout << "\n\nCongratulations! New score successfully added to the player's scoresheet!\n\n";
	}
	else
		std::cout << "\n\nSorry: name entered does not match any of the records saved in the table.\n\n";

	return;
}

int table::num_players() const {

	int result = 0;

	std::map<std::string, record>::const_iterator itr;
	for (itr = mainMap.cbegin(); itr != mainMap.cend(); ++itr) {

		std::string name = itr->first;
		record temp = itr->second;
		unsigned sizeOfList = temp.getSizeOfDeque();

		if (sizeOfList > 0)
			++result;
	}
	return result;
}

std::vector<std::string> table::print_best_recent(int n) const {

	std::multimap<double, std::string> tempAvgsAndNames;
	unsigned count = 0;
	int i = 0;

	std::map<std::string, record>::const_iterator itr;
	for (itr = mainMap.cbegin(); itr != mainMap.cend(); ++itr) {

		record temp = itr->second;

		unsigned sizeOfList = temp.getSizeOfDeque();

		double avg;

		if (sizeOfList > 0) {

			std::string name = itr->first;
			record temp = itr->second;
			avg = temp.overall_average();
			//shifting all records and names (only those that have at least one score!) to a MULTIMAP! (since two or more players may have identical averages! )
			tempAvgsAndNames.insert(std::pair<double, std::string>(avg, name));
			count++;
		}
	}

	int index = 0;
	std::vector<std::string> topList;
	std::multimap<double, std::string>::reverse_iterator rev;
	for (rev = tempAvgsAndNames.rbegin(); rev != tempAvgsAndNames.rend(); rev++) {
		if (index < n) {
			std::string np = rev->second;
			topList.push_back(np);
			index++;
		}
	}

	return topList;
}

double table::average_best() const {

	double totalSum = 0;
	int globalIndex = 0;

	std::map<std::string, record>::const_iterator itr;
	for (itr = mainMap.begin(); itr != mainMap.end(); ++itr) {

		std::string name = itr->first;
		record temp = itr->second;
		int sizeVector = temp.getSizeOfDeque();

		if (sizeVector > 0) {

			double individualBestScore = temp.best_score();
			totalSum += individualBestScore;
			++globalIndex;
		}
	}

	if (globalIndex == 0)
		return 0;
	else
		return totalSum / globalIndex;
}

std::string table::best_overall() const {

	std::string topPlayer = "0";
	const unsigned sizeTable = num_players();
	std::vector<std::string> tempList = print_best_recent(sizeTable);
	return tempList[0];
}


int table::novice_count() const {

	int count = 0;

	std::map<std::string, record>::const_iterator itr;
	for (itr = mainMap.begin(); itr != mainMap.end(); ++itr) {

		std::string name = itr->first;
		bool answer = isPlayerNovice(name);

		if (answer == true)
			++count;
	}
	return count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////


//added functions:

void table::setMap(std::map<std::string, record>& theMap) {
	mainMap.insert(theMap.begin(), theMap.end());
	return;
}

void table::printAllData() {

	std::cout << "\n\n\tNAME\tSCORES\n\n";

	std::map<std::string, record>::iterator itr;
	for (itr = mainMap.begin(); itr != mainMap.end(); ++itr) {

		std::string name = itr->first;
		record temp = itr->second;
		std::cout << "\n\t" << name;
		temp.printRecord();
		std::cout << std::endl;
	}
	return;
}

void table::printNamesScoresAverages() const {

	std::map<std::string, record>::const_iterator itr;
	for (itr = mainMap.cbegin(); itr != mainMap.cend(); ++itr) {

		std::string name = itr->first;
		record temp = itr->second;

		std::cout << "\n" << name << " -----> best score = " << temp.best_score() << std::endl;
		std::cout << "average: " << temp.overall_average() << std::endl;

		std::cout << std::endl;
	}
	return;
}

bool table::findNameInList(const std::string& s) const {

	bool nameFound = false;

	std::map<std::string, record>::const_iterator itr;
	for (itr = mainMap.begin(); itr != mainMap.end(); ++itr)
	{
		std::string name = itr->first;

		if (compareNames(s, name) == true) {
			nameFound = true;
		}
	}
	return nameFound;
}

bool table::compareNames(const std::string& s1, const std::string& s2) const {

	if (s1.compare(s2) == 0)
		return true;
	else
		return false;
}

double table::findBestScore(const std::string& s) const {

	double bestScore = 0;

	std::map<std::string, record>::const_iterator itr;
	for (itr = mainMap.begin(); itr != mainMap.end(); ++itr)
	{
		std::string name = itr->first;

		if (compareNames(s, name) == true) {

			record temp = itr->second;
			bestScore = temp.best_score();
			break;
		}
	}
	return bestScore;
}

double table::getAverageOfPlayer(const std::string& s) {

	double avg = 0;

	std::map<std::string, record>::const_iterator itr;
	for (itr = mainMap.begin(); itr != mainMap.end(); ++itr)
	{
		std::string name = itr->first;

		if (compareNames(s, name) == true) {

			record temp = itr->second;
			avg = temp.overall_average();
			break;
		}
	}
	return avg;
}

double table::getAvgTenLastScores(const std::string& s) {

	double avg = 0;

	std::map<std::string, record>::const_iterator itr;
	for (itr = mainMap.begin(); itr != mainMap.end(); ++itr) {

		std::string name = itr->first;

		if (compareNames(s, name) == true) {

			record temp = itr->second;
			int sizeV = temp.getSizeOfDeque();

			if (sizeV >= 10)
				avg = temp.recent_average();

			break;
		}
	}
	return avg;
}

bool table::isPlayerNovice(const std::string& s) const {

	bool answer;

	std::map<std::string, record>::const_iterator itr;
	for (itr = mainMap.begin(); itr != mainMap.end(); ++itr)
	{
		std::string name = itr->first;

		if (compareNames(s, name) == true) {

			record temp = itr->second;
			answer = temp.novice();
			break;
		}
	}
	return answer;
}