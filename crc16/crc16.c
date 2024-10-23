#include "crc16.h"

unsigned short
crc16_ccitt(unsigned char const *p_data, unsigned int size, unsigned short const *p_crc)
{
    unsigned short crc = (p_crc == NULL) ? 0x0000 : *p_crc;
    unsigned char b = 0;

    if (p_crc == NULL)
    {
        b = 0;
    }

    for (unsigned int i = 0; i < size; i++)
    {
        for (unsigned char j = 0; j < 8; j++)
        {
            b = ((p_data[i] << j) & 0x80) ^ ((crc & 0x8000) >> 8);
            crc <<= 1;
            if (b != 0)
            {
                crc ^= 0x1021;
            }
        }
    }

    return crc;
}