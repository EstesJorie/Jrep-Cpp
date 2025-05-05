#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <stdlib.h>

#define MAX_LINE 1024

void printHighlighted(const char *line, regmatch_t match)
{
    fwrite(line, 1, match.rm_so, stdout); //before match

    printf("\033[1;31m"); //red color
    fwrite(line + match.rm_so, 1, match.rm_eo - match.rm_so, stdout);
    printf("\033[0m"); //reset color

    fputs(line + match.rm_eo, stdout); //rest of line printed
}

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

    regex_t regex;
    int reti = regcomp(&regex, pattern, REG_ICASE | REG_EXTENDED); //compile pattern
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }
    
    char line[MAX_LINE];
    int lineNum = 0;
    while (fgets(line, sizeof(line), fp))
    {
        lineNum++;

        regmatch_t match;
        if (regexec(&regex, line, 1, &match, 0) == 0)
        {
            printf("%4d: ", lineNum); //show line num
            printHighlighted(line, match); //print match
        }
    }

    regfree(&regex); //frees memory from regex
    if(fp != stdin) fclose(fp);
    return 0;
}
