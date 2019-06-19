/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/

#include <stdio.h>

/* global variable declaration for recursive function.*/
int level = 0, i;

/* This function prints the visualization of the newick tree to stdout with recursion.*/
void recPrint(char * str);

int main()
{
	FILE *fp;
	char line[200];	/* Declaring character array for line.*/

	/* Opening the file for reading. If file cant open prints error. */
	fp = fopen("input.txt", "r");
	if(fp == NULL) {
		perror("input.txt");
		return -1;
	}

	fgets(line, 200, fp); /* Reading a line from the file. */

	recPrint(line);	/* Printing the visualization of the newick tree to stdout with recursion.*/

	fclose(fp); /* Closing the file. */
	return 0;
}

/* This function prints the visualization of the newick tree to stdout with recursion.*/
void recPrint(char * str){
	if ( str[0]== '\n' )	/* Controls whether the string is finished.*/
	{
		return;
	}
	else if ( str[0]== '(' ) /* If char is '(' level is increased by one, then look next character*/
	{
		++level;
		recPrint(str+1);
	}
	else if ( str[0]== ')' ) /* If char is ')' level is decreased by one, then look next character.*/
	{
		if(level > 0)
			--level;
		recPrint(str+1);
	}
	else if ( str[0]== ',' ) /* If char is ',' look next character.*/
	{
		recPrint(str+1);
	}
	else	/* Printing branches and nodes, then look next character.*/
	{
		for (i = 0; i < level; ++i)
		{
			printf("-");
		}
		printf("%c\n", str[0]);
		recPrint(str+1);
	}
	return;
}