#include <stdio.h>
#include <stdint.h>
#include <opencl-c.h>
#include <stdlib.h>

static int8_t X = 4;

int Math;

void choose(uint8_t octet, uint8_t *c) ;

void convert(uint8_t *c, int8_t *cP) ;

int main() {
    printf("Hello, World!\n");
    return 0;
}

uint8_t hash(uint8_t *message){
    return 0;
}

void mgf1(uint8_t *seed, uint8_t seed_len, uint8_t min_calls_mask, uint8_t N){

    uint8_t Z = hash(seed);

    uint8_t * buf = malloc(min_calls_mask * sizeof(uint8_t));

    uint8_t i = 0;
    int16_t v = 0;

    for (int i = 0; i < min_calls_mask; ++i) {
        uint8_t octet = buf[i];
        uint8_t *c = malloc(5* sizeof(uint8_t));
        int8_t *cP = malloc(5* sizeof(int8_t));

        if (octet < 243) {
            choose(octet, c);
            convert(c,cP);
            int j = 0;
            while (j < 5) {
                int k = i + j;
                v = v + (cP[k] *  ((int16_t) (Math.pow(X,k))));
                j++;
            }
            i = i + 5;
        }
    }

    int16_t output = v %  ((int16_t) (Math.pow(X,N)));


    free(buf);

}

void choose(uint8_t octet, uint8_t *c) {

    for (int i = 0; i < 5; ++i) {
        c[i] = (uint8_t) (octet % 3);
        octet = (uint8_t) ((octet - c[i]) / 3);
    }

}

void convert(uint8_t *c, int8_t *cP) {
    for (int i = 0; i < 5; ++i) {
        if (c[i] == 2) {
            cP[i] = -1;
        } else {
            cP[i] = c[i];
        }

    }
}