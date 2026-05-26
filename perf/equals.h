#include <cpu/word.h>
#include <cpu/cpu.h>

class EqualsTest {
public:
    EqualsTest ();

private:
    Cpu equals_cpu();

    Word equals_stripes[4] = {
        {0,1,2,3,4},
        {4,3,2,1,0},
        {3,2,1,4,0},
        {0,4,2,3,1}
    };
};
