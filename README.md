To create:

> g++ -std=c++11 -Wall -pedantic grep.cpp -o Jrep


To run/use:
> ./Jrep [word] [file]

> ./Jrep world sample.txt

Using piping to search one file
>> *[cat sample.txt | ./Jrep banana]*

Regex Matching Examples
>>  ./Jrep '[A-Z]{3}' sample.txt
>>  ./Jrep '^start' sample.txt
>>  ./Jrep t.st sample .txt
