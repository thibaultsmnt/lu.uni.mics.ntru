#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include "sha256.h"

static int8_t X = 2;

static int8_t HASH_OUTPUT_SIZE = 32;
static int8_t MIN_CALLS_MASK_SIZE = 4;

void choose(uint8_t octet, uint8_t *c) ;

uint8_t mgf1(uint8_t seed[], uint8_t seed_len, uint8_t min_calls_mask, uint8_t N, uint8_t *mask);

void print (uint8_t array[], uint8_t length);

int main() {
    printf("Hello, World!\n");
    const uint8_t seed[] = {0xd0, 0x4c, 0x38, 0xca, 0x20, 0xa1, 0xb5, 0x5f,
                            0x3e, 0x95, 0x47, 0x1f, 0x2b, 0xb1, 0xc0, 0x6e,
                            0x70, 0xd0, 0xf0, 0x97, 0x52, 0xf4, 0x60, 0x3b,
                            0xf5, 0x52, 0xc3, 0x8b, 0x76, 0x7a, 0x32, 0x62,
                            0x55, 0x3c, 0xa5, 0xf4, 0x35, 0x06, 0xec, 0xcc,
                            0x7d, 0x52, 0x84, 0xe3, 0x3d, 0x24, 0x6e, 0x90,
                            0x09, 0xe9, 0xe3, 0xaa, 0x68, 0x71, 0x00, 0x5b,
                            0xc8, 0x53, 0x02, 0x80, 0x78, 0xe3, 0x86, 0x2c,
                            0xed, 0x91, 0x63, 0x56, 0x5a, 0x3d, 0xc5, 0x7d,
                            0xd5, 0x91, 0xaf, 0x9b, 0x96, 0x3c, 0xc7, 0xb5,
                            0x6d, 0x5f, 0xe6, 0x6d, 0x8a, 0x06, 0xf5, 0xee,
                            0xc6, 0xed, 0xc2, 0x3f, 0x59, 0xb2, 0x07, 0x5f,
                            0xb5, 0xb9, 0x60, 0xc7, 0x80};
    uint8_t seed_len = sizeof(seed) / sizeof(seed[0]);
    uint8_t min_calls_mask = 6;
    uint8_t N = 20;
    uint8_t *mask = malloc(N * sizeof(uint8_t));

    mgf1(seed, seed_len, 6, N, mask);
    print(mask, N);

    return 0;
}


uint8_t mgf1(uint8_t seed[], uint8_t seed_len, uint8_t min_calls_mask, uint8_t N, uint8_t *mask){

    uint8_t Z[36];

    sha256_hash(Z, seed, seed_len);

    uint8_t bufferSize = (uint8_t) (min_calls_mask * HASH_OUTPUT_SIZE);
    uint8_t *buffer = malloc(min_calls_mask * sizeof(uint8_t));


    // Fill the buffer
    uint8_t *ctr = Z +32;

    // Set counter to 0
    memset(ctr, 0, 4);

    for (uint8_t i = 0; i < min_calls_mask; ++i) {

        // Generate hash and add it to buffer
        sha256_hash((buffer + i*HASH_OUTPUT_SIZE), Z, (size_t) (HASH_OUTPUT_SIZE + MIN_CALLS_MASK_SIZE));

        // Increment ctr
        if (++ctr[3] == 0) {
            if (++ctr[2] == 0) {
                if (++ctr[1] == 0) {
                    ++ctr[0];
                }
            }
        }
    }

    print(buffer, bufferSize);

    uint8_t octet_available = bufferSize;
    uint8_t *octet = buffer;

    while (N >=5 ){

        if (octet_available == 0){
            return 1;
        }

        if (*octet < 243){
            choose(*octet, mask);
            mask +=5;
            N -= 5;
        }
        octet++;
        octet_available--;

    }

    while (N) {

        uint8_t trits [5];
        if (octet_available == 0){
            return 1;
        }

        if (*octet < 243){
            choose(*octet, trits);
            memcpy(mask, trits, N);
            N = 0;
        } else {
            octet++;
            --octet_available;
        }

    }

    free(buffer);

    return 0;

}


void print (uint8_t array[], uint8_t length){
    for (uint8_t i = 0; i < length; ++i) {
        printf("0x%02x, ", array[i]);
    }
    printf("\n");


}
void choose(uint8_t octet, uint8_t *c) {

    for (int i = 0; i < 5; ++i) {
        c[i] = (uint8_t) (octet % 3);
        octet = (uint8_t) ((octet - c[i]) / 3);
    }

}


