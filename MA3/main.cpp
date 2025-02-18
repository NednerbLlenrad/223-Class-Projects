#include <map>
#include "TwitterData.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    // Schema: UserName,Last,First,Email,NumTweets,MostViewedCategory
    string raw_data[5][6] = { {"rangerPower", "Smit", "Rick", "smitRick@gmail.com", "1117", "power lifting"},
                             {"kittyKat72", "Smith", "Kathryn", "kat@gmail.com", "56", "health"},
                             {"lexi5", "Anderson", "Alexis", "lexi5@gmail.com", "900", "education"},
                             {"savage1", "Savage", "Ken", "ksavage@gmail.com", "17", "president"},
                             {"smithMan", "Smith", "Rick", "rick@hotmail.com", "77", "olympics"} };
    TwitterData* twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }


    //
    // Your code goes here
    //
    //SearchbyName Map
    std::map<string, TwitterData> twitterMap;
    //Fill Map
    for (int i = 0; i < 5; ++i)
    {
        twitterMap[twitter_data[i].getUserName()] = twitter_data[i];
    }
    //Print through map
    cout << "Print searchByName map:" << endl;
    for (const auto& entry : twitterMap)
    {
        cout << "Key: " << entry.first << " Value: " << entry.second.getActualName() << ", " << entry.second.getEmail() << ", " << entry.second.getNumTweets() << ", " << entry.second.getCategory() << endl;
    }
    //Find User and delete
    string searchUsername = "savage1";
    auto search = twitterMap.find(searchUsername);
    if (search != twitterMap.end())
    {
        TwitterData& user = search->second;
        cout << "Search by key: " << user.getUserName() << " Value: " << user.getActualName() << ", " << user.getEmail() << ", " << user.getNumTweets() << ", " << user.getCategory() << endl;
        twitterMap.erase(search);
        //Code to print map again for debugging
        //for (const auto& entry : twitterMap)
        //{
        //    cout << "Key: " << entry.first << " Value: " << entry.second.getActualName() << ", " << entry.second.getEmail() << ", " << entry.second.getNumTweets() << ", " << entry.second.getCategory() << endl;
        //}
    }
    else
    {
        cout << "User with key: " << searchUsername << " does not exist." << endl;
    }
    //SearchByEmail Map
    std::map<string, TwitterData> twitterMap2;
    //Fill Map
    for (int i = 0; i < 5; ++i)
    {
        twitterMap2[twitter_data[i].getEmail()] = twitter_data[i];
    }
    //Print through map
    cout << "Print searchByEmail map:" << endl;
    for (const auto& entry : twitterMap2)
    {
        cout << "Key: " << entry.first << " Value: " << entry.second.getActualName() << ", " << entry.second.getUserName() << ", " << entry.second.getNumTweets() << ", " << entry.second.getCategory() << endl;
    }
    //Find User and delete
    string searchEmail = "kat@gmail.com";
    auto searchE = twitterMap2.find(searchEmail);
    if (searchE != twitterMap2.end())
    {
        TwitterData& user = searchE->second;
        cout << "Search by key: " << user.getEmail() << " Value: " << user.getActualName() << ", " << user.getUserName() << ", " << user.getNumTweets() << ", " << user.getCategory() << endl;
        twitterMap2.erase(searchE);
        //Code to print map again for debugging
        /*for (const auto& entry : twitterMap2)
        {
            cout << "Key: " << entry.first << " Value: " << entry.second.getActualName() << ", " << entry.second.getUserName() << ", " << entry.second.getNumTweets() << ", " << entry.second.getCategory() << endl;
        }*/
    }
    else
    {
        cout << "User with key: " << searchEmail << " does not exist." << endl;
    }
    return 0;
}
