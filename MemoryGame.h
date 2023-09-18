// Memory Game.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "LinkedList.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;
using std::stoi;

//Struct for the user profiles
struct Profile {
	string name;
	int score;
};

//Class for the game itself
class MemoryGame
{
public:
	//Load CMD
	bool loadCmdList();
	//Load Profiles
	bool loadProfiles();
	//Load Files
	void loadFiles();
	//Runs the program
	void runApp();
	//Menu
	int menu(int choice);
	//Prints Rules
	void gameRules();
	//Play Game
	void playGame(string name, int score);
	//Load Profile
	void loadProfile();
	//Add Command
	void addCommand();
	//Remove Command
	void removeCommand();
	//Exit
	void exitWork();
	//Store Command List
	bool storeCmdList();
	//Store Profile List
	bool storeProfiles();
	//Saves the name and score
	void saveGame(string name, int score);
	//Generates the three nodes
	LinkedList<string, string> getRandomPair();
private:
	LinkedList<string, string> cmdList;
	Profile profileList[100];
	int profileNum = 0;
};

