#include "system.h"


void *memcpy(void *dst, void const *src, int n){
    char * ret = dst;
    char * p = dst;
    const char * q = src;
    while (n--)
        *p++ = *q++;
    return ret;
}


void *memset(void *dst, char val, int n){
	// 8bit
    char *temp = dst;
    for(;n != 0; n--) *temp++ = val;
    return dst;
}

/*
 * memset by word(16 bit)
 * */
uint16_t *memsetw(uint16_t *dest, uint16_t val, uint32_t count)
{
    uint16_t *temp = (uint16_t *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

/*
 * memset by double word(32 bit)
 * */
uint32_t *memsetdw(uint32_t *dest, uint32_t val, uint32_t count)
{
    uint32_t *temp = (uint32_t *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}


int strlen(const unsigned char * s) {
    int len = 0;
    while(*s++)
        len++;
    return len;
}
