/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/

#include <stdio.h>
#include <string.h>

/* This function finds the result of polynomial for each value.*/
double findResult(char _polynomial[1000], double value);

int main()
{
	FILE *fval, *fpol, *fout;
	char polynomial[1000]; /* Declaring character array for polynomial.	*/
	double values[100], result=0.0; /* Declaring double array for values.	*/
	int i=0, k=0;

	/* Opening the file for writing. If file cant open prints error and return -1 */
	fout = fopen("evaluations.txt", "w");
	if(fval == NULL) {
		printf("Error opening file...\n");
		return(-1);
	}

	/* Opening the values file for reading. If file cant open prints error and return -1 */
	fval = fopen("values.txt", "r");
	if(fval == NULL) {
		printf("Error opening file...\n");
		return(-1);
	}
	while(!feof(fval) ){
		fscanf(fval, "%lf", &values[i]);
		i++;
	}
	i--;

	/* Opening the polynomial file for reading. If file cant open prints error and return -1 */
	fpol = fopen("polynomial.txt", "r");
	if(fpol == NULL) {
		printf("Error opening file...\n");
		return(-1);
	}
	fgets(polynomial, 1000, fpol);

	/* Writing the result of polynomial for each value to the "evaluations.txt" .*/
	while(k<i){
		result = findResult(polynomial, values[k]);

		fprintf(fout, "%.2lf\n", result);
		k++;
	}


	fclose(fpol); /* Closing the file. */
	fclose(fval); /* Closing the file. */
	fclose(fout); /* Closing the file. */
	return 0;
}

/* This function finds the result of polynomial for each value.*/
double findResult(char _polynomial[1000], double value){

	char dest[1000]; /* Declaring temp character array for polynomial.	*/
	const char str2[] = "+-"; /* Declaring const character array for search.*/
	const char str3[] = "x";
	char * ret, temp1, temp2, temp3='+';
	double coefficient, result=0.0, valuePow=1.0;
	int power, n, i;

	strcpy(dest, _polynomial); /* Copying by _polynomial to dest.*/
	ret = strpbrk(dest, str2); /* Finding the first '+' or '-' character in the dest */

	/* Checking which mark started with.*/
	if ( *_polynomial == '-' ){
		temp3 = '-';
		strcpy(dest, ret+1);
		ret = strpbrk(dest, str2);
	}
	else if( *_polynomial == '+' ){
		strcpy(dest, ret+1);
		ret = strpbrk(dest, str2);
	}

	n = sscanf( dest, "%lf %c %c %d", &coefficient, &temp1, &temp2, &power );
	if(n==0){
		coefficient=1;
		n = sscanf( dest, "%c %c %d", &temp1, &temp2, &power );
		if(n==1) power=1;
		else if(n==2){
			ret = strstr(dest, str3);
			strcpy(dest, ret);
			n = sscanf( dest, "%c %c %d", &temp1, &temp2, &power );
			if(n==1) power=1;
		}
	}
	if (temp2 == '+' || temp2 == '-')
		power=1;

	for (i = 0; i < power; ++i)
		valuePow *= value;

	if ( temp3 == '-' )
		result -= coefficient * valuePow; /* insertion of the monomial value.*/
	else
		result += coefficient * valuePow; /* insertion of the monomial value.*/

	while( ret != NULL ) {
		valuePow = 1.0; /* Reseting the valuePow.*/
		temp3 = *ret;
		strcpy(dest, ret+1); /* Copying by point (ret+1) to dest.*/

		n = sscanf( dest, "%lf %c %c %d", &coefficient, &temp1, &temp2, &power );
		if(n==0){
			coefficient=1;
			n = sscanf( dest, "%c %c %d", &temp1, &temp2, &power );
			if(n==1) power=1;
			else if(n==2){
				ret = strstr(dest, str3);
				strcpy(dest, ret);
				n = sscanf( dest, "%c %c %d", &temp1, &temp2, &power );
				if(n==1) power=1;
			}
		}
		if (temp2 == '+' || temp2 == '-')
			power=1;

		for (i = 0; i < power; ++i)
			valuePow *= value;

		if ( temp3 == '+' )
			result += coefficient * valuePow; /* insertion of the monomial value.*/
		else
			result -= coefficient * valuePow; /* insertion of the monomial value.*/

		ret = strpbrk(dest, str2); /* Finding the '+' or '-' character in the dest */
	}

	return result;
}