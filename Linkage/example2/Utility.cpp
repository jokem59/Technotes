#include <string>
#include "Utility.h"

// non-const global variable; external linkage; declared and defined
double GRAVITY = 9.8;

std::string GetGravityAsString()
{
    return std::to_string(GRAVITY);
}
