#include <locale.h>
#include <vector>
#include <iostream>
#include "ABNT.hpp"
#include "enum.hpp"

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    protocol::ABNTProtocol ABNT;

    std::vector<uint8_t> data = { 0x30, 0x12, 0x34, 0x56, 0x13};

    data.insert(data.end(), 59, 0x00);

    std::vector<uint8_t> frameWithCRC = ABNT.addCRCToFrame(data, CRCType::ARC);

    ABNT.printFrame(frameWithCRC);

    if(ABNT.isABNTFrame(frameWithCRC))
    {
        std::cout << "O frame é um ABNT válido\n"; 
    }
    else
    {
        std::cout << "O frame NÃO é um ABNT válido\n";
    }

    return 0;
}
