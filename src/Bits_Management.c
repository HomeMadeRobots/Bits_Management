#include "Bits_Management.h"

#include "Memory_Mapping.h"


static const uint8_t SET_MASK_BLOCK[8] =
    { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

static const uint8_t RESET_MASK_BLOCK[8] =
    { 0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE };


/*============================================================================*/
void Set_Bit_Block( uint8_t* block, uint8_t bit_index )
{
    block[bit_index/8] |= SET_MASK_BLOCK[bit_index%8];
}
/*----------------------------------------------------------------------------*/
void Reset_Bit_Block( uint8_t* block, uint8_t bit_index )
{
    block[bit_index/8] &= RESET_MASK_BLOCK[bit_index%8];
}
/*----------------------------------------------------------------------------*/
int Test_Bit_Block( const uint8_t* block, uint8_t bit_index )
{
    return ( ( block[bit_index/8] & SET_MASK_BLOCK[bit_index%8] )!=0 ) ? 1 : 0;
}
/*----------------------------------------------------------------------------*/
void Permute_Bits(
    const uint8_t* input_block,
    uint8_t block_size,
    uint8_t* output_block,
    const uint8_t* permutation_table )
{
    uint8_t id_bit = 0;
    uint8_t id_tested_bit = 0;
    for ( id_bit=0 ; id_bit<block_size ; id_bit++ )
    {
        id_tested_bit = pgm_read_byte(&permutation_table[id_bit]);
        if( Test_Bit_Block( input_block, id_tested_bit ) )
        {
            Set_Bit_Block( output_block, id_bit );
        }
        else
        {
            Reset_Bit_Block( output_block, id_bit );
        }
    }
}


/*============================================================================*/
static const PROGMEM bool ParityTable256[256] = 
{
#   define P2(n) n, n^1, n^1, n
#   define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#   define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
    P6(0), P6(1), P6(1), P6(0)
};
bool Is_Byte_Even( uint8_t a_byte )
{
    return !pgm_read_byte(&ParityTable256[a_byte]);
}
