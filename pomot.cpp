#include <stdlib.h>
#include <ctime>
#include <iostream>
#include "timer.h"
#include "worklog.h"

#define POMODORO_DEFAULT 1500000000

using namespace std;



int main(int argc, char * argv[])
{
    int min_ep, min_br;

    /* Check input values */
    if (argc == 1) {
        min_ep = 25;
        min_br = 5;
    } else if (argc == 3){
        min_ep = atoi(argv[1]);
        min_br = atoi(argv[1]);
        if(min_ep < 0 || min_br < 0) {
            cerr << "Arguments must be positive, you would not want subtract from your work hours!" << endl;
            return 1;
        }
    } else {
        cerr << "Usage: pomot | pomot <mins for episode> <mins for break>" << endl;
        return 1;
    }

    Timer main_timer(min_ep, min_br);
    Worklog log;
    cout << "Currently saving into " << log.get_filename() << endl;

    main_timer.run();
    cout << "Timer ended." << endl;
    

}
