//Thomas Solano
//Fund Comp
//Lab8
//crossword.c

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "crossfunc.h"

int main(int argc, char *argv[])
{
	//VARIABLES
	char tobesorted[num_words][word_length];
	char scrambled_words[num_words][word_length];
	char blank_board[word_length][word_length];
	char solution_board[word_length][word_length];

	//will determine either across or down
	//0 is across, 1 is down
	int word_class[num_words];
	int count = 0;

	//NO FILES ENTERED
	if (argc == 1)
	{
		printf("Enter a list of words:\n");
		while (1)
		{
			char someword[word_length];
			//puts words into word array until . is entered
			scanf("%s", someword);
			if (!strcmp(someword,"."))
			{
				break;
			}
			if (check_word(someword) == 1)
			{
				strcpy(tobesorted[count],someword);
			}
			count++;			
		}
	}
	//IF A FILE IS ENTERED
	else if (argc < 4)
	{
		FILE *fp = fopen(argv[1], "r");
		if (fp == NULL)
		{
			printf("Can't open the %s file.\n", argv[1]);
			return 1;
		}
		while(!feof(fp))
		{
			char someword[word_length];
			fscanf(fp, "%s", someword);
			if (!strcmp(someword,"."))
			{
				break;
			}
			if (check_word(someword) == 1)
			{
				strcpy(tobesorted[count], someword);
			}
			count++;
		}
	}
	//too many arguments entered
	else
	{
		printf("Too many arguments.\n");
		return 1;
	}

	//CREATE PUZZLES
	create_board(solution_board, '.');
	create_board(blank_board, '#');

//BUILD PUZZLE

	//SORT CLUES
	sort_words(tobesorted, count);
	make_clues(tobesorted, scrambled_words, count);

	//print longest word in middle of the grid
	int edge = floor((word_length - strlen(tobesorted[0])) / 2);
	char thisword[word_length];
	int letteris[word_length][word_length];
	int word_across[num_words];
	int word_down[num_words];
        strcpy(thisword, tobesorted[0]);
	for (int i = 0; i < strlen(tobesorted[0]); i++)
	{
		solution_board[7][i + edge] = thisword[i];
		blank_board[7][i + edge] = ' ';
		letteris[7][i + edge] = 0;
	}
	word_across[0] = 7 + 1;
	word_down[0] = edge + 1;
	word_class[0] = 0;

	//place rest of words
	for (int i = 1; i < count; i++)
	{
		build_puzzle(blank_board, solution_board, tobesorted[i], word_class, i, letteris, word_across, word_down);
	}

	//keep going until as many can be placed as possible
	int numtimes2 = 0;
	while(1)
	{
		int numtimes1 = 0;
		for (int i = 1; i < count; i++)
		{
			if (word_class[i] == 2)
			{
			numtimes1++;
			build_puzzle(blank_board, solution_board, tobesorted[i], word_class, i, letteris, word_across, word_down);
			}
		}
		if (numtimes1 == numtimes2)
		{
			break;
		}
		numtimes2 = numtimes1;
	}


	//MAKE CLUES
	make_clues(tobesorted, scrambled_words, count);

	//EXPORT PUZZLE TO A FILE
	if (argc == 3)
	{
		//get name of file
		char newfile[20];
		strcpy(newfile, argv[2]);

		//create editable file
		FILE *fnew;
		fnew = fopen(newfile, "w");

		//prints everything into new file
		fprintf(fnew, "Anagram Crossword Puzzle Generator\n");
		fprintf(fnew, "----------------------------------\n\n");

		fprintf(fnew, "SOLUTION:\n");
		fprint_board(solution_board, fnew);
		fprintf(fnew, "PUZZLE:\n");
		fprint_board(blank_board, fnew);
		fprintf(fnew, "CLUES:\n");
		fprintf(fnew, " Location | Direction | Anagram\n");
		for (int i = 0; i < count; i++)
		{
			if (word_class[i] == 1 || word_class[i] == 0)
			{
				fprintf(fnew, " %2d,%-8d", word_across[i], word_down[i]);
				if(word_class[i] == 0)
				{
					fprintf(fnew, "%-12s", "ACROSS");
				}
				else if(word_class[i] == 1)
				{
					fprintf(fnew, "%-12s", "DOWN");
				}
				fprintf(fnew, "%-15s\n", scrambled_words[i]);
			}
		}
		return 0;
	}


	printf("Anagram Crossword Puzzle Generator\n");
	printf("----------------------------------\n\n");

	//PRINT THE PUZZLES
	printf("SOLUTION:\n");
	print_board(solution_board);
	printf("PUZZLE:\n");
	print_board(blank_board);

	//PRINT CLUES
	printf("CLUES:\n");
	printf(" Location | Direction | Anagram\n");
	for (int i = 0; i < count; i++)
	{
		if (word_class[i] == 1 || word_class[i] == 0)
		{
			printf(" %2d,%-8d", word_across[i], word_down[i]);
			if(word_class[i] == 0)
			{
				printf("%-12s", "ACROSS");
			}
			else if(word_class[i] == 1)
			{
				printf("%-12s", "DOWN");
			}
			printf("%-15s\n", scrambled_words[i]);
		}
	}


	return 0;
}

