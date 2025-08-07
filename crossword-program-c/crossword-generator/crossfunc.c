//Thomas Solano
//Fund Comp
//Lab8
//crossfunc.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "crossfunc.h"

//makes sure word is valid
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

void fprint_board(char board[][word_length], FILE *fp)
{
	//initialize row separator
	int count = 0;
	fprintf(fp, " ");

	//top border
	for (int i = 0; i < word_length; i++)
	{
		fprintf(fp, "-");
	}
	fprintf(fp, "\n");

	//side borders
	for (int i = 0; i < word_length; i++)
	{
		fprintf(fp, "|");
		for (int j = 0; j < word_length; j++)
		{
			count++;
			fprintf(fp, "%c", board[i][j]);
		}
		if (count > 10)
		{
			fprintf(fp, "|\n");
			count = 0;
		}
	}
	fprintf(fp, " ");

	//bottom border
	for (int i = 0; i < word_length; i++)
	{
		fprintf(fp, "-");
	}
	fprintf(fp, "\n\n");
}


//Sorts words longest to smallest
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

//Scrambles letters in the words to make clues
void make_clues(char scramble_array[][word_length], char new_arr[][word_length],int count)
{
	//make temporary string var
	char thisword[word_length];
	//randomize srand
	srand(time(0));
	//iterate through all words
	for (int i = 0; i < count; i++)
	{
		strcpy(thisword, scramble_array[i]);
		int length = strlen(thisword);
		//iterate through letters of word
		for (int j = 0; j < length; j++)
		{
			//goes through each letter and replaces with another letter (by random) in that word
			int ind = rand() % length;
			char temp = thisword[j];
			thisword[j] = thisword[ind];
			thisword[ind] = temp;
		}
		strcpy(new_arr[i],thisword);
	}
}

//Builds the board
void build_puzzle(char blank[][word_length], char solution[][word_length], char *word, int class[num_words], int numword, int letteris[][word_length], int acoords[num_words], int dcoords[num_words])
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
					//if that letter is part of an across word
					if (letteris[across][down] == 0)
					{
						//check surrounding cells
						int ok = check_across(solution, across, down, i, length, word[i]);
						if ((across >= i) && (word_length - across >= length - i) && ok == 1)
						{
							//notate an intersection
							intersections[across][down] = 1;
							//notates across and down coordinates
							acoords[numword] = across - i + 1;
							dcoords[numword] = down + 1;
							//replace . in solution board with letters in the word, and # with blank spaces in blank board
							for (int place = 0; place < length; place++)
							{
								solution[across - i][down] = word[place];
								blank[across - i][down] = ' ';
								letteris[across - i][down] = 1;
								i--;
							}
							//notates the word is across
							class[numword] = 1;
							return;
						}
					}
					//if the letter is part of a down word
					else if (letteris[across][down] == 1)
					{
						//check surrounding cells
						int ok = check_down(solution, across, down, i, length, word[i]);
						if ((down >= i) && (word_length - down >= length - i) && ok == 1)
						{
							intersections[across][down] = 1;
							//notates across and down coordinates
							acoords[numword] = across + 1;
							dcoords[numword] = down - i + 1;
							//replace . in solution board with letters in the word, and # with blank spaces in blank board
							for (int place = 0; place < length; place++)
							{
								solution[across][down - i] = word[place];
								blank[across][down - i] = ' ';
								letteris[across][down - i] = 0;
								i--;
							}
							//notates the word is down
							class[numword] = 0;
							return;
						}
					}
				}
			}
		}
	}
	//makes word 'invalid' and displays that word could not be placed
	printf("Could not place %s.\n\n", word);
	class[numword] = 2;
}

//checks surrounding cells to make sure word can be placed across
//will return 1 if word can be placed, and 0 if it cannot
int check_across(char solution[][word_length], int across, int down, int across_index, int length, char letter)
{
	int ok = 1;
	//checks caps
	if (solution[across - across_index - 1][down] != '.' || solution[across - across_index + length][down] != '.')
	{
		ok = 0;
		return ok;
	}
	//checks spaces adjacent to where the letters would go
	for (int j = 0; j < length; j++)
	{
		if ((solution[across - across_index][down - 1] != '.' || solution[across - across_index][down + 1] != '.') && (solution[across - across_index][down] == '.' || solution[across - across_index][down] != letter))
		{
			ok = 0;
			return ok;
		}
		across_index--;	
	}
	return ok;
}

//checks surrounding cells to make sure word can be placed dowr
int check_down(char solution[][word_length], int across, int down, int down_index, int length, char letter)
{
	int ok = 1;
	//check caps 
	if (solution[across][down - down_index - 1] != '.' || solution[across][down - down_index + length] != '.')
	{
		ok = 0;
		return ok;
	}
	//checks sides of words
	for (int j = 0; j < length; j++)
	{
		if ((solution[across - 1][down - down_index] != '.' || solution[across + 1][down - down_index] != '.') && (solution[across][down - down_index] == '.' || solution[across][down - down_index] != letter))
		{
			ok = 0;
			return ok;
		}
		down_index--;
	}
	return ok;
}



