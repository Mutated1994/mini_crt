//
// Created by Lance on 2020/8/19.
//

#ifndef MINICRT_MINICRT_H
#define MINICRT_MINICRT_H

// malloc
#ifndef NULL
#define NULL (0)
#endif

void free(void *ptr);

void *malloc(unsigned size);

static int brk(void *end_data_segment);

int mini_crt_init_heap();

// 字符串
char *itoa(int n, char *str, int radix);

int strcmp(const char *src, const char *dst);

char *strcpy(char *dest, const char *src);

unsigned strlen(const char *str);

// 文件IO
typedef long f_size;
typedef unsigned long u_f_size;
typedef long FILE;

#define EOF (-1)

#define stdin   ((FILE*)0)
#define stdout  ((FILE*)1)
#define stderr  ((FILE*)2)

int mini_crt_init_io();

FILE *fopen(const char *filename, const char *mode);

f_size fread(void *buffer, f_size size, f_size count, FILE *stream);

f_size fwrite(const void *buffer, f_size size, f_size count, FILE *stream);

f_size fclose(FILE *fp);

f_size fseek(FILE *fp, f_size offset, f_size set);

// printf
long fputc(char c, FILE *stream);

long fputs(const char *str, FILE *stream);

long printf(const char *format, ...);

long fprintf(FILE *stream, const char *format, ...);

// internal
void do_global_ctors();
void mini_crt_call_exit_routine();

// internal
void do_global_ctors();
void mini_crt_call_exit_routine();

#endif //MINICRT_MINICRT_H
