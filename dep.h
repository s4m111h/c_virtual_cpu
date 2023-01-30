#ifndef DEP_H
#define DEP_H

#define FIRST_BYTE 0x00000000000000FF
#define byte unsigned char     // 1 bytes - 0 to 255.
#define u64 unsigned long long // 8 bytes - 0 to 18,446,744,073,709,551,615
#define s64 long long          // 8 bytes - -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
#define d64 double             // 8 bytes - 1.7E +/- 308 (15 digits)

enum registers
{
    r0,
    r1,
    r2,
    r3,
    r4,
    r5,
    r6,
    r7,
    f0,
    f1,
    f2,
    f3,
    f4,
    f5,
    f6,
    f7,
    NUM_REGISTERS
};

enum instr
{
    push,
    pushf,
    pop,
    popf,
    move,
    loadi,
    loadf,
    fclear,
    halt,
    NUM_INSTRUCTIONS
};

typedef struct
{
    s64 *mem;
    s64 max_mem;

    // registers
    s64 pc;
    s64 sp;
    s64 r[8];
    d64 fr[8];

    // instruction parts
    s64 inst;
    s64 dest;
    s64 src;

    // flags
    s64 zero;
    s64 ltz;
    s64 gtz;
} cpu;

void clear_flags(cpu *c);
void set_flags(cpu *c, s64 a, s64 b);
void fset_flags(cpu *c, d64 a, d64 b);

cpu *new_cpu(s64 *memory, s64 mem_size);
void run_cpu(cpu *c);
void fetch(cpu *c);
void execute(cpu *c);
void free_cpu(cpu *c);

#endif