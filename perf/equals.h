#include <cpu/word.h>
#include <cpu/cpu.h>

static inline const int stripe_count = 4;

class EqualsTest {
public:
    EqualsTest ();

    void test(int iterations);

private:
    Cpu cpu;

    Word stripes[stripe_count] = {
        {0,1,2,3,4},
        {4,3,2,1,0},
        {3,2,1,4,0},
        {0,4,2,3,1}
    };
};
