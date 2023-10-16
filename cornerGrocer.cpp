/*
Jaiden Blanchard
10/13/23
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
using namespace std;


class cornerGrocerClass {
public:
    /*Menu option 1
    Prompt a user to input the item, or word, they wish to look for.
    Return a numeric value for the frequency of the specific word.*/

    void getMenuOne() {
        string itemSearch;
        cout << "Please input item name: " << endl;
        cin >> itemSearch;
        cout << "The amount of " << itemSearch << " in the list is: " << groceryMap[toLowerString(itemSearch)] << endl;
        cout << endl;
    }

    /* Menu option 2
    Print the list with numbers that represent the frequency of all items purchased.
    The screen output should include every item(represented by a word) paired with
    the number of times that item appears in the input file,
    CS210_Project_Three_Input_File.txt.For example, the file might read as follows : */

    void getMenuTwo() {
        for (const auto& kv : groceryMap) {
            cout << "There are " << kv.second << " " << kv.first << " in the Grocery List." << endl;
        }
        cout << endl;
    }

    /*Menu option 3
    Print the same frequency information for all the items in the form of a histogram.
    Then print the name, followed by asterisks or another special character to represent the numeric amount.
    The number of asterisks should equal the frequency read from the CS210_Project_Three_Input_File.txt file.
    For example, if the file includes 4 potatoes, 5 pumpkins, and 3 onions, then your text-based histogram
    may appear as represented below. However, you can alter the appearance or color of the histogram in any way you choose*/

    void getMenuThree() {
      for (const auto& kv : groceryMap) {
          cout << kv.first << " ";
          for(int i = 0; i < kv.second; i++)
              cout << "*";
          cout << endl;}
          cout << endl;}

    // write to our backup data file and then exit.
    void getMenuFour() {
        cout << "All done!" << endl;
        backupData.open("G:\\My Drive\\College\\Programming Languages\\Corner Grocer\\frequency.dat"); // change path to your needs.
        for (const auto& kv : groceryMap) {
            backupData << kv.first << ", " << kv.second << endl;
        }
        backupData.close();
        exit(0);
    }

    // open and access the grocery list, then close it when we're done with it.
    void setGroceryList()
    {
        groceryList.open("G:\\My Drive\\College\\Programming Languages\\Corner Grocer\\CS210_Project_Three_Input_File.txt"); // open the file // change path to your needs.
        fillGroceryMap();
        groceryList.close();
    }

private:

    string itemName;
    ifstream groceryList;
    ofstream backupData;
    map<string, int> groceryMap;

    // fill the grocery map
    void fillGroceryMap()
    {
        string line;
        while(getline(groceryList, line))
        {
            line = toLowerString(line);
            if(groceryMap.find(line) == groceryMap.end())
            {
                groceryMap.emplace(line, 1);
            }
            else{
                groceryMap[line]++;
            }
        }
    }

    // exception handling incase words are written in varying ways, ex: yams == Yams == yAMs and so on.
    string toLowerString (string word)
    {
        for (int i = 0; i < word.length(); i++)
            word[i] = tolower(word[i]);

        return word;
    }
};

int main() {
    cornerGrocerClass cornerGrocer;
    int menuInput;

    // menu display options 

    cout << "Please select a menu option." << endl;
    cout << "[1] Search Grocery List" << endl;
    cout << "[2] Produce Grocery List Totals" << endl;
    cout << "[3] Produce Grocery List Histogram" << endl;
    cout << "[4] Exit." << endl;

    cin >> menuInput;
    
    //while there is input, print one of these menus according to the input.
    while (true) {
        if (menuInput == 1) {
            cornerGrocer.setGroceryList();
            cout << "Menu option 1: " << endl;
            cornerGrocer.getMenuOne();
            cin >> menuInput;
        }
        else if (menuInput == 2) {
            cornerGrocer.setGroceryList();
            cout << "Menu option 2: " << endl;
            cornerGrocer.getMenuTwo();
            cin >> menuInput;
        }

        else if (menuInput == 3) {
            cornerGrocer.setGroceryList();
            cout << "Menu option 3: " << endl;
            cornerGrocer.getMenuThree();
            cin >> menuInput;
        }

        else { // technically anything other than 1 2 or 3 will prompt this option
            (menuInput == 4);
            cout << "Menu option 4: " << endl;
            cornerGrocer.getMenuFour();
        }
    }
}
