#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <sstream>

using namespace std;
int main() {
    vector<bool> finish(10, false);
    vector<vector<int>> allocation;
    vector<vector<int>> request;
    vector<int> available;
    vector <string> processes;
    set <int> set; // this set for process that have requested resources more than the available resources
    bool deadlocked = false;

    ifstream allocationFile,requestFile,availableFile; // indata is like cin
    allocationFile.open("/Users/shahdyahya/Desktop/untitled3/Allocation");
    requestFile.open("/Users/shahdyahya/Desktop/untitled3/Request");
    availableFile.open("/Users/shahdyahya/Desktop/untitled3/Available");

    if (!allocationFile.is_open()) {
        cerr << "Error: Unable to open file "  << endl;
        return 1;
    }
    if (!requestFile.is_open()) {
        cerr << "Error: Unable to open file "  << endl;
        return 1;
    }
    if (!availableFile.is_open()) {
        cerr << "Error: Unable to open file "  << endl;
        return 1;
    }
    string availableFileInput;
    getline(availableFile, availableFileInput); // read the first line and do nothing

    // extract the data between commas
    while (getline(availableFile, availableFileInput, ',')) {
        // Convert the data into an integer
        int num = stoi(availableFileInput);
        // add it to an available vector
        available.push_back(num);
    }


    string allocationFileInput,requestFileInput;

    getline(allocationFile, allocationFileInput); // skip the first line of allocationFile (read it and do nothing)
    string s;
    // read from allocationFile
    while (getline(allocationFile, s)) {
        stringstream ss(s);
        vector<int> row;
        string token;
        // Skip the process name
        getline(ss, token, ',');

        // Read the resource allocation values
        while (getline(ss, token, ',')) {
            int num = stoi(token);
            row.push_back(num);
        }

        allocation.push_back(row);
    }


    getline(requestFile, requestFileInput);// skip the first line of requestFile (read it and do nothing)

    // Read the process data
    while (getline(requestFile, s)) {
        stringstream ss(s);
        vector<int> row;
        string token;

        // Skip the process name
        getline(ss, token, ',');

        // Read the resource allocation values
        while (getline(ss, token, ',')) {
            int num = stoi(token);
            row.push_back(num);
        }

        request.push_back(row);
    }
    bool consistent = true;
    if(request.size() != allocation.size()){
        cout<< "the data is not consistent";
        consistent = false;
    }
    for(int i = 0; i < request.size(); i++){
        if(request[i].size() != available.size() || allocation[i].size() != available.size()){
            cout<< "the data is not consistent";
            consistent = false;
            break;
        }
    }


    // Check if the data is consistent
    if (consistent) {
        int k = 0, temp;

        // Iterate over each process
        for (int i = 0; i < allocation.size(); i++) {
            // Check if the process is not finished
            if (!finish[i]) {
                int flag = true; // Flag to check all the resources

                // Check if there are enough resources for the process
                for (int j = 0; j < allocation[i].size(); j++) {
                    if (available[j] < request[i][j]) {
                        flag = false;
                    }
                }

                // If there are enough resources, add the allocation to available
                if (flag) {
                    for (int j = 0; j < allocation[i].size(); j++) {
                        available[j] += allocation[i][j];
                    }
                    finish[i] = true;

                    // Remove the process from the set if it was in a deadlock
                    if (set.count(i)) {
                        set.erase(i);
                    }
                    // if the process is finished add it to the processes vector
                    string process = "p" + to_string(i + 1);
                    processes.push_back(process);
                }

                // If there are not enough resources, add the process to the set
                if (!flag) {
                    set.insert(i);
                }
            }

            // If there are processes in the set and reached the end, check for deadlock
            if (!set.empty() && i == allocation.size() - 1) {
                if (k && temp == set.size()) {
                    cout << "There is a deadlock" << endl;
                    deadlocked = true;
                    break;
                }

                k++;
                temp = set.size();

                // Reset the iteration to the process in the set
                i = *set.begin() - 1;
                set.erase(set.begin());
            }
        }
    }

// Print the result based on deadlock status
    if (deadlocked) {
        cout << "The processes that are deadlocked:" << endl;
        for (auto it = set.begin(); it != set.end(); ++it) {
            cout << "p" << *it + 1 << " ";
        }
    }

    else {
        cout << "There is no deadlock" << endl;
        for (auto i : processes) {
            cout << i << " ";
        }
    }
    return 0;
}


