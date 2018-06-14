#include <ctime>
#include <unistd.h>
#include <iostream>
#include "timer.h"

#define POMODORO_DEFAULT 1500000000

using namespace std;



int main(int argc, char * argv[])
{
    /* Check input values */
    if(argc == 1){
        Timer t;
    } else if (argc == 3){
        int m_e = atoi(argv[1]);
        int m_b = atoi(argv[1]);
        if(m_e < 0 || m_b < 0) {
            cerr << "Arguments must be positive, you would not want subtract from your work hours!" << endl;
            return 1;
        }
        Timer t(m_e, m_b);
    } else {
        cerr << "Usage: pomot | pomot <mins for episode> <mins for break>" << endl;
        return 1;
    }

    t.start();
    cout << "Timer started." << endl;
    

}
