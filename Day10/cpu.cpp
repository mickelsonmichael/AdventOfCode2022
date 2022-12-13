#include <vector>
#include <iostream>

#define INITIAL_STRENGTH_SIGNAL 20
#define SIGNAL_STRENGTH_STEP 40

class CPU
{
private:
    int _register = 1;
    size_t _cycle_number = 1;
    int _signal_strength = 0;
    void next()
    {
        _cycle_number += 1;

        const int sig = _cycle_number - INITIAL_STRENGTH_SIGNAL;
        if (sig == 0 || sig % SIGNAL_STRENGTH_STEP == 0)
        {
            // std::cout << _cycle_number << " -> Increasing signal strength by "
            //           << _cycle_number << " * "
            //           << _register << " = "
            //           << _cycle_number * _register << '\n';

            _signal_strength += _cycle_number * _register;
        }
    }

public:
    CPU(){};
    void noop()
    {
        next();
    }
    void addx(int x)
    {
        next();

        _register += x;

        next();
    }
    int signal_strength() const
    {
        return _signal_strength;
    }
};
