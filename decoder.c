#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#define _GNU_SOURCE
#include <sched.h>
#include <time.h>

#define ERROR_DECODING 0x1
#define ERROR_FILE     0

struct decoder_state {
	uint64_t pc;
	uint64_t flags;
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

int decode_instruction(void* decode);

static int decode(struct decoder_state* state, FILE* file, uint64_t len) {
	struct timeval start, end;
	gettimeofday(&start, NULL);

	uint32_t instruction[4];
	struct decoded_instruction decoded_buffer[4];
	int decoding = 0, p1 = 0, p2 = 0, p3 = 0, p4= 0;

	while (state->pc < len) {
		if (state->pc + 16 < len) {
			fread(&instruction, sizeof(uint32_t), 4, file);
			state->pc += 16;
			if (decoding)

			p1 = clone(&decode_instruction, NULL, CLONE_VM | CLONE_SIGHAND, &decoded_buffer[0]);
			p2 = clone(&decode_instruction, NULL, CLONE_VM | CLONE_SIGHAND, &decoded_buffer[1]);
			p3 = clone(&decode_instruction, NULL, CLONE_VM | CLONE_SIGHAND, &decoded_buffer[2]);
			p4 = clone(&decode_instruction, NULL, CLONE_VM | CLONE_SIGHAND, &decoded_buffer[3]);
		}

		else { // At this stage we have any of {4,8,12} bytes left
			fread(&instruction, sizeof(uint32_t), 1, file);
			state->pc += 4;
		}
	}

	gettimeofday(&end, NULL);
	if (end.tv_usec - start.tv_usec < 1000) 
		printf("Time taken to decode = %ld micros", end.tv_usec - start.tv_usec);
	else
		printf("Time taken to decode = %lf millis", ((double)(end.tv_usec - start.tv_usec)) / 1000);

	return 0;
}

int decode_instruction(void* decode) {
	struct decoded_instruction* ins = decode;
	return 0;
}

