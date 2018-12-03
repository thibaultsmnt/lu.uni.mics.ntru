#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "sha256.h"

static int8_t X = 2;

int Math;

void choose(uint8_t octet, uint8_t *c) ;

void minRepresentation(uint8_t *c, int8_t *cP) ;

int16_t pow (int16_t a, int16_t n) ;

int16_t mgf1(uint8_t seed[], uint8_t min_calls_mask, uint8_t N);

void print (uint8_t array[], uint8_t length);

int main() {
    printf("Hello, World!\n");
    const uint8_t string1[] = ">";
    const uint8_t test[] = ">6ì@hAY›Eðš¥ãX˜Á© ÿ5×—ÀêçP";
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

    uint8_t hashval[32];

    uint8_t length = sizeof(test2) / sizeof(test2[0]);

    //sha256_hash(hashval, test, 20);

    mgf1(test2, 6,20);

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
    printf("\n");

    uint16_t v = 0;
    uint8_t i = 0;

    for (uint8_t j = 0; j < bufferSize; ++j) {
        uint8_t octet = buffer[j];
        if ( octet < 243 ){

            uint8_t c[5];
            int8_t cP[5];
            choose(octet, c);
            print(c,5);
            minRepresentation(c,cP);

            for (uint8_t k = 0; k < 5; ++k) {
                v = v + cP[i+k]*pow(X,i+k);
            }

            i = (uint8_t) (i + 5);

        }
    }
    printf("%02x", v);


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
        printf("0x%02x, ", array[i]);
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