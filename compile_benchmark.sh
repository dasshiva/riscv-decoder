#$1 is the source file
elf="${1}.elf"
bin="${1}.bin"
clang $1 -target riscv64-unknown-elf -march=rv64izihintpause -mabi=lp64 -o $elf -nostdlib -Wl,-Ttext=0x0
llvm-objcopy -O binary $elf $bin