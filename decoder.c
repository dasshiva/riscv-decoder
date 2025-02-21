#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include "opcodes.h"
#include "lookup_structs.h"

#define ERROR_DECODING 0x1
#define ERROR_FILE     0

struct decoded_instruction {
	uint32_t original; // the original opcode we decoded from
	uint32_t flags; 
	union {
		int32_t imm; // long immediate for U-type and J-type
		int16_t short_imm; // short immediate for S and B-type
		uint8_t rtype_rs2; // carries rs2 if R-type
	};
	uint16_t opcode; // We assign opcodes to instructions individually so funct3 and funct7 are unnecessary
	union {
		uint8_t rs2; // carries rs2 for S and B-type
		uint8_t rd;  // rd for all other options
	};
	uint8_t rs1; // 0 for J and U types
};

struct decoder_state {
	uint64_t pc;
	uint64_t flags;
	struct decoded_instruction cache[4];
};

#define dump_decoder_state(decoder)  { \
	printf("pc = 0x%lx flags = 0x%lx", decoder.pc, decoder.flags); \
	return ERROR_DECODING; \
}

static int decode(struct decoder_state*, FILE*, uint64_t);

int decode_file(FILE* file) {
	struct decoder_state state = {0};
	fseek(file, 0, SEEK_END);
	uint64_t length = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (length % 4 != 0) {
		printf("file length is not aligned to 4 bytes, won't decode file\n");
		return ERROR_FILE;
	}

	if (decode(&state, file, length)) 
		dump_decoder_state(state);
	
	return 0;
}

void* decode_instruction(void* decode);

static int decode(struct decoder_state* state, FILE* file, uint64_t len) {
	struct timeval start, end;
	gettimeofday(&start, NULL);

	uint32_t instruction[4];
	int decoding = 0;
	pthread_t p1, p2, p3, p4;

	while (state->pc < len) {
		if (state->pc + 16 < len) {
			fread(&instruction, sizeof(uint32_t), 4, file);
			state->pc += 16;
			if (decoding) {
				pthread_join(p1, NULL);
				pthread_join(p2, NULL);
				pthread_join(p3, NULL);
				pthread_join(p4, NULL);
				decoding = 0;
			}

			state->cache[0].original = instruction[0];
			state->cache[1].original = instruction[1];
			state->cache[2].original = instruction[2];
			state->cache[3].original = instruction[3];

			pthread_create(&p1, NULL, &decode_instruction, &state->cache[0]);
			pthread_create(&p2, NULL, &decode_instruction, &state->cache[1]);
			pthread_create(&p3, NULL, &decode_instruction, &state->cache[2]);
			pthread_create(&p4, NULL, &decode_instruction, &state->cache[3]);
			decoding = 1;
		}
		else { // At this stage we have any of {4,8,12} bytes left
			fread(&instruction, sizeof(uint32_t), 1, file);
			state->cache[0].original = instruction[0];
			decode_instruction(&state->cache[0]);
			state->pc += 4;
		}
	}

	gettimeofday(&end, NULL);
	//printf("%lf ms", ((double)(end.tv_usec - start.tv_usec)) / 1000);

	return 0;
}


void* decode_instruction(void* decode) {
	struct decoded_instruction* ret = decode;
	uint32_t target = ret->original;

	uint32_t opcode = target & OPCODE_EXTRACT_MASK;
	int32_t imm = B_IMMED(target);
	printf("0x%x %d\n", target, imm);
	return NULL;
}

