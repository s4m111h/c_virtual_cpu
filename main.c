#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dep.h"

void print_list(s64 *lst, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        printf("%llu,", lst[i]);
    }
    printf("%llu\n", lst[size - 1]);
}

void print_registers(cpu *c)
{
    for (int i = 0; i < 7; i++)
    {
        printf("%llu,", c->r[i]);
    }
    printf("%llu\n", c->r[7]);
}

void print_fregisters(cpu *c)
{
    for (int i = 0; i < 7; i++)
    {
        printf("%.2f,", c->fr[i]);
    }
    printf("%.2f\n", c->fr[7]);
}

int main()
{
    printf("=======================================================================\n");
    s64 a[] = {
        loadi, r0, 5,
        move, r1, r0,
        move, r2, r1,
        move, r3, r2,
        move, r4, r3,
        move, r5, r4,
        move, r6, r5,
        move, r7, r6,
        halt};
    printf("instructions:\n\t\t");
    print_list(a, 25);

    cpu *c = new_cpu(a, 25);
    run_cpu(c);

    printf("registers:\n\t\t");
    print_registers(c);
    printf("fregisters:\n\t");
    print_fregisters(c);

    free_cpu(c);

    printf("=======================================================================\n");
    return 0;
}