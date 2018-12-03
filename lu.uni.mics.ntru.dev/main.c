#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include "sha256.h"

static int8_t X = 2;

int Math;

void choose(uint8_t octet, uint8_t *c) ;

void minRepresentation(uint8_t *c, int8_t *cP) ;

int16_t pow (int16_t a, int16_t n) ;

int16_t mgf1(uint8_t seed[], uint32_t min_calls_mask, uint8_t N);


void print (uint8_t array[], uint8_t length);

int main() {
    printf("Hello, World!\n");
    const uint8_t test2[] = {0xd0, 0x4c, 0x38, 0xca, 0x20, 0xa1, 0xb5, 0x5f,
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

    mgf1(test2, 6,20);

    return 0;
}



int16_t mgf1(uint8_t seed[], uint32_t min_calls_mask, uint8_t N){

    // Hash from 0 to min calls =>  min calls + 1 space needed
    uint8_t Z[36];

    sha256_hash(Z, seed, 65);

    // WARNING: may overflow
    uint8_t bufferSize = (uint8_t) (min_calls_mask+1 * 32);
    uint8_t *buffer = malloc(bufferSize * sizeof(uint8_t));


    // Fill the buffer
    uint8_t *ctr = Z +32;

    // Set counter to 0
    memset(ctr, 0, 4);

    for (uint8_t i = 0; i < min_calls_mask; ++i) {

        // Generate hash and add it to buffer
        sha256_hash((buffer + i*32), Z, 36);
        print(Z, 36);

        // Increment ctr
        if (++ctr[3] == 0) {
            if (++ctr[2] == 0) {
                if (++ctr[1] == 0) {
                    ++ctr[0];
                }
            }
        }
    }



    uint8_t *out = malloc(N* sizeof(uint8_t));
    uint8_t *outWork = out;


    uint8_t octet_available = bufferSize;
    uint8_t *octet = buffer;

    uint8_t workN = N;
    while (workN){

        if (octet_available == 0){
            return 1;
        }

        if (*octet < 243){
            choose(*octet, outWork);
            outWork +=5;
            workN--;
        }
        octet++;
        octet_available--;

    }

    free(buffer);

    print(out, N);

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

void minRepresentation(uint8_t *c, int8_t *cP) {
    for (int i = 0; i < 5; ++i) {
        if (c[i] == 2) {
            cP[i] = -1;
        } else {
            cP[i] = c[i];
        }

    }
}

int16_t pow (int16_t a, int16_t n) {
    int16_t result = 1;
    for (int i = 0; i < n; ++i) {
        result *= n;
    }
    return n;
}


