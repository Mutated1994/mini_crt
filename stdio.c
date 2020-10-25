#include "minicrt.h"

int mini_crt_io_init()
{
    return 1;
}

static f_size open(const char *pathname, f_size flags, f_size mode)
{
    f_size fd = 0;
    asm("movq $5, %%rax \n\t"
        "movq %1, %%rbx \n\t"
        "movq %2, %%rcx \n\t"
        "movq %3, %%rdx \n\t"
        "int $0x80 \n\t"
        "movq %%rax, %0 \n\t":
    "=m"(fd):"m"(pathname), "m"(flags), "m"(mode)
    );
    return fd;
}

static f_size read(f_size fd, void *buffer, u_f_size size)
{
    f_size ret = 0;
    asm("movq $3, %%rax \n\t"
        "movq %1, %%rbx \n\t"
        "movq %2, %%rcx \n\t"
        "movq %3, %%rdx \n\t"
        "int $0x80 \n\t"
        "movq %%rax, %0 \n\t":
    "=m"(ret):"m"(fd), "m"(buffer), "m"(size)
    );
    return ret;
}

static f_size write(f_size fd, const void *buffer, u_f_size size)
{
    f_size ret = 0;
    asm( "movq $4, %%rax \n\t"
         "movq %1, %%rbx \n\t"
         "movq %2, %%rcx \n\t"
         "movq %3, %%rdx \n\t"
         "int $0x80 \n\t"
         "movq %%rax, %0 \n\t":
    "=m"(ret):"m"(fd), "m"(buffer), "m"(size));
    return ret;
}

static f_size close(f_size fd)
{
    f_size ret = 0;
    asm("movq $6, %%rax \n\t"
        "movq %1, %%rbx \n\t"
        "int $0x80 \n\t"
        "movq %%rax, %0 \n\t":
    "=m"(ret):"m"(fd));
    return ret;
}

static f_size seek(f_size fd, f_size offset, f_size mode)
{
    f_size ret = 0;
    asm("movq $19, %%rax \n\t"
        "movq %1, %%rbx \n\t"
        "movq %2, %%rcx \n\t"
        "movq %3, %%rdx \n\t"
        "int $0x80 \n\t"
        "movq %%rax, %0 \n\t":
    "=m"(ret):"m"(fd), "m"(offset), "m"(mode)
    );
    return ret;
}

FILE *fopen(const char *filename, const char *mode)
{
    f_size fd = -1;
    f_size flags = 0;
    f_size access = 00700; // 创建文件的权限

    // 来自于/usr/include/bits/fcntl.h
    // 注意：以0开始的数字是八进制的
#define O_RDONLY             00
#define O_WRONLY             01
#define O_RDWR               02
#define O_CREAT            0100
#define O_TRUNC           01000
#define O_APPEND          02000

    if (strcmp(mode, "w") == 0)
        flags |= O_WRONLY | O_CREAT | O_TRUNC;
    if (strcmp(mode, "w+") == 0)
        flags |= O_RDWR | O_CREAT | O_TRUNC;
    if (strcmp(mode, "r") == 0)
        flags |= O_RDONLY;
    if (strcmp(mode, "r+") == 0)
        flags |= O_RDWR | O_CREAT;

    fd = open(filename, flags, access);
    return (FILE *) fd;
}

f_size fread(void *buffer, f_size size, f_size count, FILE *stream)
{
    return read((f_size) stream, buffer, size * count);
}

f_size fwrite(const void *buffer, f_size size, f_size count, FILE *stream)
{
    return write((f_size) stream, buffer, size * count);
}

f_size fclose(FILE *fp)
{
    return close((f_size) fp);
}

f_size fseek(FILE *fp, f_size offset, f_size set)
{
    return seek((f_size) fp, offset, set);
}
