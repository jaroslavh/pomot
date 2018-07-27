#include <iostream>
#include <chrono>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include "worklog.h"

using namespace std;

Worklog::Worklog()
{
    using namespace chrono;

    int ret_val;
    //make ./src directory if there is none
    ret_val = mkdir("logs", 0777);
    if ((ret_val != 0) && (ret_val == EEXIST)) {
        cerr << "Failed to create src directory." << endl; //TODO print error message
        exit(2); //TODO exception
    }

    //create log based on current date and time
    system_clock::time_point system_time = system_clock::now();
    time_t current_time = system_clock::to_time_t(system_time);
    char buff[100];
    if (strftime(buff, 100, "%Y-%m-%d", localtime(&current_time)) == 0) {
        cerr << "File name of log too long, exceeded 99 characters." << endl;
        exit(2); // TODO exception
    }

    directory = string("logs/"); //TODO improve working with directory - maybe as a parameter? 
    filename = string(buff) + string("-worklog.txt");

    ofstream logfile;
    if (exists(directory + filename) == true) {
        cout << "File exists, quitting. I would not dare to overwrite your log." << endl; //TODO finish this functionality
        exit(2); // TODO exception
    }
    logfile.open(directory + filename);
    logfile << "Worklog: " << buff << endl;
    logfile.close();
}

int Worklog::worklog_open() //maybe use only as private
{
    file.open(directory + filename, fstream::app);
    if (!file) {
        cerr << "Failed to open: " << directory + filename << endl;
        return 1;
    }
    return 0;
}

int Worklog::worklog_append(const string &line)
{
    if (worklog_open() != 0) {
        cerr << "Could not append :(" << endl;
        return 1;
    }

    file << line << endl;

    file.close();
    return 0;
}

inline bool Worklog::exists(const string &name)
{
    ifstream f(name);
    return f.good();
}
