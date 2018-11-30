#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "sha256.h"

static int8_t X = 5;

int Math;

void choose(uint8_t octet, uint8_t *c) ;

void minRepresentation(uint8_t *c, int8_t *cP) ;

int16_t pow (int16_t a, int16_t n) ;

int16_t mgf1(uint8_t seed[], uint8_t min_calls_mask, uint8_t N);

void print (uint8_t array[], uint8_t length);

int main() {
    printf("Hello, World!\n");
    const uint8_t string1[] = "abc";
    uint8_t hashval[32];

    sha256_hash(hashval, string1, 3);

    mgf1(string1, 3,10);

    return 0;
}



int16_t mgf1(uint8_t seed[], uint8_t min_calls_mask, uint8_t N){

    // Hash from 0 to min calls =>  min calls + 1 space needed
    min_calls_mask = (uint8_t) (min_calls_mask + 1);
    uint8_t Z[32];

    sha256_hash(Z, seed, 3);

    // WARNING: may overflow
    uint8_t bufferSize = (uint8_t) (min_calls_mask * 32);
    uint8_t *buffer = malloc(bufferSize * sizeof(uint8_t));

    // Create copy of the table
    uint8_t Zi[33];
    for (int j = 0; j < 32; ++j) {
        Zi[j]= Z [j];
    }

    // Fill the buffer
    for (uint8_t i = 0; i < min_calls_mask; ++i) {
        Zi[32] = i;
        sha256_hash((buffer + i*32), Zi, 3);
    }
    print(buffer, bufferSize);

    uint16_t v = 0;
    uint8_t i = 0;

    for (uint8_t j = 0; j < bufferSize; ++j) {
        uint8_t octet = buffer[j];
        if ( octet < 243 ){

            uint8_t c[5];
            int8_t cP[5];
            choose(octet, c);
            minRepresentation(c,cP);

            for (uint8_t k = 0; k < 5; ++k) {
                v = v + cP[i+k]*pow(X,i+k);
            }

            i = (uint8_t) (i + 5);

        }
    }

//    uint8_t i = 0;
//    int16_t v = 0;
//
//    for (int i = 0; i < min_calls_mask; ++i) {
//        uint8_t octet = buffer[i];
//        uint8_t *c = malloc(5* sizeof(uint8_t));
//        int8_t *cP = malloc(5* sizeof(int8_t));
//
//        if (octet < 243) {
//            choose(octet, c);
//            minRepresentation(c,cP);
//            int j = 0;
//            while (j < 5) {
//                int k = i + j;
//                v = v + (cP[k] *  ((int16_t) (pow(X,k))));
//                j++;
//            }
//            i = i + 5;
//        }
//    }
//
//    int16_t output = v %  ((int16_t) (pow(X,N)));
//
//
//    free(buffer);

    return 0;

}


void print (uint8_t array[], uint8_t length){
    for (uint8_t i = 0; i < length; ++i) {
        printf("%02x", array[i]);
    }

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