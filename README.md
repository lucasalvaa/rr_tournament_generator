# Round-robin tournament schedule generator

## What is a round-robin tournament?

A **[round-robin tournament](https://en.wikipedia.org/wiki/Round-robin_tournament)** is a competition format in which each contestant meets every other participant, usually in turn.
In a **single round-robin** schedule, each participant plays every other participant once.
If each participant plays all others twice, this is frequently called a **double round-robin**.
In sports with a large number of competitive matches per season, double round-robins are common.
Most association football leagues in the world are organized on a double round-robin basis, in which every team plays all others in its league once at home and once away.

### Which sports competitions use the round-robin format?
This format is used in almost every football league, for example the british **Premier League**, the italian **Serie A**, the german **Bundesliga** and the spanish **LaLiga**.

### Round-robin tournament scheduling algorithm
Given a number of competitors equal to n:
- If n is even, there will be n-1 matchdays, each one with n/2 matches
- If n is odd, there will be n matchdays, each one with (n-1)/2 matches and a team that rests in turn.
There are several scheduling algorithms for round-robin tournaments. This program uses the **[circle method](https://en.wikipedia.org/wiki/Round-robin_tournament#Circle_method)**

## About this project

This program is written in C language.

### How to properly execute the program 
Once all the files have been compiled, to run the program you need to launch the following command in your terminal:
`./[executable name] "[tournament name]" [number of competitors]`
If \[tournament name\] and \[number of competitors\] are not specified, the program assings default name and number of competitors to the tournament. 

### How to compile quickly and correctyle
A _makefile_ file is available in the repository. To compile quickly and correctly, just type `make` in your terminal.
Object files (marked with the .o extension) can be removed after the compilation typing `make clean` in your terminal.
Before executing these commands, make sure the _makefile_ is in the same directory of the source code.

### Program limits
- At the moment, this program allows to generate a single round-robin schedule.
- At the moment, teams can't be represented by names, but only by numbers.
- At the moment, the generated schedule is not saved to a file.
