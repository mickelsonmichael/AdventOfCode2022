#include <vector>
#include <iostream>

#define INITIAL_STRENGTH_SIGNAL 20
#define SIGNAL_STRENGTH_STEP 40

#define CRT_PIXELS 240
#define CRT_PIXELS_PER_ROW 40

class CPU
{
private:
    int _register = 1;
    size_t _cycle_number = 1;
    int _signal_strength = 0;
    std::vector<char> _screen;
    int _crt = 0;

    void next()
    {
        _cycle_number += 1;

        const int sig = _cycle_number - INITIAL_STRENGTH_SIGNAL;
        if (sig == 0 || sig % SIGNAL_STRENGTH_STEP == 0)
        {
            _signal_strength += _cycle_number * _register;
        }
    }
    void paint()
    {
        int effective_crt = _crt % CRT_PIXELS_PER_ROW;
        if (effective_crt >= _register - 1 && effective_crt <= _register + 1)
        {
            _screen[_crt] = '#';
        }

        _crt += 1;
    }

public:
    CPU() : _screen(CRT_PIXELS, '.'){};
    void noop()
    {
        next();

        paint();
    }
    void addx(int x)
    {
        paint();

        next();

        paint();

        _register += x;

        next();
    }
    int signal_strength() const
    {
        return _signal_strength;
    }
    void print() const
    {
        for (size_t i = 0; i <= CRT_PIXELS; ++i)
        {
            if (i % CRT_PIXELS_PER_ROW == 0)
            {
                std::cout << '\n';
            }

            std::cout << _screen[i];
        }

        std::cout << '\n';
    }
};
