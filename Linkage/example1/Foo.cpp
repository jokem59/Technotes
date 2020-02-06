#include <iostream>
#include "Foo.h"

// function factory
#define FUNCFACTORY(name, X)                                                                  \
    void Function##name()                                                                     \
    {                                                                                         \
        std::cout << "Running Function" << #name << " with macro arg: " << X << "\n"; \
    }                                                                                         \

FUNCFACTORY(Mog, 5)
FUNCFACTORY(Kupo, 6)
FUNCFACTORY(Tibbers, 7);

int main()
{
    FunctionMog();
    FunctionKupo();
    FunctionTibbers();
    return 0;
}
