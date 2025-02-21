#ifndef __LOOKUP_STRUCTS_H__
#define __LOOKUP_STRUCTS_H__

#include <stdint.h>

static const uint32_t FUNCT3_EXTRACT_MASK       =  ((1 << 14) | (1 << 13) | (1 << 12));
static const uint32_t FUNCT7_EXTRACT_MASK       =  (~((1 << 25) - 1));
static const uint32_t RD_EXTRACT_MASK           =  ((1 << 11) | (1 << 10) | (1 << 9) | (1 << 8) | (1 << 7));
static const uint32_t OPCODE_EXTRACT_MASK       =  ((uint8_t)~(1 << 7));
static const uint32_t RS2_EXTRACT_MASK          =  ((1 << 24) | (1 << 23) | (1 << 22) | (1 << 21) | (1 << 20));
static const uint32_t RS1_EXTRACT_MASK          =  ((1 << 19) | (1 << 18) | (1 << 17) | (1 << 16) | (1 << 15));
static const uint32_t U_TYPE_IMMED_EXTRACT_MASK =  (~((1 << 12) - 1));
static const uint32_t S_TYPE_LOW_IMMED          =  RD_EXTRACT_MASK;   // S_TYPE immed[4:0] occupies the same space as rd
static const uint32_t S_TYPE_HIGH_IMMED         =  FUNCT7_EXTRACT_MASK; // S_TYPE immed[11:5] occupies the same space as funct7
static const uint32_t I_TYPE_IMMED_EXTRACT_MASK =  (~((1 << 20) - 1));
static const uint32_t B_TYPE_BIT_11             =  (1 << 7);
static const uint32_t B_TYPE_BIT_12             =  (1 << 31);
static const uint32_t B_TYPE_LO_BITS            =  ((1 << 11) | (1 << 10) | (1 << 9) | (1 << 8)); // immed[4:1]
static const uint32_t B_TYPE_HI_BITS            =  ((1 << 30) | (1 << 29) | (1 << 28) | (1 << 27) | (1 << 26) | (1 << 25)); // immed[10:5]
static const uint32_t J_TYPE_BIT_20             =  (1 << 31);
static const uint32_t J_TYPE_HI_BITS            =  ((RS1_EXTRACT_MASK) | (FUNCT3_EXTRACT_MASK)); // Immed [19:12]
static const uint32_t J_TYPE_BIT_11             =  (1 << 20);
static const uint32_t J_TYPE_LO_BITS            =  (B_TYPE_HI_BITS | (1 << 24) | (1 << 23) | (1 << 22) | (1 << 21)); // Immed[10:1]

static const inline int32_t J_IMMED(const uint32_t x) {
    return ((x & J_TYPE_BIT_20) >> 11) | (x & J_TYPE_HI_BITS) | ((x & J_TYPE_BIT_11) >> 9) | ((x & J_TYPE_LO_BITS) >> 20);
} 

static const inline int32_t B_IMMED(const uint32_t x) {
    int32_t ret = ((x & B_TYPE_BIT_12) >> 19) | ((x & B_TYPE_BIT_11) << 4) | ((x & B_TYPE_HI_BITS) >> 21) | ((x & B_TYPE_LO_BITS) >> 6);
    return ret;
}

static const inline int32_t I_IMMED(const uint32_t x) {
    int32_t ret = (x & I_TYPE_IMMED_EXTRACT_MASK);
    return  ret >> 20;
}

static const inline int32_t S_IMMED(const uint32_t x) {
    int32_t immhi =  x & S_TYPE_HIGH_IMMED;
    int32_t immlo =  x & S_TYPE_LOW_IMMED;
    return (immhi >> 20) | (immlo >> 7);
}

static const inline int32_t U_IMMED(const uint32_t x) {
    return x & U_TYPE_IMMED_EXTRACT_MASK;
}

typedef struct {
    
} lookup_ins;

#endif