/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/

#include <stdio.h>

/* This function reads file and finds all bi-grams in the file.*/
int readFile(char * fileName, int arr[][27] );

/* This function evaluates the dissimilarity scores of language pairs.*/
void dissimilarity(int arr1[][27], int arr2[][27]);

int main()
{
	/* Declaring integer arrays for languages bi-grams. */
	int lang1[27][27]= {0}, lang2[27][27]= {0}, lang3[27][27]= {0}, 
		lang4[27][27]= {0}, lang5[27][27]= {0}, langX[27][27]= {0};

	/* Reading files and finds all bi-grams in the files.*/
	readFile("language_1.txt", lang1 );
	readFile("language_2.txt", lang2 );
	readFile("language_3.txt", lang3 );
	readFile("language_4.txt", lang4 );
	readFile("language_5.txt", lang5 );
	readFile("language_x.txt", langX );

	dissimilarity(langX, lang1);
	dissimilarity(langX, lang2);
	dissimilarity(langX, lang3);
	dissimilarity(langX, lang4);
	dissimilarity(langX, lang5);

	return 0;
}

/* This function reads file and finds all bi-grams in the file.*/
int readFile(char * fileName, int arr[][27] ){
	FILE *fp;
	int c1, c2; /* Declaring integer variables for characters. */

	/* Opening the file for reading. If file cant open prints error. */
	fp = fopen(fileName, "r");
	if(fp == NULL) {
		perror(fileName);
		return -1;
	}

	/* Getting first character of the file. */
	c1=fgetc(fp);
	if (c1<97 || c1>122)
		c1=123;

	do{
		c2=fgetc(fp); /* Getting other characters of the file. */
		if( feof(fp) ){
			if( c1!=123 )
				++arr[c1-97][26];
			break;
		}

		if (c2<97 || c2>122) /* If character is whitespace then 123 assign to c2. */
			c2=123;

		if (c1==123 && c2==123) /* If there is two adjacent whitespace skips following statements. */
			continue;

		++arr[c1-97][c2-97]; /* Increase the bi-gram read. */

		c1=c2;	/* assign c2 to c1. */
	}while(1);

	fclose(fp); /* Closing the file. */
	return 0;
}

/* This function evaluates the dissimilarity scores of language pairs.*/
void dissimilarity(int arr1[][27], int arr2[][27]){
	int i, j; /* Declaring integer variables for loops.	*/
	double totalbigrams_1= 0.0, totalbigrams_2= 0.0, dissimilarity_ =0.0, frequency_diff;

	for (i = 0; i < 27; ++i)
	{
		for ( j = 0; j < 27; ++j)
		{
			totalbigrams_1 += arr1[i][j]; /* Counting total number of all bi-grams in 1st language.*/
			totalbigrams_2 += arr2[i][j]; /* Counting total number of all bi-grams in other language.*/
		}
	}
	for (i = 0; i < 27; ++i)
	{
		for ( j = 0; j < 27; ++j)
		{
			/* Calculating the frequency difference of a particular bi-gram.*/
			frequency_diff = (arr1[i][j] / totalbigrams_1) - (arr2[i][j] / totalbigrams_2);
			if (frequency_diff > 0)
				dissimilarity_ += frequency_diff; /* Dissimilarity calculating.*/
			else
				dissimilarity_ -= frequency_diff; /* Dissimilarity calculating.*/
		}
	}

	printf("%lf\n", dissimilarity_); 	/* Printing the dissimilarity values.*/
}