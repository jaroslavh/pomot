#include <time.h>
#include <unistd.h>
#include <iostream>
#include <ao/ao.h>
#include <mpg123.h>
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
    play_sound("end_sound.mp3");
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

void Timer::play_sound(string path)
{
    mpg123_handle *mh;
    char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;

    /* init */
    ao_initialize();
    driver = ao_default_driver_id();
    if (mpg123_init() != MPG123_OK) {
        cerr << "Error: Failed to initialize mpg123 library." << endl;
        exit(2); //TODO throw exception
    }
    mh = mpg123_new(NULL, &err);
    if (mh == NULL) {
        cerr << "Error: Failed to allocate mpg123_handle memory." << endl;
        exit(2); //TODO throw exception
    }
    buffer_size = mpg123_outblock(mh);
    buffer = (char*) malloc(buffer_size * sizeof(char)); //TODO new + probably not needed
    if(buffer == NULL) {
        cerr << "Error: not enough memory for sound buffer." << endl;
    }

    /* open the file and get the decoding format */
    if (mpg123_open(mh, path.c_str()) != MPG123_OK) {
        cerr << "Error: could not open " << path << endl;
        exit(2); //TODO throw exception
    }

    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * 8;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    /* decode and play */
    while (mpg123_read(mh, (unsigned char *)buffer, buffer_size, &done) == MPG123_OK)
        ao_play(dev, buffer, done);

    /* clean up */
    free(buffer);
    ao_close(dev);
    if (mpg123_close(mh) != MPG123_OK) {
        cerr << "Error: Failed to close audio device." << endl;
    }
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
}
