#ifndef __OPCODES_H__
#define __OPCODES_H__

// A list of the major opcodes for RV64G
enum Opcode {
	// RV-32I
	LOAD   =    3,
	STORE  =   35,
	SYSTEM =  115, // Includes ECALL, EBREAK and Zicsr
	PAUSE  =   15,
	FENCE  =   15,
	REG    =   51,
	IMM    =   19,
	BRANCH =   99,
	JALR   =  103,
	JAL    =  111,
	AUIPC  =   23,
	LUI    =   55,

	// RV-64I (in addition to RV32I)
	REG_WIDE = 59, // ADDIW, SLLIW, SRLIW, SRAIW
	IMM_WIDE = 27, // ADDW, SUBW, SLLW, SRLW, SRAW

	// RV32M
	MUL_DIV = 51, // REG with funct7 = 1

	// RV64M (in addition to RV32M)
	MUL_DIV_WIDE = 59, 

	// RV32A and RV64A use the same opcode 
	ATOMIC = 47,

	// RV32 and RV64F use the same opcodes with diff funct3 values
	FP_LOAD  =  7,
	FP_STORE = 39,
	FP_MADD  = 67,
	FP_MSUB  = 71,
	FP_NMADD = 79,
	FP_NMSUB = 75,
	FP_FOP   = 83,

	// From here we define our own opcodes instruction wise leaving us the space for about 1500 instructions
	// Note some instructions (eg. LUI, AUIPC, JAL, JALR) already have their unique opcodes
	// Do not assign new opcodes to them!!
	INSTRUCTION_BASE = 64000, 

	// These use BRANCH major opcode
	BEQ,
	BNE,
	BLT,
	BGE,
	BLTU,
	BGEU,

	// These use LOAD major opcode
	LB,
	LH,
	LW,
	LBU,
	LHU,
	LWU,
	LD,

	// These use STORE major opcode
	SB,
	SH,
	SW,
	SD,

	// These use IMM major opcode
	ADDI,
	SLTI,
	SLTIU,
	XORI,
	ORI,
	ANDI,
	SLLI, 
	SRLI,
	SRAI,
	// The last three use (SLLI, SRLI, SRAI) have the same representation in RV32 and RV64

	// These use REG major opcode
	ADD,
	SUB,
	SLL,
	SLT,
	SLTU,
	XOR,
	SRL,
	SRA,
	OR,
	AND,

	// These use SYSTEM major opcode
	ECALL,
	EBREAK,
	CSRRW,
	CSRRS,
	CSRRC,
	CSRRWI,
	CSRRSI,
	CSRRCI,

	// These use IMM_WIDE major opcode
	ADDIW,
	SLLIW,
	SRLIW,
	SRAIW,

	// These use REG_WIDE major opcode
	ADDW,
	SUBW,
	SLLW,
	SRLW,
	SRAW,

	// These use MUL_DIV major opcode
	MUL,
	MULH,
	MULHSU,
	MULHU,
	DIV,
	DIVU,
	REM,
	REMU,

	// These use MUL_DIV_WIDE major opcode
	MULW,
	DIVW,
	DIVUW,
	REMW,
	REMUW,

	// These use ATOMIC major opcode
	// The *_W opcodes represent RV32A while the *_D opcodes represent RV64A
	LR_W,
	SC_W,
	AMOSWAP_W,
	AMOADD_W,
	AMOXOR_W,
	AMOAND_W,
	AMOOR_W,
	AMOMIN_W,
	AMOMAX_W,
	AMOMINU_W,
	AMOMAXU_W,

	LR_D,
	SC_D,
	AMOSWAP_D,
	AMOADD_D,
	AMOXOR_D,
	AMOAND_D,
	AMOOR_D,
	AMOMIN_D,
	AMOMAX_D,
	AMOMINU_D,
	AMOMAXU_D,

	// These use FP_LOAD major opcode
	FLW,
	FLD,

	// These use FP_STORE major opcode
	FSW,
	FSD,

	// These use FP_MADD major opcode (*_S represents the F extension while *_D represents the D extension)
	FMADD_S,
	FMADD_D,

	// These use FP_MSUB major opcode
	FMSUB_S,
	FMSUB_D,

	// These use FP_NMADD major opcode
	FNMADD_S,
	FNMADD_D,

	// These use FP_NMSUB major opcode
	FNMSUB_S,
	FNMSUB_D,

	// These use FP_FOP major opcode (again *_S represents the F extension while *_D represents the D extension)
	// Opcodes without a suffix do not have equivalents in the other extension
	// This is the combination of RV32F and RV32D
	FADD_S,
	FADD_D,
	FSUB_S,
	FSUB_D,
	FMUL_S,
	FMUL_D,
	FDIV_S,
	FDIV_D,
	FSQRT_S,
	FSQRT_D,
	FSGNJ_S,
	FSGNJ_D,
	FSGNJN_S,
	FSGNJN_D,
	FSGNJX_S,
	FSGNJX_D,
	FMIN_S,
	FMIN_D,
	FMAX_S,
	FMAX_D,
	FCVTWS,
	FCVTWUS,
	FMVXW,
	FEQ_S,
	FEQ_D,
	FLT_S,
	FLT_D,
	FLE_S,
	FLE_D,
	FCLASS_S,
	FLCASS_D,
	FCVTSW,
	FCVTSWU,
	FMVWX,
	FCVTSD,
	FCVTDS,
	FCVTWD,
	FCVTWUD,
	FCVTDW,
	FCVTDWU,

	// Now we put RV64F and RV64D which use FP_FOP opcode as well
	FCVTLS,
	FCVTLUS,
	FCVTSL,
	FCVTSLU,
	FCVTLD,
	FCVTLUD,
	FMVXD,
	FCVTDL,
	FCVTDLU,
	FMVDX,

	INVALID  = 65535 // Intentionally large opcode not used by any impl. right now
};

#endif