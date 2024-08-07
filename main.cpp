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

    std::cout << "Frame com CRC: ";
    for (uint8_t byte : frameWithCRC) {
        std::cout << std::hex << std::uppercase << "0x" << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

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
