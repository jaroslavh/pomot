#include <stdint.h>
#include <string>

using namespace std;

class Timer
{
    public:
        Timer();
        Timer(uint16_t mins_ep, uint16_t mins_br);
        void set_mins_episode(uint16_t m);
        void set_mins_break(uint16_t m);
        void run();
        string to_time(uint16_t seconds);
        void play_sound(string path);

    private:
        uint16_t mins_episode;
        uint16_t mins_break;
        
};
