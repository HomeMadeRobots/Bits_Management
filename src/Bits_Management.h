#ifndef BITS_MANAGEMENT_H
#define BITS_MANAGEMENT_H

#include <stdint.h>
#include <stdbool.h>

/*============================================================================*/
static const uint8_t SET_MASK[8] =
    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

static const uint8_t RESET_MASK[8] =
    { 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F };

#define Set_Bit_Uint8(carrier,bit)      (carrier |= SET_MASK[bit] )
#define Reset_Bit_Uint8(carrier,bit)    (carrier &= RESET_MASK[bit] )
#define Test_Bit_Uint8(carrier,bit)     ((carrier&SET_MASK[bit])?true:false)


/*============================================================================*/
void Set_Bit_Block( uint8_t* block, uint8_t bit_index );
void Reset_Bit_Block( uint8_t* block, uint8_t bit_index );
int Test_Bit_Block( const uint8_t* block, uint8_t bit_index );
void Permute_Bits(
    const uint8_t* initial_block,
    uint8_t block_size,
    uint8_t* result,
    const uint8_t* permutation_table );


/*============================================================================*/
bool Is_Byte_Even( uint8_t a_byte );


#endif