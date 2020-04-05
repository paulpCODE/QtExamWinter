#ifndef RANDOM_H
#define RANDOM_H
#include <random>


struct Random
{
private:
    Random();
    Random operator = ( Random& ) = delete;
    Random(const Random& ) = delete;
public:
    static int RandInt(const int &RAND_min, const int &RAND_max) {
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

        return static_cast<int>(rand() * fraction * (RAND_max - RAND_min + 1) + RAND_min);
    }
};
#endif // RANDOM_H
