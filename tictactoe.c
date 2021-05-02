#include <stdio.h>
#include <stdlib.h>

char board[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
void print_board(){

	for(int i = 0 ; i < 9 ; i ++){
		if(i == 0 || i % 3 == 0){
			//start of row
			printf("| ");
		}
		printf("%c | ", board[i]);
		if(i == 2 || i == 5 || i == 8){
			//end of row
			printf("\n");
		}		
	}	
	printf("\n");
}

int check_state(){
	//check horizontal
	for(int i = 0; i < 9; i += 3){
		if(board[i] == board[i+1] && board[i+1] == board[i+2]){
			return 1;
		}
	}
	//check vertical
	for(int i = 0; i < 9; i++){
		if(board[i] == board[i+3] && board[i+3] == board[i+6]){
			return 1;
		}
	}
	//check diagonal
	char middle = board[4];
	if(board[4] > 47 || board[4] < 58){
		//middle is empty, no need to check
		return 0;
	} else {
		if(board[4] == board[0] && board[4] == board[8]){
			return 1;
		} 
		if(board[4] == board[2] && board[4] == board[6]){
			return 1;
		}
	}
	return -100;
}

int place_move(int spot, char token){
	if(board[spot] > 47 && board[spot] < 58){
		//empty
		board[spot] = token;
		
		//check if winning move
		int player_won = check_state();		
		if(player_won){
			print_board();
			printf("%c won!\n", token);
			return 100;		
		}
		return 0;
	} else {
		//spot already has a token
		return -1;
	}
}

void start_game(char player){
	int game_continue = 1;
	int  move = -1;
	char computer = '?';
	if(player == 'o'){
		computer = 'x';
	} else {
		computer = 'o';	
	}
	while(game_continue){
		print_board();	
		printf("Choose move (0-8):\n");
		scanf("%d", &move);
		if(move > -1 && move < 9){
			int state  = place_move(move, player);
			if(state == -1){
				printf("Slot taken, choose again\n");
			}
			if(state = 100){
				game_continue = 0;
			}
			int computer_move = 1;
			while(computer_move){
				for(int i = 0 ; i < 9 ; i ++){
						computer_move = place_move(i, computer);				    if(computer_move != -1){
						break;
					}
				}
				if(computer_move == 100){
					//computer won
					game_continue = 0;
					computer_move = 0;	
				}
			}
		} else {
			printf("Choose from 0 - 8 please.\n");
		}
	}

}
int main(int argc, char** argv){
	printf("Welcome! Please choose a token (x or o):\n");
	char token;
	scanf("%c", &token);
	if(token == 'x'){
		start_game('x');		
	} else if (token == 'o'){
		start_game('o');
	} else {
		printf("Please enter 'x' or 'o'. Try Again?\n");
	}
	return 0;
}
