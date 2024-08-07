#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include "enum.hpp"

namespace protocol
{

    class ABNTProtocol
    {
    private:
        static constexpr uint16_t POLY = 0x8005; // Polinômio CRC16 (X16 + X15 + X2 + 1)
        static constexpr uint16_t init_CRC = 0xFFFF;

    public:
        auto calculateCRC16(const std::vector<uint8_t> &frame, CRCType type) -> uint16_t;
        auto addCRCToFrame(const std::vector<uint8_t> &frame, CRCType type) -> std::vector<uint8_t>;
        void printFrame(const std::vector<uint8_t> &frame);
        auto isABNTFrame(const std::vector<uint8_t> &frame) -> bool;
    };
}