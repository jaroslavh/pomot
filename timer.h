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

void Timer::start()
{
    time_t result = time(nullptr);
    usleep(3000000);
    time_t result2 = time(nullptr);
    cout << result2 - result << " seconds since the Epoch\n";
}
