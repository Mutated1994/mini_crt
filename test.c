#include "minicrt.h"

// ./test arg1 arg2
int main(int argc, char *argv[])
{
    int i;
    FILE *fp;

    char **v = malloc(argc * sizeof(char *));
    for (i = 0; i < argc; ++i)
    {
        v[i] = malloc(strlen(argv[i]) + 1);
        strcpy(v[i], argv[i]);
    }

    // stdout
    for (i = 0; i < argc; ++i)
    {
        fwrite(v[i], 1, strlen(v[i]), stdout);
        fwrite("\n", 1, sizeof(char), stdout);
    }

    // Writes a string to the file
    fp = fopen("test.txt", "w");
    long lens[argc];
    for (i = 0; i < argc; ++i)
    {
        lens[i] = strlen(v[i]);
        fwrite(v[i], 1, lens[i], fp);
    }
    fclose(fp);

    // Reads the content of the file
    fp = fopen("test.txt", "r");
    for (i = 0; i < argc; ++i)
    {
        long len = lens[i];
        char *buf;
        buf = malloc(len + 1);
        fread(buf, 1, len, fp);
        buf[len] = '\0';
        printf("%d %s\n", len, buf);
        free(buf);
        free(v[i]);
    }
    fclose(fp);

    return 0;
}