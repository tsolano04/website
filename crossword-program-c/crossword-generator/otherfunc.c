#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "crossfunc.h"

int check_word(char *word)
{
	int ok = 0;
	//checks if word length is between 2 and 15
	if (strlen(word) < 2 || strlen(word) > 15)
	{
		printf("This word is invalid, too long or short.\n");
		return ok;
	}

	//checks if all letters are alphabetical
	for (int i = 0; i < strlen(word); i++)
	{
		if (!isalpha(word[i]))
		{
			printf("This word is invalid, non-alphabetical characters present\n");
			return ok;
		}
	}

	uppercase(word);
	ok = 1;

	return ok;
}

//convert all letters to uppercase
void uppercase(char* string)
{
	for (int i = 0; string[i]; i++)
	{
		string[i] = toupper(string[i]);
	}
	return;
}

//create board based on character inputted
void create_board(char thisboard[][word_length], char space)
{
	for (int i = 0; i < word_length; i++)
	{
		for (int j = 0; j < word_length; j++)
		{
			thisboard[i][j] = space;
		}
	}
	print_board(thisboard);
}

//print out the game board
void print_board(char board[][word_length])
{
	//initialize row separator
	int count = 0;
	printf(" ");

	//top border
	for (int i = 0; i < word_length; i++)
	{
		printf("-");
	}
	printf("\n");

	//side borders
	for (int i = 0; i < word_length; i++)
	{
		printf("|");
		for (int j = 0; j < word_length; j++)
		{
			count++;
			printf("%c", board[i][j]);
		}
		if (count > 10)
		{
			printf("|\n");
			count = 0;
		}
	}
	printf(" ");

	//bottom border
	for (int i = 0; i < word_length; i++)
	{
		printf("-");
	}
	printf("\n\n");
}

void sort_words(char sort_these[][word_length], int count)
{
	char temp[word_length];
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (strlen(sort_these[j]) < strlen(sort_these[j+1]))
			{
				strcpy(temp, sort_these[j+1]);
				strcpy(sort_these[j+1], sort_these[j]);
				strcpy(sort_these[j], temp);
			}
		}
	}

	return;
}
 
void make_clues(char scramble_array[][word_length], char new_arr[][word_length],int count)
{
	char thisword[word_length];
	srand(time(0));
	for (int i = 0; i < count; i++)
	{
		strcpy(thisword, scramble_array[i]);
		printf("Before: %s\n", thisword);
		int length = strlen(thisword);
		printf("%d\n", length);
		int rand_nums[length];
		for (int j = 0; j < length; j++)
		{
			int ind = rand() % length;
			printf("%d\n", ind);
			char temp = thisword[i];
			printf("%c\n", temp);
			thisword[i] = thisword[ind];
			thisword[ind] = temp;
			printf("%s\n", thisword);
		}
		printf("After: %s\n", thisword);
		strcpy(new_arr[i],thisword);
		printf("%s\n", new_arr[i]);
	}
}

void build_puzzle(char blank[][word_length], char solution[][word_length], char *word, int class[num_words], int numword, int letteris[][word_length])
{
	int intersections[word_length][word_length];
	//through the letters of the word
	int length = strlen(word);
	for (int i = 0; i < length; i++)
	{
		//across
		for (int across = 0; across < word_length; across++)
		{
			//down
			for (int down = 0; down < word_length; down++)
			{
				//sees if chars match
				if (word[i] == solution[across][down] && intersections[across][down] != 1)
				{
					//notate an intersection
					intersections[across][down] = 1;
					//if that letter is part of an across word
					if (letteris[across][down] == 0)
					{
						//check surrounding cells
						int ok = check_surroundings(solution, intersections, across, down, i, 0, length);
						if ((across >= i) && (word_length - across >= length - i) && ok == 1)
						{
							for (int place = 0; place < length; place++)
							{
								solution[across - i][down] = word[place];
								blank[across - i][down] = ' ';
								letteris[across - i][down] = 1;
								i--;
							}
							class[numword] = 1;
							return;
						}
					}
					//if the letter is part of a down word
					else if (letteris[across][down] == 1)
					{
						//check surrounding cells
						int ok = check_surroundings(solution, intersections, across, down, 0, i, length);
						if ((down >= i) && (word_length - down >= length - i))
						{
							for (int place = 0; place < length; place++)
							{
								solution[across][down - i] = word[place];
								blank[across][down - i] = ' ';
								letteris[across][down - i];
								i--;
							}
							class[numword] = 0;
							return;
						}
					}
				}
			}
		}
	}
}

int check_surroundings(char solution[][word_length], int intersections[][word_length], int across, int down, int across_index, int down_index, int length)
{
	printf("ACROSS INDEX: %d  DOWN INDEX: %d\n", across_index, down_index);
	int ok = 1;
	for (int j = 0; j < length; j++)
	{
		if (across_index != 0)
		{
			printf("CHECKING ACROSS\n");
			if ((solution[across - across_index][down - 1] != '.' || solution[across_index][down + 1] != '.'))
			{
				printf("NEXT TO DOWN\n");
				ok = 0;
				return ok;
			}
			across_index--;
		}
		else if (down_index != 0)
		{
			printf("CHECKING DOWN\n");
			if ((solution[across - 1][down - down_index] != '.' || solution[across + 1][down - down_index] != '.'))
			{
				printf("NEXT TO ACROSS\n");
				ok = 0;
				return ok;
			}
			down_index--;
		}
	}
	return ok;
}

