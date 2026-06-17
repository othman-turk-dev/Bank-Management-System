#include <iostream>
#include "clsLoginScreen.h"
#include"clsutility.h"

int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }

    return 0;
}