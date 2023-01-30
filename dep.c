#include <stdio.h>
#include <stdlib.h>
#include "dep.h"

void clear_flags(cpu *c)
{
    c->zero = 0;
    c->ltz = 0;
    c->gtz = 0;
    // printf("Flag Cleared\n");
}

void set_flags(cpu *c, s64 a, s64 b)
{
    s64 res = a - b;
    c->zero = (res == 0);
    c->ltz = (res < 0);
    c->gtz = (res > 0);
    // printf("Flag Set\n");
}

void fset_flags(cpu *c, d64 a, d64 b)
{
    d64 res = a - b;
    c->zero = (res == 0);
    c->ltz = (res < 0);
    c->gtz = (res > 0);
    // printf("Flag Fset\n");
}

cpu *new_cpu(s64 *memory, s64 mem_size)
{
    cpu *c = malloc(sizeof(cpu));
    c->mem = memory;
    c->sp = mem_size - 1;
    c->max_mem = mem_size;
    c->pc = -1;
    c->inst = 0;
    return c;
}

void run_cpu(cpu *c)
{
    while (c->inst != halt)
    {
        fetch(c);
        execute(c);
    }
}

void fetch(cpu *c)
{
    c->pc++;
    c->inst = c->mem[c->pc] & FIRST_BYTE;
    c->dest = c->mem[c->pc + 1];
    c->src = c->mem[c->pc + 2];
}

void execute(cpu *c)
{
    switch (c->inst)
    {
    case push:
        c->mem[--c->sp] = c->r[c->mem[++c->pc]];
        break;
    case pushf:
        c->mem[--c->sp] = (s64)c->fr[c->mem[++c->pc] - 8];
        break;
    case pop:
        c->r[c->mem[++c->pc]] = c->mem[c->sp++];
        break;
    case popf:
        c->fr[c->mem[++c->pc] - 8] = (d64)c->mem[c->sp++];
        break;
    case move:
        c->r[c->dest] = c->r[c->src];
        c->pc += 2;
        break;
    case loadi:
        c->r[c->dest] = c->src;
        c->pc += 2;
        break;
    case loadf:
        c->fr[c->dest - 8] = (d64)c->src;
        c->pc += 2;
        break;
    case fclear:
        clear_flags(c);
        break;
    }
}

void free_cpu(cpu *c)
{
    free(c);
}
