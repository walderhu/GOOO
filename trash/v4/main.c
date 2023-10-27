#include "tic_tac_toe.h"
int main()
{
    switch (lobby())
    {
    case 1:
        start_pwp();
        break;
    case 2:
        start_pwe();
        break;
    case -1:
        break;
    }

    return 0;
}
