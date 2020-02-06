#include <iostream>
#include <string>
#include "Utility.h"
#include "Math.h"

void FunctionDecl(int); // a function with no declaration, has no memory address

void CheckGravity(std::string); // forward declaration of function
void CheckGravity(std::string); // forward declaration of function
void CheckGravity(std::string); // forward declaration of function
extern double GRAVITY; // forward declaration of variable

//double GRAVITY = 100.5; // BAD - Because we're linking, we hit multiple definition error

extern int SECRETS; // results in unresolve external symbol due to SECRETS having internal linkage in Math.dll

int main()
{
    // Mainpulate global variable GRAVITY within Math.dll address space
    std::cout << "Manipulating global variable GRAVITY within Math.dll address space\n";
    CheckGravity("Math.dll");
    AddToGravity(25.0);
    CheckGravity("Math.dll");
    std::cout << "\n\n";

    // Manipulating the global variable GRAVITY within main.exe address space
    std::cout << "Manipulating global variable GRAVITY within main.exe address space\n";
    std::cout << "Main.exe global variable GRAVITY: " << GRAVITY << '\n';
    GRAVITY += 1.2;
    std::cout << "Main.exe global variable GRAVITY: " << GRAVITY << '\n';
    std::cout << "Global for main.exe: " << GetGravityAsString() << '\n';

    // Set internally linked Math.h variable - if commented out, main.exe doesn't get copy of this symbol
    // Also shows that independent copies tracked for main.exe and Math.dll
    std::cout << "Calling Math.dll's CheckSecrets()\n";
    CheckSecrets();

    // CAN'T DO THIS due to internal linkage
    //std::cout << "SECRETS value: " << SECRETS << '\n';

    return 0;
}
