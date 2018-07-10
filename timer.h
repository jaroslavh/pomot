#include <stdint.h>

class Timer
{
    public:
        Timer();
        Timer(uint16_t mins_ep, uint16_t mins_br);
        void set_mins_episode(uint16_t m);
        void set_mins_break(uint16_t m);
        void start();

    private:
        uint16_t mins_episode;
        uint16_t mins_break;
        
};
