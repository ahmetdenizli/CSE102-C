/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/

#include <stdio.h>
#include <string.h>

/* This function reads file horizontally and founds head position of the string. */
int read_Hor(char text[][250], const char * str_name, int * position);

/* This function reads file vertically and founds head position of the string. */
int read_Ver(char text[][250], const char * str_name, int * position);

int main()
{
	FILE *fp;
	/* Declaring and initializing 5 constant strings	*/
	const char str1[10] = "Xanthos", str2[10] = "Patara", str3[10] = "Myra", str4[10] = "Arycanda", str5[10] = "Phaselis";
	char text[100][250]; /* Declaring character array for text.	*/

	int pos_str1, pos_str2, pos_str3, pos_str4, pos_str5, result= -1, i= 0; /* Declaring variables.	*/

	/* Opening the file for reading. If file cant open prints error and return -1 */
	fp = fopen("input.txt", "r");
	if(fp == NULL) {
		printf("Error opening file...\n");
		return(-1);
	}

	while(fgets(text[i], 250, fp) != NULL ){
		i++;
	}

	/* Searchs the given strings. Prints their head position and the orientation to the terminal. */
	/* If one of the strings is not found prints 'string was not found'. */
	result = read_Hor(text, str1, &pos_str1);
	if (result)
		printf("%s (%d,%d) Horizontal\n", str1, result, pos_str1);
	else{
		result = read_Ver(text, str1, &pos_str1);
		if (result)
			printf("%s (%d,%d) Vertical\n", str1, pos_str1, result);
		else
			printf("%s was not found\n", str1);
	}

	result = read_Hor(text, str2, &pos_str2);
	if (result)
		printf("%s (%d,%d) Horizontal\n", str2, result, pos_str2);
	else{
		result = read_Ver(text, str2, &pos_str2);
		if (result)
			printf("%s (%d,%d) Vertical\n", str2, pos_str2, result);
		else
			printf("%s was not found\n", str2);
	}

	result = read_Hor(text, str3, &pos_str3);
	if (result)
		printf("%s (%d,%d) Horizontal\n", str3, result, pos_str3);
	else{
		result = read_Ver(text, str3, &pos_str3);
		if (result)
			printf("%s (%d,%d) Vertical\n", str3, pos_str3, result);
		else
			printf("%s was not found\n", str3);
	}

	result = read_Hor(text, str4, &pos_str4);
	if (result)
		printf("%s (%d,%d) Horizontal\n", str4, result, pos_str4);
	else{
		result = read_Ver(text, str4, &pos_str4);
		if (result)
			printf("%s (%d,%d) Vertical\n", str4, pos_str4, result);
		else
			printf("%s was not found\n", str4);
	}

	result = read_Hor(text, str5, &pos_str5);
	if (result)
		printf("%s (%d,%d) Horizontal\n", str5, result, pos_str5);
	else{
		result = read_Ver(text, str5, &pos_str5);
		if (result)
			printf("%s (%d,%d) Vertical\n", str5, pos_str5, result);
		else
			printf("%s was not found\n", str5);
	}

	fclose(fp); /* Closing the file. */
	return 0;
}

/* This function reads file horizontally and founds head position of the string. */
int read_Hor(char text[][250], const char * str_name, int * position){
	char *ret; /* Declaring character pointer for position.	*/
	int i=0;

	/* Reads text for locate the given strings. If it finds return the row number */	
	while(text[i]){
		ret = strstr(text[i], str_name);
		if (ret){
			*position = ret - text[i] +1;
			return i+1;
		}
		i++;
		if (i == 100) /* Checks 'i' is the last row of text. If it is return 0.*/
			return 0;
	}

	return 0;
}

/* This function reads file vertically and founds head position of the string. */
int read_Ver(char text[][250], const char * str_name, int * position){
	int i, j, k=0;
	char text_1[250][100];
	char *ret; /* Declaring character pointer for position.	*/

	for (i = 0; i < 100; ++i)
	{
		for (j = 0; j<250; ++j)
		{
			if(text[i][j] != '\0' && text[i][j] != ' ')
				text_1[j][i]=text[i][j];
		}
	}

	/* Reads text for locate the given strings. If it finds return the column number */	
	while(text_1[k]){
		ret = strstr(text_1[k], str_name);
		if (ret){
			*position = ret - text_1[k] +1;
			return k+1;
		}
		k++;
		if (k == 250) /* Checks 'k' is the last column of text. If it is return 0.*/
			return 0;
	}

	return 0;
}