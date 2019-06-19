/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/

#include <stdio.h>

void playGame();

int main(){
	int result= -1234;
	do{
		playGame();
		printf("İf you want play again enter '1' :\n");
		scanf("%d", &result);
	}while(result);

	return 0;
}

/*This function launches and checks status of the game. */
void playGame(){
	/*Declaring and initializing variables 						*/
	/*Define area of the board, number of attempts, marked area	*/
	int num_of_attemps= 10, board_x= 100, board_y= 150; 
	float x, y, detector_x= 20.0, detector_y= 40.0, marked_x= 10.0, marked_y= 20.0, 
		  marked_left_x= 30.0, marked_right_x= 40.0, marked_bottom_y= 30.0, marked_top_y= 50.0, left_x, right_x, bottom_y, top_y;

	printf("Board = [100 x 150], marked region = [10 x 20], Detector = [20 x 40], The smallest coordinate [0.0]\n");
	printf("You have 10 attempts.\n");
	/*Using while loop for taking inputs and continuing the game*/
	while (num_of_attemps > 0)
	{
		/*Takes center coordinates of the shape from player.*/
		printf("Enter the x coordinate of the move:\n");
		scanf("%f", &x);
		printf("Enter the y coordinate of the move:\n");
		scanf("%f", &y);
		/*Define corners of the detector area*/
		left_x= (x - detector_x/2.0);
		right_x= (x + detector_x/2.0);
		bottom_y= (y - detector_y/2.0);
		top_y= (y + detector_y/2.0);

		--num_of_attemps;	/*Attempts decreases 1 */

		/*Controls whether the movement is within the limits of the board */
		if ( x<10 || x>board_x || y<20 || y>board_y )
		{
			++num_of_attemps;	/*Attempts increase 1 */
			printf("Error, move is not valid. Try again. Attempts remaining: %d.\n", num_of_attemps);
		}
		/*Controls whether detector fully overlaps with the marked region  */
		else if ( (left_x <= marked_left_x) && (marked_right_x <= right_x) && (bottom_y <= marked_bottom_y) && (marked_top_y <= top_y) ){
			printf("Direct Hit! Congratulations! You win the game.\n");
			num_of_attemps= -1;	/*Attempts assigned -1 for exit from while loop */
		}
		/*Controls whether detector partially overlaps with the marked region */
		else if ( ((left_x< marked_left_x && marked_left_x< right_x) || (left_x< marked_right_x && marked_right_x< right_x)) && 
				  ((bottom_y< marked_bottom_y && marked_bottom_y< top_y) || (bottom_y< marked_top_y && marked_bottom_y< top_y)) )
		{
			if (left_x< marked_left_x && marked_left_x< right_x && marked_right_x>right_x)
				marked_right_x= right_x;
			else if (left_x< marked_right_x && marked_right_x< right_x && marked_left_x< left_x)
				marked_left_x= left_x;

			if (bottom_y< marked_bottom_y && marked_bottom_y< top_y && marked_top_y> top_y)
				marked_top_y= top_y;
			else if (bottom_y< marked_top_y && marked_bottom_y< top_y && marked_bottom_y< bottom_y)
				marked_bottom_y= bottom_y;
			/*Marked region is updated to the intersected area. */
			marked_x= marked_right_x - marked_left_x;
			marked_y= marked_top_y - marked_bottom_y;
			/*Detector width and height are also decreased to half of their value for the next iteration.*/
			detector_x /= 2;
			detector_y /= 2;
			printf("Partial hit! marked region was shirked to [%.2f x %.2f], detector was shirked to [%.2f x %.2f], attempts remaining: %d.\n", marked_x, marked_y, detector_x, detector_y, num_of_attemps);
		}
		else {
			printf("You missed the target! Try again, attempts remaining: %d.\n", num_of_attemps);
		}
	}
	/*Controls whether attempts is over */
	if (num_of_attemps == 0){
		printf("Game over! You lost the game. Thank you for playing.\n");
	}
}