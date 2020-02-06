#include <iostream>
#include <string>
#include "Utility.h"
#include "Math.h"

// forward declaration of variable - if this is commented out, this DLL won't compile
extern double GRAVITY;

// internally linked variable
static int SECRETS = 42;

// also internally linked variable
constexpr int MOARSECRETS = 43;

DLLEXPORT
void CheckGravity(std::string User)
{
    std::cout << "Calling GetGravityAsString()\n";

    std::string result = GetGravityAsString();

    std::cout << User << " Call.  Gravity is fixed at: " << result << '\n';
    return;
}

DLLEXPORT
void AddToGravity(double NewGrav)
{
    std::cout << "Adding " << NewGrav << " to GRAVITY\n";
    GRAVITY += NewGrav;
    return;
}

DLLEXPORT
void CheckSecrets()
{
    std::cout << "SECRETS value: " << SECRETS << '\n';
    return;
}

DLLEXPORT
void CheckMoarSecrets()
{
    std::cout << "MOARSECRETS value: " << MOARSECRETS << '\n';
    return;
}
