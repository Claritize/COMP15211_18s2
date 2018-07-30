#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned int Word;

Word reverseBits(Word w);

int main(void) {
    
    Word w1 = 0x01234567;
    //0000 => 0000 = 0
    //0001 => 1000 = 8
    //0010 => 0100 = 4
    //0011 => 1100 = C
    //0100 => 0010 = 2
    //0101 => 1010 = A
    //0110 => 0110 = 6
    //0111 => 1110 = E
    assert(reverseBits(w1) == 0xE6A2C480);
    printf("All tests passed!");

    return 0;
}

Word reverseBits(Word w) {

    Word ret = 0;
    int i;
    for (int bit = 0; bit < 32; bit++) {
        Word wMask = 1 << (31-bit);
        Word retMask = 1 << bit;
        if (w & wMask) {
            ret = ret | retMask;
        }
    }    

    return ret;
}