#include <iostream>
#include <string>
#include <fstream>
using namespace std;

    const int MAX_ENTRY = 999;

struct schedule {
    string courseCode, courseDesc, section, day, time, room;
};

void pressEnter() {
    cout << "\nPress ENTER to return to main menu...\n";
    cin.ignore();
    cin.get();
}

void saveFile (schedule post[], int &total) {
    
    ofstream outFile("CTracker.txt", ios::app);

    if(!outFile) {
        cout << "Error opening file for saving!" << endl;
        return;
    }

    for (int i = 0; i < total; i++) {
        outFile << post[i].courseCode << endl;
        outFile << post[i].courseDesc << endl;
        outFile << post[i].section << endl;
        outFile << post[i].day << endl;
        outFile << post[i].time << endl;
        outFile << post[i].room << endl;
        outFile << "------------------------------" << endl;
    }

    outFile.close();
    cout << "All schedules saved successfully!" << endl;

    pressEnter();
}

void loadFile (schedule post[], int &total) {
    
    ifstream inFile("CTracker.txt");

    if(!inFile) {
        cout << "No saved data found. Please post a schedule." << endl;
        return;
    }

    total = 0;
    string line;

    while (getline(inFile, post[total].courseCode)) {
        getline(inFile, post[total].courseDesc);
        getline(inFile, post[total].section);
        getline(inFile, post[total].day);
        getline(inFile, post[total].time);
        getline(inFile, post[total].room);
        getline(inFile, line);
        total++;
    }

    inFile.close();
    cout << "Schedule loaded successfully! (" << total << " entries)" << endl;
}

void Post (schedule post[], int &total) {

    cout << "\n--- Post a Schedule ---\n";

    if (total >= MAX_ENTRY) {
        cout << "Maximum entry reached. You're no longer able to post.\n";
        pressEnter();
        return;
    }

    cout << "\nEnter Course Code: ";
    cin >> ws;
    getline(cin, post[total].courseCode);

    cout << "Enter Course Description: ";
    cin >> ws;
    getline(cin, post[total].courseDesc);

    cout << "Enter Section name: ";
    cin >> ws;
    getline(cin, post[total].section);

    cout << "Enter your desired day to teach: ";
    cin >> ws;
    getline(cin, post[total].day);

    cout << "Enter your desired time and duration to teach. (ex. 07:00AM - 10:00AM): ";
    cin >> ws;
    getline(cin, post[total].time);

    cout << "Enter which room you'd like to occupy: ";
    cin >> ws;
    getline(cin, post[total].room);

    cout << "\nSchedule successfully posted!" << endl;
    cout << "Course Code:" << post[total].courseCode << endl;
    cout << "Course Description: " << post[total].courseDesc << endl;
    cout << "Section: " << post[total].section << endl;
    cout << "Day: " << post[total].day << endl;
    cout << "Time: " << post[total].time << endl;
    cout << "Room: " << post[total].room << endl;
    total++;

    pressEnter();
}

void search (schedule post[], int &total) {
    bool found = false;
    string search;

    cout << "\nEnter Course Code: ";
    cin >> search;

    if (search.empty()) {
        cout << "Course Code cannot be EMPTY." << endl;
        return;
    }

    for (int i = 0; i < total; i++) {
        if (search == post[i].courseCode) {
            cout << "\nCourse Code: " << post[i].courseCode << endl;
            cout << "Course Description: " << post[i].courseDesc << endl;
            cout << "Section: " << post[i].section << endl;
            cout << "Day: " << post[i].day << endl;
            cout << "Time: " << post[i].time << endl;
            cout << "Room: " << post[i].room << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No Course Code " << search << " found posted. Please try again." << endl;
    }

    pressEnter();

}

int main () {

    int choice, total = 0;
    schedule post[MAX_ENTRY];

        loadFile(post, total);
    do {
      
        cout << "--- Welcome to C-Tracker! Please Select your desired choice. ---\n";
        cout << "1. Post a schedule" << endl;
        cout << "2. Search a schedule. (Using Course Code)" << endl;
        cout << "3. Save your schedule." << endl;
        cout << "4. Exit C-Tracker." << endl;
        cout << "Please choose the desired choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            Post(post, total);
            break;
        
        case 2:
            search(post, total);
            break;

        case 3:
            saveFile(post, total);
            break;

        case 4:
            cout << "Thank you for using C-Tracker. Have a good day!" << endl;
            break;

        default:
            break;
        }
    } while (choice != 4);

    return 0;
}