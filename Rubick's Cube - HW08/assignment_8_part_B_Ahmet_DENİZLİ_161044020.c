/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define Struct for cubes faces. */
typedef struct _face{
	int size;
	int ** slices;
}FACE;

/* This function rotate rows right or left and rotate columns up or down.*/
void rotate( FACE _arr[], int face_num, char * str, int num, char * way, int shrnk_c);

int main(int argc, char const *argv[])
{
	int n, i, j, k, num1, num2, shrink_count =0;	/* Declaring necessary integers.*/
	FACE arr[6];									/* Declaring Face struct array for cube.*/
	char command[7], str1[8], str2[6]; 				/* Declaring strings for reading.*/
	FILE *f_commands, *f_result;					/* Declaring file pointers.*/

	/* Opening the file for reading. If file cant open prints error. */
	f_commands = fopen("commands.txt", "r");
	if(f_commands == NULL) {
		perror("commands.txt");
		return -1;
	}

	fscanf(f_commands, "%d", &n);	/* Getting cubes size from the file.*/

	/* Dynamic allocation for cube. */
	for ( k = 0; k < 6; ++k)
	{
		arr[k].size = n;
		arr[k].slices = (int **) malloc(n * sizeof(int *));
		for ( i = 0; i < n; ++i)
			arr[k].slices[i] = (int *) malloc(n * sizeof(int));
	}

	/* Dynamic allocation for cube. */
	for ( k = 0; k < 6; ++k)
		for ( i = 0; i < n; ++i)
			for ( j = 0; j < n; ++j)
				arr[k].slices[i][j] = k;

	/* Getting commands with loop. */
	do{
		fscanf(f_commands, "%s", command); /* Getting command that rotate or shrink from the file. */

		if( feof(f_commands) )
			break;

		if ( strcmp(command, "rotate") == 0)
		{
			fscanf(f_commands, "%d %s %d %s", &num1 , str1, &num2, str2);
			rotate(arr, num1, str1, num2, str2, shrink_count);
		}
		else if ( strcmp(command, "shrink") == 0) /* shrinks to a smaller cube. */
		{
			shrink_count++;
		}

	}while(1);


	/* Opening the file for writing. If file cant open prints error. */
	f_result = fopen("result.txt", "w");
	if(f_result == NULL) {
		perror("result.txt");
		return -1;
	}

	/* Writing Rubik’s cube to the result file. */
	for ( k = 0; k < 6; ++k){
		for ( i = (0 +shrink_count); i < n; ++i){
			for ( j = (0 +shrink_count); j < n; ++j){
				fprintf(f_result, "%d ", arr[k].slices[i][j] );
			}
			fprintf(f_result, "\n");
		}
		fprintf(f_result, "\n");
	}

	/* Freeing dynamic memories. */
	for ( k = 0; k < n; ++k)
	{
		for ( i = 0; i < n; ++i)
			free(arr[k].slices[i]);
		free(arr[k].slices);
	}

	fclose(f_commands); /* Closing the file. */
	fclose(f_result); /* Closing the file. */
	return 0;
}

/* This function rotate rows right or left and rotate columns up or down.*/
void rotate( FACE _arr[], int face_num, char * str, int num, char * way, int shrnk_c){
	int i, k, temp, size = (_arr[0].size - shrnk_c);

	/* Switch case for cubes faces numbers.*/
	switch (face_num){
		case 0:
			if (strcmp(str, "row") == 0)
			{
				if (strcmp(way, "right") == 0)
				{
					for ( k = 1; k < 4; ++k)
					{
						for (i = 0; i < size; ++i)
						{
							temp = _arr[k].slices[num +shrnk_c][i +shrnk_c];
							_arr[k].slices[num +shrnk_c][i +shrnk_c] = _arr[0].slices[num +shrnk_c][i +shrnk_c];
							_arr[0].slices[num +shrnk_c][i +shrnk_c] = temp;
						}
					}
				}
				else if (strcmp(way, "left") == 0)
				{
					for ( k = 3; k > 0; --k)
					{
						for (i = 0; i < size; ++i)
						{
							temp = _arr[k].slices[num +shrnk_c][i +shrnk_c];
							_arr[k].slices[num +shrnk_c][i +shrnk_c] = _arr[0].slices[num +shrnk_c][i +shrnk_c];
							_arr[0].slices[num +shrnk_c][i +shrnk_c] = temp;
						}
					}
				}
			}
			else if (strcmp(str, "column") == 0)
			{
				if (strcmp(way, "up") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[i +shrnk_c][num +shrnk_c];
						_arr[4].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[2].slices[i +shrnk_c][size -1 -num +shrnk_c];
						_arr[2].slices[i +shrnk_c][size -1 -num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[i +shrnk_c][num +shrnk_c];
						_arr[5].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}

				}
				else if (strcmp(way, "down") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[i +shrnk_c][num +shrnk_c];
						_arr[5].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[2].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[2].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[i +shrnk_c][num +shrnk_c];
						_arr[4].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
			}
			break;
		case 1:
			if (strcmp(str, "row") == 0)
			{
				if (strcmp(way, "right") == 0)
				{
					for ( k = 1; k < 4; ++k)
					{
						for (i = 0; i < size; ++i)
						{
							temp = _arr[k].slices[num +shrnk_c][i +shrnk_c];
							_arr[k].slices[num +shrnk_c][i +shrnk_c] = _arr[0].slices[num +shrnk_c][i +shrnk_c];
							_arr[0].slices[num +shrnk_c][i +shrnk_c] = temp;
						}
					}
				}
				else if (strcmp(way, "left") == 0)
				{
					for ( k = 3; k > 0; --k)
					{
						for (i = 0; i < size; ++i)
						{
							temp = _arr[k].slices[num +shrnk_c][i +shrnk_c];
							_arr[k].slices[num +shrnk_c][i +shrnk_c] = _arr[0].slices[num +shrnk_c][i +shrnk_c];
							_arr[0].slices[num +shrnk_c][i +shrnk_c] = temp;
						}
					}
				}
			}
			else if (strcmp(str, "column") == 0)
			{
				if (strcmp(way, "up") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[size -1 -num +shrnk_c][i +shrnk_c];
						_arr[4].slices[size -1 -num +shrnk_c][i +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[3].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[3].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[num +shrnk_c][size-1 -i +shrnk_c];
						_arr[5].slices[num +shrnk_c][size-1 -i +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
				else if (strcmp(way, "down") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[num +shrnk_c][size-1 -i +shrnk_c];
						_arr[5].slices[num +shrnk_c][size-1 -i +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[3].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[3].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[size -1 -num +shrnk_c][i +shrnk_c];
						_arr[4].slices[size -1 -num +shrnk_c][i +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
			}
			break;
		case 2:
			if (strcmp(str, "row") == 0)
			{
				if (strcmp(way, "right") == 0)
				{
					for ( k = 1; k < 4; ++k)
					{
						for (i = 0; i < size; ++i)
						{
							temp = _arr[k].slices[num +shrnk_c][i +shrnk_c];
							_arr[k].slices[num +shrnk_c][i +shrnk_c] = _arr[0].slices[num +shrnk_c][i +shrnk_c];
							_arr[0].slices[num +shrnk_c][i +shrnk_c] = temp;
						}
					}
				}
				else if (strcmp(way, "left") == 0)
				{
					for ( k = 3; k > 0; --k)
					{
						for (i = 0; i < size; ++i)
						{
							temp = _arr[k].slices[num +shrnk_c][i +shrnk_c];
							_arr[k].slices[num +shrnk_c][i +shrnk_c] = _arr[0].slices[num +shrnk_c][i +shrnk_c];
							_arr[0].slices[num +shrnk_c][i +shrnk_c] = temp;
						}
					}
				}
			}
			else if (strcmp(str, "column") == 0)
			{
				if (strcmp(way, "up") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c];
						_arr[4].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c] = _arr[2].slices[i +shrnk_c][num +shrnk_c];
						_arr[2].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[0].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c];
						_arr[0].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c] = _arr[2].slices[i +shrnk_c][num +shrnk_c];
						_arr[2].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c];
						_arr[5].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c] = _arr[2].slices[i +shrnk_c][num +shrnk_c];
						_arr[2].slices[i +shrnk_c][num +shrnk_c] = temp;
					}

				}
				else if (strcmp(way, "down") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c];
						_arr[5].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c] = _arr[2].slices[i +shrnk_c][num +shrnk_c];
						_arr[2].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[0].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c];
						_arr[0].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c] = _arr[2].slices[i +shrnk_c][num +shrnk_c];
						_arr[2].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c];
						_arr[4].slices[size-1 -i +shrnk_c][size-1 -num +shrnk_c] = _arr[2].slices[i +shrnk_c][num +shrnk_c];
						_arr[2].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
			}
			break;
		case 3:
			if (strcmp(str, "row") == 0)
			{
				if (strcmp(way, "right") == 0)
				{
					for ( k = 1; k < 4; ++k)
					{
						for (i = 0; i < size; ++i)
						{
							temp = _arr[k].slices[num +shrnk_c][i +shrnk_c];
							_arr[k].slices[num +shrnk_c][i +shrnk_c] = _arr[0].slices[num +shrnk_c][i +shrnk_c];
							_arr[0].slices[num +shrnk_c][i +shrnk_c] = temp;
						}
					}
				}
				else if (strcmp(way, "left") == 0)
				{
					for ( k = 3; k > 0; --k)
					{
						for (i = 0; i < size; ++i)
						{
							temp = _arr[k].slices[num +shrnk_c][i +shrnk_c];
							_arr[k].slices[num +shrnk_c][i +shrnk_c] = _arr[0].slices[num +shrnk_c][i +shrnk_c];
							_arr[0].slices[num +shrnk_c][i +shrnk_c] = temp;
						}
					}
				}
			}
			else if (strcmp(str, "column") == 0)
			{
				if (strcmp(way, "up") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[num +shrnk_c][size-1 -i +shrnk_c];
						_arr[4].slices[num +shrnk_c][size-1 -i +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[1].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[1].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[size-1 -num +shrnk_c][i +shrnk_c];
						_arr[5].slices[size-1 -num +shrnk_c][i +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}

				}
				else if (strcmp(way, "down") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[size-1 -num +shrnk_c][i +shrnk_c];
						_arr[5].slices[size-1 -num +shrnk_c][i +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[1].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[1].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[num +shrnk_c][size-1 -i +shrnk_c];
						_arr[4].slices[num +shrnk_c][size-1 -i +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
			}
			break;
		case 4:
			if (strcmp(str, "row") == 0)
			{
				if (strcmp(way, "right") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[num +shrnk_c][size-1 -i +shrnk_c];
						_arr[4].slices[num +shrnk_c][size-1 -i +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[1].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[1].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[size-1 -num +shrnk_c][i +shrnk_c];
						_arr[5].slices[size-1 -num +shrnk_c][i +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
				else if (strcmp(way, "left") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[size-1 -num +shrnk_c][i +shrnk_c];
						_arr[5].slices[size-1 -num +shrnk_c][i +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[1].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[1].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[num +shrnk_c][size-1 -i +shrnk_c];
						_arr[4].slices[num +shrnk_c][size-1 -i +shrnk_c] = _arr[3].slices[i +shrnk_c][num +shrnk_c];
						_arr[3].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
			}
			else if (strcmp(str, "column") == 0)
			{
				if (strcmp(way, "up") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[i +shrnk_c][num +shrnk_c];
						_arr[4].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[2].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[2].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[i +shrnk_c][num +shrnk_c];
						_arr[5].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}

				}
				else if (strcmp(way, "down") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[i +shrnk_c][num +shrnk_c];
						_arr[5].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[2].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[2].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[i +shrnk_c][num +shrnk_c];
						_arr[4].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
			}
			break;
		case 5:
			if (strcmp(str, "row") == 0)
			{
				if (strcmp(way, "right") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[size -1 -num +shrnk_c][i +shrnk_c];
						_arr[4].slices[size -1 -num +shrnk_c][i +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[3].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[3].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[num +shrnk_c][size-1 -i +shrnk_c];
						_arr[5].slices[num +shrnk_c][size-1 -i +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
				else if (strcmp(way, "left") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[num +shrnk_c][size-1 -i +shrnk_c];
						_arr[5].slices[num +shrnk_c][size-1 -i +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[3].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[3].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[size -1 -num +shrnk_c][i +shrnk_c];
						_arr[4].slices[size -1 -num +shrnk_c][i +shrnk_c] = _arr[1].slices[i +shrnk_c][num +shrnk_c];
						_arr[1].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
			}
			else if (strcmp(str, "column") == 0)
			{
				if (strcmp(way, "up") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[i +shrnk_c][num +shrnk_c];
						_arr[4].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[2].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[2].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[i +shrnk_c][num +shrnk_c];
						_arr[5].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}

				}
				else if (strcmp(way, "down") == 0)
				{
					for (i = 0; i < size; ++i)
					{
						temp = _arr[5].slices[i +shrnk_c][num +shrnk_c];
						_arr[5].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[2].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c];
						_arr[2].slices[size-1 -i +shrnk_c][size -1 -num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
					for (i = 0; i < size; ++i)
					{
						temp = _arr[4].slices[i +shrnk_c][num +shrnk_c];
						_arr[4].slices[i +shrnk_c][num +shrnk_c] = _arr[0].slices[i +shrnk_c][num +shrnk_c];
						_arr[0].slices[i +shrnk_c][num +shrnk_c] = temp;
					}
				}
			}
			break;
	}
}