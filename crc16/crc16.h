#ifndef _CRC16_H_
#define _CRC16_H_


/**
 * @brief Compute the CRC-16 CCITT
 * 
 * @param p_data Pointer to the data buffer
 * @param size Size of the data buffer
 * @param p_crc Pointer to the CRC value
 */
unsigned short
crc16_ccitt(unsigned char const *p_data, unsigned int size, unsigned short const *p_crc);

#endif
