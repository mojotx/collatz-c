//
// Created by Michael Jarvis on 7/29/22.
//

#include "collatz.h"

unsigned long int
collatz(unsigned long int n) {
    if (n % 2 == 0)
        return n/2;
    else
        return 3 * n + 1;
}
