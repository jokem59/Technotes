#include <iostream>
#include <string>
#include <vector>

void AddOneToEach(std::vector<int>& vec)
{
    for (auto& e : vec)
    {
        e++;
    }

    return;
}

void PrintVector(const std::vector<int>& vec)
{
    std::cout << "Print vector elements: ";
    for (const auto& e : vec)
    {
        std::cout << e << ",";
    }
    std::cout << '\n';

    return;
}

int main()
{
    auto v { std::vector<int>{1, 2, 3, 4, 5} };

    PrintVector(v);
    AddOneToEach(v);
    PrintVector(v);

    return 0;
}
