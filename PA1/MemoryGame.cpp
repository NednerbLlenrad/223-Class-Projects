

#include "MemoryGame.h"

bool MemoryGame::loadCmdList()
{
	//Opens and writes both CSVs to their respective linked list and array
	ifstream commands("commands.csv");//Opens the file
	if (!commands)
	{
		cout << "Error Commands.csv is unable to be opened.";
		system("pause");
		return 0;
	}
	cmdList.setHead(nullptr);
	string line;
	getline(commands, line);

	////Debugging Line
	//cout << "Entering while loop" << endl;

	while (getline(commands, line))
	{
		stringstream str(line);
		string token;

		getline(str, token, ',');
		string cmd = token;

		getline(str, token, ',');
		string desc = token.substr(2, token.length() - 3);

		//// Debugging output
		//cout << "Command: " << cmd << ", Description: " << desc << endl;

		cmdList.add(cmd, desc);
	}
	if (cmdList.isEmpty())
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

bool MemoryGame::loadProfiles()
{
	//Opens and writes both CSVs to their respective linked list and array
	ifstream commands("profiles.csv");//Opens the file
	if (!commands)
	{
		cout << "Error profiles.csv is unable to be opened.";
		system("pause");
		return 0;
	}
	string line;
	getline(commands, line);

	////Debugging Line
	//cout << "Entering while loop" << endl;
	while (getline(commands, line))
	{
		stringstream str(line);
		string token;

		getline(str, token, ',');
		string name = token;

		getline(str, token, ',');
		int points = stoi(token);

		//// Debugging output
		//cout << "Name: " << name << ", Points: " << points << endl;

		Profile profileT;//Temporary profile
		profileT.name = name;//Loads name
		profileT.score = points;//Loads points
		profileList[profileNum] = profileT;//Saves it to the front of the array
		profileNum++;//Moves to next profile
	}
	if (profileList[0].score == NULL)//Checks if the first profile was loaded. if it is then it can be assumed the rest were loaded
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void MemoryGame::loadFiles()
{
	//loads teh cmd and profiles
	bool check = loadCmdList();
	check = loadProfiles();
	if (check == false)
	{
		cout << "Error Loading Files to lists.";
		system("pause");
	}
}

void MemoryGame::runApp()
{
	//Runs the application and handles main functions
	loadFiles();
	int choice = 0;
	string name;
	while (choice != 6)
	{
		choice = 0;
		choice = menu(choice);
		switch (choice)
		{
		case 1:
			gameRules();
			break;
		case 2:
			cout << "Please enter a name:" << endl;
			cin >> name;
			playGame(name, 0);
			break;
		case 3:
			loadProfile();
			break;
		case 4:
			addCommand();
			break;
		case 5:
			removeCommand();
			break;
		case 6:
			cout << "Thanks for Playing!" << endl;
			exitWork();
			break;
		}
	}
	return;
}

int MemoryGame::menu(int choice)
{
	//Prints the menu and returns the selection
	while (choice <= 0 || choice >= 7)
	{
		system("cls");
		cout << "Welcome to the Linux Memory Game!" << endl;
		cout << "Please select an option below:" << endl;
		cout << "1. Game Rules" << endl;
		cout << "2. Play Game" << endl;
		cout << "3. Load Previous Game" << endl;
		cout << "4. Add Command" << endl;
		cout << "5.Remove Command" << endl;
		cout << "6. Exit" << endl;
		cin >> choice;
	}
	return choice;
}

void MemoryGame::gameRules()
{
	//Prints game rules
	system("cls");
	cout << "1.Choose how many rounds to play." << endl;
	cout << "2. Each round one command will be given with three random descriptions." << endl;
	cout << "3. One description matches the command." << endl;
	cout << "4. Write the number of the description into the prompt." << endl;
	cout << "4a. If you are correct you gain a point." << endl;
	cout << "4b. If you are incorrect you lose a point." << endl;
	cout << "5. Your score is saved at the end of the game." << endl;
	system("pause");
	system("cls");
	return;
}

void MemoryGame::playGame(string name, int score) {
	int rounds = 0, correct = 0, guess = 0;
	LinkedList<string, string> options;

	while (rounds < 5 || rounds > 30) {
		system("cls");
		cout << "How many rounds would you like to play? (Minimum 5 and Maximum 30)" << endl;
		cin >> rounds;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
	}

	int size = cmdList.size(); 

	for (int i = 0; i < rounds; i++) { 
		// Check if the cmdList has enough items
		if (size < 3) {
			cout << "Error: Not enough items in cmdList for the game." << endl;
			return;
		}

		int i1, i2, i3;
		i1 = rand() % size;
		do {
			i2 = rand() % size;
		} while (i1 == i2);
		do {
			i3 = rand() % size;
		} while (i3 == i2 || i3 == i1);

		Node<string, string>* curr = cmdList.getHead();
		for (int i = 0; i < size; i++) {
			if (i == i1 || i == i2 || i == i3) {
				options.add(curr->getCmd(), curr->getDesc());
			}
			curr = curr->getNext();
		}

		correct = rand() % 3;
		Node<string, string>* answerNode = options.getHead();

		for (int j = 0; j < 3; j++) {
			if (j == correct) {
				cout << answerNode->getCmd() << endl;
			}
			answerNode = answerNode->getNext();
		}

		Node<string, string>* optionNode = options.getHead();
		for (int j = 0; j < 3; j++) {
			cout << j + 1 << ". " << optionNode->getDesc() << endl;
			optionNode = optionNode->getNext();
		}

		//Gets the guess from the player
		cout << "Guess: ";
		while (guess < 1 || guess > 3) {
			cin >> guess;
		}

		if (guess == correct + 1) { 
			score++;
			cout << "Correct! +1" << endl;
			cout << "Score: " << score << endl;
		}
		else {
			score--;
			cout << "Incorrect! -1" << endl;
			cout << "Score: " << score << endl;
		}
		system("pause");
		system("cls");
		guess = 0;
		// Clear the options for the next round
		options.clearList();
	}

	saveGame(name, score);
	return;
}


void MemoryGame::loadProfile()
{
	//List array names and scores
	//User enters name to load
	//Check if name is in array
	//If not, reprompt until valid response
	//Play game like normal
	string name;
	int score;
	cout << "Save Games" << endl;
	cout << "Name, Points" << endl;
	for (int j = 0; j < profileNum; j++)
	{
		cout << j + 1 << ". " << profileList[j].name << ", " << profileList[j].score << endl;
	}
	int choice = 0;
	while (choice < 1 || choice > profileNum)
	{
		cout << "Please enter the number of the profile to load: ";
		cin >> choice;
	}
	name = profileList[choice - 1].name;
	score = profileList[choice - 1].score;
	playGame(name, score);
	return;
}

void MemoryGame::addCommand()
{
	//Prompts the user for a name of a command
	//Saves it to the linked list
	//Prompts user for description of command
	//Saves it to the same node of linked list
	//Adds the node to the end of the list.
	string command, description;
	cout << "Please enter the name of the command you would like to add:" << endl;
	cin >> command;
	//Clears input buffer
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Please enter the description of the command you would like to add:" << endl;
	getline(cin, description);
	cmdList.add(command, description);
	return;
}

void MemoryGame::removeCommand()
{
	//Search through linked list by command name
	//Removes it from the linkes list
	string cmdName;
	cout << "Please enter the name of the command you would like to remove:" << endl;
	//Clears input buffer
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin >> cmdName;
	bool deleteCheck = cmdList.remove(cmdName);
	if (deleteCheck == 1)
	{
		cout << "Successfully deleted command." << endl;
		system("pause");
	}
	else
	{
		cout << "Sorry that command is not present in the list." << endl;
		system("pause");
	}
	return;
}

void MemoryGame::exitWork()
{
	//Saves the linked list to the commands.csv
	//Saves the array to profiles.csv
	bool check = storeCmdList();
	check = storeProfiles();
	if (check == 1)
	{
		cout << "Game Saved!" << endl;
		system("pause");
	}
	return;
}

bool MemoryGame::storeCmdList()
{
	//Writes the linked list of commands to the csv file in the same format as it is read in
	//Then closes the file and returns true if successful
	ofstream outfile("commands.csv");
	if (!outfile)
	{
		cout << "Unable to open commands.csv" << endl;
		return false;
	}
	Node<string, string>* curr = cmdList.getHead();
	outfile << "commands, \"descriptions\"," << endl;
	while (curr != nullptr)
	{
		outfile << curr->getCmd() << ", \"" << curr->getDesc() << "\"," << endl;
		curr = curr->getNext();
	}
	outfile.close();
	return true;
}

bool MemoryGame::storeProfiles()
{
	//Saves the profiles to the csv file in proper formatting
	ofstream outfile("profiles.csv");
	if (!outfile)
	{
		cout << "Unable to open profiles.csv" << endl;
		return false;
	}
	
	outfile << "name, points," << endl;
	for (int i = 0; i < profileNum; i++)
	{
		outfile << profileList[i].name << ", " << profileList[i].score << "," << endl;
	}
	outfile.close();
	return true;
}

void MemoryGame::saveGame(string name, int score)
{
	//Saves the current game to the profile array.
	//If the name is currently in the list, it updates the score
	//If the name is new, then it is placed at the end
	//If the maximum saves are reached it prompts with the list of saves to overwrite and overwrites it
	int i = 0;
	for (; i < profileNum; i++)
	{
		if (profileList[i].name == name)
		{
			profileList[i].score = score;
			return;
		}
		if (profileList[i].name == "")
		{
			profileList[i].name = name;
			profileList[i].score = score;
			return;
		}
	}
	if (i < 100)
	{
		profileList[i + 1].name = name;
		profileList[i + 1].score = score;
	}
	else
	{
		cout << "Save Games full! Choose one to overwrite:" << endl;
		cout << "Name, Points" << endl;
		for (int j = 0; j < 100; j++)
		{
			cout << j + 1 << ". " << profileList[j].name << ", " << profileList[j].score << endl;
		}
		int choice = 0;
		while (choice < 1 || choice > 100)
		{
			cout << "Please enter the number of the profile to overwrite: ";
			cin >> choice;
		}
		profileList[choice - 1].name = name;
		profileList[choice - 1].score = score;
	}

}
