#include <stdlib.h>
#include <stdio.h>

#include "my_asm_decoder.h"

struct instr_t decode_command(unsigned char cmd)
{
    if ((cmd >> 2) == 0b111111)
    {
        fprintf(stderr, "Unrecognized instruction: %x\n", (unsigned)cmd);
        abort();
    }

    struct instr_t instr;

    if ((cmd >> 7) == 0)
    {
        instr.opcode = MOVI;
        instr.opnd.imm = cmd;
        return instr;
    }

    // if second from left bit == 1 then instr.opcode = IN or OUT
    if (((cmd >> 6) & 1) == 1)
    {
        if (((cmd >> 2) & 1) == 0)
            instr.opcode = IN;
        else if (((cmd >> 2) & 1) == 1)
            instr.opcode = OUT;
        else
        {
            fprintf(stderr, "Bad In/OUT: %x\n", (unsigned)cmd);
            abort();
        }
        instr.opnd.rop = cmd & 0x3; // getting rightmost 2 bits
        return instr;
    }

    switch (cmd >> 4)
    {
    case ADD:
        instr.opcode = ADD;
        break;
    case SUB:
        instr.opcode = SUB;
        break;
    case DIV:
        instr.opcode = DIV;
        break;
    case MUL:
        instr.opcode = MUL;
        break;
    default:
        fprintf(stderr, "Unrecognized arithmetic instruction: %x\n", (unsigned)cmd);
        abort();
        break;
    }
    instr.opnd.ops.rs = cmd & 0x3;
    instr.opnd.ops.rd = (cmd >> 2) & 0x3;
    return instr;
}

void print_instr(struct instr_t instr)
{
    static const char *regnames[] = {"A", "B", "C", "D"};
    static const char *arithnames[] = {"ADD", "SUB", "MUL", "DIV"};

    switch (instr.opcode)
    {
    case MOVI:
        printf("MOVI D, %d\n", instr.opnd.imm);
        break;
    case IN:
        printf("IN %s\n", regnames[instr.opnd.rop]);
        break;
    case OUT:
        printf("OUT %s\n", regnames[instr.opnd.rop]);
        break;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
        printf("%s %s, %s\n", arithnames[instr.opcode - 8], regnames[instr.opnd.ops.rd], regnames[instr.opnd.ops.rs]);
        break;
    default:
        fprintf(stderr, "Unsupported instruction opcode: %x\n", instr.opcode);
        break;
    }
}

int main()
{
    unsigned command;
    while (scanf("%x", &command) == 1)
    {
        struct instr_t instr;
        unsigned char cmd = command & 0xFF; // getting the 8 bits of command
        instr = decode_command(cmd);
        print_instr(instr);
    }

    return 0;
}