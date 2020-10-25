#include "minicrt.h"

extern int main(int argc, char *argv[]);

void exit(int);

static void crt_fatal_error(const char *msg)
{
    // printf("fatal error: %s", msg);
    exit(1);
}

void mini_crt_entry(void)
{
    long ret;

    long argc;
    char **argv;
    char *ebp_reg = 0;
    // ebp_reg = %ebp
    asm("movq %%rbp, %0 \n":"=r"(ebp_reg)); //__asm__¡¡__volatile__("Instruction List" : Output : Input : Clobber/Modify);
    argc = *(int *) (ebp_reg + 8);
    argv = (char **) (ebp_reg + 16);
    if (!mini_crt_heap_init())
        crt_fatal_error("heap initialize failed");

    if (!mini_crt_io_init())
        crt_fatal_error("IO initialize failed");

    ret = main(argc, argv);
    exit(ret);
}

void exit(int exitCode)
{
    asm("movq %0, %%rbx \n\t"
        "movq $1, %%rax \n\t"
        "int $0x80 \n\t"
        "hlt \n\t"::"m"(exitCode)
    );
}