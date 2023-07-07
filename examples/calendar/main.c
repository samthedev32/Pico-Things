#include "calendar.h"

int main()
{
    date d;
    d.year = 2022;
    d.month = 02;
    d.day = 26;
    if (d.day == 0)
        return 1;
    return 0;
}