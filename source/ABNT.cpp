#include "ABNT.hpp"
#include <bitset>
#include <stdexcept>

namespace protocol
{
    auto ABNTProtocol::calculateCRC16(const std::vector<uint8_t> &frame, CRCType type) -> uint16_t
    {
        // 1° Parametro -> Recebe um vetor de 8 bits;
        // 2° Parametro -> Define qual será o tipo do CRC. OBS: Limitado a os CRC de 16 bits.

        // Verificar se o Frame esta vazio.
        if (frame.empty())
        {
            // Se o Frame/Vetor estiver vazio será retornado 0.
            return 0;
        }

        uint16_t polynomial = 0xA001;
        uint16_t crc;

        // Escolher um tipo de CRC-16.
        switch (type)
        {
        case CRCType::ARC:
            crc = 0;
            break;

        default:
            crc = 0xFFFF;
            break;
        }

        for (uint8_t byte : frame)
        {
            // Converte o byte de 8 Bits para 16 Bits e armazena em uma variavel tempByte.
            uint16_t tempByte = static_cast<uint16_t>(byte);

            // Um loop para percorrer 8 bits.
            for (int i = 0; i < 8; ++i)
            {
                uint16_t temp1 = crc & 0x0001;      // Obtem o bit menos significativo do CRC.  LMB -> menos significativo MSB -> Mais significativo.
                crc >>= 1;                          // Desloca o CRC para a direita.
                uint16_t temp2 = tempByte & 0x0001; // Obtém o bit menos significativo do tempByte.
                tempByte >>= 1;                     // Desloca o tempByte para a direita

                // Compara os bits menos significativos atraves do operador XOR. Caso temp1 e temp2 sejam diferentes o valor retornado será 1.
                if ((temp1 ^ temp2) == 1)
                {
                    // Se os bits são diferentes, o CRC é alterado com uma operação XOR com o polinômio.
                    crc ^= polynomial;
                }
            }
        }

        // Reporta o CRC
        return crc;
    }

    auto ABNTProtocol::addCRCToFrame(const std::vector<uint8_t> &frame, CRCType type) -> std::vector<uint8_t>
    {
        std::vector<uint8_t> frameWithCRC = frame;

        // Calcula o CRC
        uint16_t crcValue = calculateCRC16(frame, type);

        // Adiciona o CRC ao final do frame
        frameWithCRC.push_back(static_cast<uint8_t>(crcValue & 0xFF));        // Byte menos significativo
        frameWithCRC.push_back(static_cast<uint8_t>((crcValue >> 8) & 0xFF)); // Byte mais significativo

        return frameWithCRC;
    }

    void ABNTProtocol::printFrame(const std::vector<uint8_t> &frame)
    {
        for (uint8_t byte : frame)
        {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
        }
        std::cout << std::endl;
    }


    auto ABNTProtocol::isABNTFrame(const std::vector<uint8_t> &frame) -> bool
    {
        constexpr size_t MIN_REQUEST_SIZE = 66;
        constexpr size_t MIN_RESPONSE_SIZE = 258;

        if(frame.size() != MIN_REQUEST_SIZE && frame.size() != MIN_RESPONSE_SIZE) return false;

        int8_t command = frame.at(0);
        if((command >= 1 && command <= 99) && command != 0x05, command !=  0x06, command !=  0x10, command !=  0x15)
        {
            uint16_t receivedCRC = (frame.at(frame.size() - 1) << 8) | frame.at(frame.size() - 2);

            std::vector<uint8_t> data(frame.begin(), frame.end() - 2);

            uint16_t calculatedCRC = calculateCRC16(data, CRCType::ARC);

            if(receivedCRC == calculatedCRC) return true;
        }

        return false;
    }




}
