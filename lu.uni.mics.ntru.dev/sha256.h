#ifndef _SHA256_H
#define _SHA256_H

#include <stddef.h>

#ifdef _MSC_VER
typedef unsigned __int8  uint8_t;   // 8-bit unsigned integer (0~255)
typedef unsigned __int16 uint16_t;  // 16-bit unsigned integer
typedef unsigned __int32 uint32_t;  // 32-bit unsigned integer
typedef unsigned __int64 uint64_t;  // 64-bit unsigned integer
#else
#include <stdint.h>
#endif

typedef struct
{
  uint32_t hval[8];  // current (i.e. intermediate) hash value
  uint8_t mbuf[64];  // buffer for a 64-byte block of the message
  uint64_t length;   // overall length of hashed message (in bits) 
  uint8_t mbytes;    // number of bytes contained in mbuf array
} sha256_context_t;

// Low-level API
void sha256_init(sha256_context_t *ctx);
void sha256_update(sha256_context_t *ctx, const void *data, size_t dlen);
void sha256_final(sha256_context_t *ctx, uint8_t *hashval);

// High-level API
void sha256_hash(uint8_t *hashval, const void *data, size_t dlen);

#endif
