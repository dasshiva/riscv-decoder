#!/usr/bin/python3

import random
import sys

file = open("hello.S", "w");
file.write("_hello:\n");

instructions = ["lui", "auipc", "jal", "jalr", "beq", "bne", "blt",
                "bge", "bltu", "bgeu", "lb", "lh", "lw","lbu", "lhu",
                "sb", "sh", "sw", "xori", "ori", "andi", "slli",
                "srai", "addi", "slti", "sltiu", "srli", "add", "sub",
                "sll", "slt", "sltu", "xor", "srl", "sra", "or", "and",
                "fence", "pause", "ecall", "ebreak"]

smaple_size = 0

if len(sys.argv) < 2:
    sample_size = 1000
else:
    sample_size = int(sys.argv[1])

for _ in range(0, sample_size):
    ins = random.choice(instructions)
    if (ins.endswith("i") or ins.endswith("iu")) and ins != "lui":
        if ins in ["slli", "srli", "slti", "sltiu", "srli", "srai"]:
            imm = random.randint(0, 31)
        else:
            imm = random.randint(-2048, 2047)
        file.write(f"\t {ins} x{random.randint(1, 31)}, x{random.randint(1, 31)}, {imm}\n")
    elif ins in ["fence", "pause", "ecall", "ebreak"]:
        file.write(f"\t {ins}\n")
    elif ins.startswith("b"):
        file.write(f"\t {ins} x{random.randint(1,31)}, x{random.randint(1, 31)}, label\n")
    elif ins in ["lui", "auipc"]:
        file.write(f"\t {ins} x{random.randint(1, 31)}, {random.randint(1, 131172)}\n")
    elif ins == "jal":
        imm = random.randint(-65535, 65535)
        if abs(imm) % 2 != 0:
            imm -= 1
        file.write(f"\t {ins} x{random.randint(1, 31)}, {imm}\n")
    elif ins == "jalr":
        file.write(f"\t {ins} x{random.randint(1, 31)}\n");
    elif ins in ["lb", "lh", "lw", "lbu", "lhu", "sb", "sh", "sw"]:
        file.write(f"\t {ins} x{random.randint(1, 31)}, {random.randint(-2048, 2047)}(x{random.randint(1, 31)})\n")
    else:
        file.write(f"\t {ins} x{random.randint(1, 31)}, x{random.randint(1, 31)}, x{random.randint(1, 31)}\n")

file.write("label:\n");
