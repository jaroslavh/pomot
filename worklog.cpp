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
    logfile.open(directory + filename);
    logfile << "Worklog: " << buff << endl;
    logfile.close();

}
