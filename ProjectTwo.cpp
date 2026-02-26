#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Structure to hold course information
struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

// Global data structure to store courses
map<string, Course> courseMap;

// Load courses from file
void loadDataStructure(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        Course course;

        getline(ss, course.courseId, '\t');
        getline(ss, course.title, '\t');

        while (getline(ss, item, '\t')) {
            course.prerequisites.push_back(item);
        }

        courseMap[course.courseId] = course;
    }

    cout << "Data loaded successfully." << endl;
    file.close();
}

// Print sorted course list
void printCourseList() {
    cout << "Here is a sample schedule:" << endl;

    for (auto const& pair : courseMap) {
        cout << pair.second.courseId << ", " << pair.second.title << endl;
    }
}

// Print individual course info
void printCourse(string courseId) {
    transform(courseId.begin(), courseId.end(), courseId.begin(), ::toupper);

    if (courseMap.find(courseId) != courseMap.end()) {
        Course course = courseMap[courseId];
        cout << course.courseId << ", " << course.title << endl;

        if (course.prerequisites.size() > 0) {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); i++) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        else {
            cout << "Prerequisites: None" << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}

// Display menu
void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

// Main function
int main() {
    string fileName;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the file name: ";
            cin >> fileName;
            loadDataStructure(fileName);
        }
        else if (choice == 2) {
            if (courseMap.empty()) {
                cout << "Please load data first." << endl;
            }
            else {
                printCourseList();
            }
        }
        else if (choice == 3) {
            if (courseMap.empty()) {
                cout << "Please load data first." << endl;
            }
            else {
                string courseId;
                cout << "What course do you want to know about? ";
                cin >> courseId;
                printCourse(courseId);
            }
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}