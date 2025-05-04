#include <stdio.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) //argc = typed words, *argv = place of words
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s pattern [file]\n", argv[0]);
        return 1; // user doesn't search
    }

    char *pattern = argv[1]; //word looking for
    FILE *fp = (argc > 2) ? fopen(argv[2], "r") : stdin; //if file is provided read this, else read input
     
    if (!fp)
    {
        perror("fopen");
        return 1; //error opening
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp))
    {
        if(strstr(line, pattern))
        {
            fputs(line, stdout); //print line where word is contained
        }
    }
    if(fp != stdin) fclose(fp);
    return 0;
}