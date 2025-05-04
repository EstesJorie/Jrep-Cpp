To create:
> gcc -std=c11 -Wall -pedantic grep.c -o Jrep

To run/use:
> ./Jrep [word] [file]

>> ./Jrep world sample.txt

Using piping to search one file
>> *[cat sample.txt | ./Jrep banana]*
