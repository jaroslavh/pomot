#include <time.h>
#include <unistd.h>
#include <iostream>
#include "timer.h"

using namespace std;

Timer::Timer() : mins_episode(25), mins_break(5)
{}

Timer::Timer(uint16_t mins_ep, uint16_t mins_br) : mins_episode(mins_ep), mins_break(mins_br)
{}

void Timer::set_mins_episode(uint16_t m)
{
    mins_episode = m;
}

void Timer::set_mins_break(uint16_t m)
{
    mins_break = m;
}

void Timer::run()
{
    cout << "GO!";
    for (uint16_t i = mins_episode * 60; i > 0; i--) {
        cout  << '\r' << flush << to_time(i);
        sleep(1);
    }
    cout << '\r' << flush << "00:00" << endl;
}

string Timer::to_time(uint16_t seconds)
{
    int secs, mins;
    string ret;

    mins = seconds / 60;
    if (mins < 10) {
        ret = "0" + to_string(mins);
    } else {
        ret = to_string(mins);
    }
    ret += ":";
    secs = seconds % 60;
    if (secs < 10) {
        ret += "0" + to_string(secs);
    } else {
        ret += to_string(secs);
    }
    
    return ret;
}
