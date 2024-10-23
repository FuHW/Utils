#ifndef __BASE64_H_
#define __BASE64_H_

#define BASE64_ENCODE_OUT_SIZE(s)   ((unsigned int)((((s) + 2) / 3) * 4))
#define BASE64_DECODE_OUT_SIZE(s)   ((unsigned int)(((s) / 4) * 3))

/**
 * @brief base64 encode
 * 
 * @param in data to encode
 * @param inlen data length
 * @param out encoded data
 * 
 * @return unsigned int encoded length
 */
unsigned int
base64_encode(const unsigned char *in, unsigned int inlen, char *out);

/**
 * @brief base64 decode
 * 
 * @param in data to decode
 * @param inlen data length
 * @param out decoded data
 * 
 * @return unsigned int decoded length
 */
unsigned int
base64_decode(const char *in, unsigned int inlen, unsigned char *out);

#endif
