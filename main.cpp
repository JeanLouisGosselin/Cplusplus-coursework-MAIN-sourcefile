#include "table.h"
#include "record.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <fstream>

void inputAutomaticData(std::map<std::string, record>&);
void inputManualData(std::map<std::string, record>&);
std::vector<std::string> splitInitialString(const std::string &s);
void validateEnteredName(std::string&, const table&);
void enterScore(double&);
void enterNumPlayers(int&, const int);

int main() {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////		PART 1 : INPUT FROM FILE	//////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::map<std::string, record> mainMap;
	table bigTable;
	std::string tempName;
	double newScore;

	inputAutomaticData(mainMap);
	bigTable.setMap(mainMap);
	/*
	//for testing only:
	fullTable.printAllData();
	*/
	bigTable.printNamesScoresAverages();
	std::cout << "\n\nThere are " << bigTable.num_players() << " players with at least one score.\n\n";
	std::string n = bigTable.best_overall();
	std::cout << "\nThe player with the highest overall average is: " << n << std::endl;
	std::cout << "\nThe average of the best scores of all players is: " << bigTable.average_best() << std::endl;
	int numberP = 5;
	std::cout << "\nNames of people who have the top " << numberP << " averages (in decreasing order) :\n\n";
	std::vector<std::string>topDogs = bigTable.print_best_recent(numberP);

	typedef std::vector<std::string>::const_iterator i;
	for (i p = topDogs.cbegin(); p != topDogs.cend(); p++) {
		std::cout << "\t" << (*p) << std::endl;
	}

	std::cout << "\n\nThere are " << bigTable.novice_count() << " players that are novices (ie: that have less than 10 scores).\n";


	std::string nameForNewScore = "Joy";
	newScore = 23.5;
	bigTable.add_score(nameForNewScore, newScore);


	bigTable.printNamesScoresAverages();
	std::cout << "\n\nThere are " << bigTable.num_players() << " players with at least one score.\n\n";
	n = bigTable.best_overall();
	std::cout << "\nThe player with the highest overall average is: " << n << std::endl;
	std::cout << "\nThe average of the best scores of all players is: " << bigTable.average_best() << std::endl;
	numberP = 3;
	std::cout << "\nNames of people who have the top " << numberP << " averages (in decreasing order) :\n\n";
	topDogs = bigTable.print_best_recent(numberP);
	for (i p = topDogs.cbegin(); p != topDogs.cend(); p++) {
		std::cout << "\t" << (*p) << std::endl;
	}
	std::cout << "\n\nThere are " << bigTable.novice_count() << " players that are novices (ie: that have less than 10 scores).\n";

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////		PART 2 : MANUAL INPUT	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::map<std::string, record> myMap;
	table fullTable;

	//////////////////////////////////////////////////////////////////////////////////////////

	inputManualData(myMap);
	fullTable.setMap(myMap);
	std::cout << "\n\nLet's find a name in the table and add a new score to that name!\n\n";
	validateEnteredName(tempName, fullTable);
	enterScore(newScore);
	fullTable.add_score(tempName, newScore);
	fullTable.printAllData();

	//////////////////////////////////////////////////////////////////////////////////////////

	std::cout << "\n\nThere are " << fullTable.num_players() << " players for whom a score has been added.\n";

	//////////////////////////////////////////////////////////////////////////////////////////

	std::cout << "\n\nEnter name of player to see player's best score so far: ";
	validateEnteredName(tempName, fullTable);
	double best = fullTable.findBestScore(tempName);
	std::cout << "\n\nBest score so far added to " << tempName << "'s records is: " << best << "\n\n";

	//////////////////////////////////////////////////////////////////////////////////////////

	std::cout << "\n\nEnter name to find that player's overall average: ";
	validateEnteredName(tempName, fullTable);
	double avg = fullTable.getAverageOfPlayer(tempName);
	std::cout << "\n\nOverall average of " << tempName << "'s records is: " << avg << "\n\n";


	//////////////////////////////////////////////////////////////////////////////////////////

	std::cout << "\n\nEnter name to find the average of that player's 10 latest scores: ";
	validateEnteredName(tempName, fullTable);
	double a = fullTable.getAvgTenLastScores(tempName);
	if (a != 0)
		std::cout << "\n\nThe average of " << tempName << "'s last 10 recorded scores is: " << a << "\n\n";
	else
		std::cout << "\n\nSorry: this player's total number of scores is lower than 10.\n\n";

	//////////////////////////////////////////////////////////////////////////////////////////

	std::cout << "\n\nEnter name of a player to find out if that player is a novice (ie: has less than scores on his active scorecheet): ";
	validateEnteredName(tempName, fullTable);
	bool theTruth = fullTable.isPlayerNovice(tempName);
	if (theTruth == true)
		std::cout << "\n\n" << tempName << " is most definitely a novice!\n\n";
	else
		std::cout << "\n\nBy no means is " << tempName << " a novice!\n\n";

	//////////////////////////////////////////////////////////////////////////////////////////

	const unsigned max = fullTable.num_players();
	int w;
	std::cout << "\n\nEnter number n to print names of n players who have the highest averages: ";
	enterNumPlayers(w, max);
	std::vector<std::string> topList = fullTable.print_best_recent(w);
	std::cout << "\n\nNames of those who have the top " << w << " averages (in decreasing order, from highest to lowest):\n\n";
	for (int i = 0; i < w; i++)
		std::cout << "\n" << topList[i];
	std::cout << "\n\n";

	////////////////////////////////////////////////////////////////////////////////////////

	double res = fullTable.average_best();
	std::cout << "\n\nThe average of the best scores of all players is: " << res << "\n\n";

	////////////////////////////////////////////////////////////////////////////////////////

	std::string topDog = fullTable.best_overall();
	std::cout << "\n\nCongratulations to " << topDog << " for having the highest average in the group!\n";

	////////////////////////////////////////////////////////////////////////////////////////

	int allNovices = fullTable.novice_count();
	std::cout << "\n\nIn total, there are: " << allNovices << " novices in the group!\n\n";

	system("PAUSE");

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


void inputAutomaticData(std::map<std::string, record>& myMap) {

	std::string line, tempName;
	std::ifstream myfile("assessmentScoreSheet.txt");
	double tempScore;

	if (myfile.is_open()) {

		getline(myfile, line);

		while (line != "0") {

			std::vector<std::string> tempStorage = splitInitialString(line);

			tempName = tempStorage[0];

			record tempRecord;

			int x = static_cast<int>(tempStorage.size());

			for (int i = 1; i < x; i++) {

				tempScore = stod(tempStorage[i]);

				if (tempScore >= 0) {
					tempRecord.add_score(tempScore);
				}
			}

			myMap.insert(std::pair<std::string, record>(tempName, tempRecord));
			getline(myfile, line);
		}
	}
	else {
		std::cout << "\n\nUnable to open file.\n\n";
	}
	return;
}

void inputManualData(std::map<std::string, record>& myMap) {

	std::string startInput;
	std::string tempName;
	double tempScore;

	std::cout << "\n\nEnter player's name and scores \n";
	std::cout << "(in format : name, decimal1, decimal2, decimal3...)\n";
	std::cout << "(enter 0 on new line to terminate)\n\n";

	getline(std::cin, startInput);
	while (startInput != "0") {

		std::vector<std::string> tempStorage = splitInitialString(startInput);

		tempName = tempStorage[0];

		record tempRecord;

		int x = static_cast<int>(tempStorage.size());

		for (int i = 1; i < x; i++) {

			tempScore = stod(tempStorage[i]);

			if (tempScore >= 0) {
				tempRecord.add_score(tempScore);
			}
		}

		myMap.insert(std::pair<std::string, record>(tempName, tempRecord));
		getline(std::cin, startInput);
	}
	return;
}

std::vector<std::string> splitInitialString(const std::string &s) {

	std::vector<std::string> v;

	typedef std::string::const_iterator iter;
	iter comma = find(s.cbegin(), s.cend(), ',');

	v.push_back(std::string(s.cbegin(), comma));

	while (comma != s.cend()) {

		iter start = ++comma;
		comma = find(start, s.cend(), ',');
		v.push_back(std::string(start, comma));
	}
	return v;
}

void enterName(std::string& s) {

	std::cout << "Enter name: ";
	getline(std::cin, s);

	return;
}

void validateEnteredName(std::string& s, const table& myMap) {

	enterName(s);
	bool found = myMap.findNameInList(s);
	while (found == false) {
		std::cout << "\n\nSorry: name entered does not match records.\n\n";
		std::cout << "Enter name of player to see player's best score so far: ";
		enterName(s);
		found = myMap.findNameInList(s);
	}
	return;
}

void enterScore(double& val) {

	std::cout << "\n\nEnter new score: ";
	std::cin >> val;
	getchar();
	while (val < 0) {
		std::cout << "\n\nSorry: negative values are not permitted.\n";
		std::cout << "\n\nEnter new score: ";
		std::cin >> val;
		getchar();
	}
	return;
}

void enterNumPlayers(int& val, const int max) {

	std::cin >> val;
	while (val > max) {
		std::cout << "\n\nSorry: invalid value. Only " << max << " players have scores.\n";
		std::cout << "\nEnter the number of players the names of which have the highest averages: ";
		std::cin >> val;
	}
	return;
}
