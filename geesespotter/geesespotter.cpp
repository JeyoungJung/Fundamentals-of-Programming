#include "geesespotter_lib.h"


char * createBoard(std::size_t xdim, std::size_t ydim){
	char * new_board = new char[xdim*ydim]{'\0'};
	return new_board;
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
	for(unsigned int i{0}; i < xdim*ydim; i++){
		if(board[i] == 9){
			if(((i-1) >= 0) && ((i % xdim) != 0) && board[i-1] != 9){
				board[i-1]++;
			}
			if((i+1 <= xdim*ydim) && (((i+1) % xdim) != 0 && board[i+1] != 9)){
				board[i+1]++;
			}
			if(i-xdim >= 0 && board[i-xdim] != 9){
				board[i-xdim]++;
			}
			if((i+xdim) < (xdim*ydim) && board[i+xdim] != 9){
				board[i+xdim]++;
			}
			if((i-xdim-1) >= 0 && ((i % xdim) != 0) && board[i-xdim-1] != 9) {
				board[i-xdim-1]++;
			}
			if(((i+xdim+1) < (xdim*ydim)) && (((i+1) % xdim) != 0) && board[i+xdim+1] != 9) {
				board[i+xdim+1]++;
			}
			if(((i-xdim+1) >= 0) && (((i+1) % xdim) != 0) && board[i-xdim+1] != 9) {
				board[i-xdim+1]++;
			}
			if(((i+xdim-1) < (xdim*ydim)) && ((i % xdim) != 0) && board[i+xdim-1] != 9) {
				board[i+xdim-1]++;
			}
		}
	}
}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
	for(unsigned int i{0}; i < xdim*ydim; i++){
		board[i] += hiddenBit();
	}
}

void cleanBoard(char * board){
	delete [] board;
	board = NULL;
}

void printBoard(char * board, std::size_t xdim, std::size_t ydim){
	for(unsigned int i{0}; i < xdim*ydim; i++){
		if(board[i] >= hiddenBit() && board[i] < (markedBit() + hiddenBit())){
			std::cout << '*';
		}
		else if (board[i] >= markedBit() + hiddenBit()){
			std::cout << 'M';
		}
		else for(int j{0}; j < 10; j++){
			if(board[i] == j){
				std::cout << j;
			}
		}
		if((i+1) % xdim == 0){
			std::cout << std :: endl;
		}
	}
}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
	if( board[(yloc*xdim)+xloc] & markedBit() )          //Marked
		return 1;
	else if( board[(yloc*xdim)+xloc] < markedBit() )				//Already Revealed
		return 2;
	else if( (board[(yloc*xdim)+xloc] - hiddenBit()) == 0x09 ){ 		//Goose
		board[(yloc*xdim)+xloc] &= valueMask();
		return 9;
	}

	board[(yloc*xdim)+xloc] &= valueMask();
	if(board[(yloc*xdim)+xloc] == 0x00){
		if((yloc*xdim)+xloc-1 >= 0 && (((yloc*xdim)+xloc) % xdim != 0) && (((board[(yloc*xdim)+xloc-1]) - hiddenBit()) != 0x09)){
			board[(yloc*xdim)+xloc-1] &= valueMask();
		}
		if((yloc*xdim)+xloc+1 <= xdim*ydim && (((yloc*xdim)+xloc+1) % xdim != 0 && (((board[(yloc*xdim)+xloc+1]) - hiddenBit()) != 0x09))){
			board[(yloc*xdim)+xloc+1] &= valueMask();
		}
		if((yloc*xdim)+xloc-xdim >= 0 && (((board[(yloc*xdim)+xloc-xdim]) - hiddenBit()) != 0x09)){
			board[(yloc*xdim)+xloc-xdim] &= valueMask();
		}
		if((yloc*xdim)+xloc+xdim <= xdim*ydim && (((board[(yloc*xdim)+xloc+xdim]) - hiddenBit()) != 0x09)){
			board[(yloc*xdim)+xloc+xdim] &= valueMask();
		}
		if((yloc*xdim)+xloc-xdim-1 >= 0 && (((yloc*xdim)+xloc) % xdim != 0) && (((board[(yloc*xdim)+xloc-xdim-1]) - hiddenBit()) != 0x09)) {
			board[(yloc*xdim)+xloc-xdim-1] &= valueMask();
		}
		if((yloc*xdim)+xloc+xdim+1 <= xdim*ydim && (((yloc*xdim)+xloc+1) % xdim != 0) && (((board[(yloc*xdim)+xloc+xdim+1]) - hiddenBit()) != 0x09)) {
			board[(yloc*xdim)+xloc+xdim+1] &= valueMask();
		}
		if((yloc*xdim)+xloc-xdim+1 >= 0 && (((yloc*xdim)+xloc+1) % xdim != 0) && (((board[(yloc*xdim)+xloc-xdim+1]) - hiddenBit()) != 0x09)) {
			board[(yloc*xdim)+xloc-xdim+1] &= valueMask();
		}
		if((yloc*xdim)+xloc+xdim-1 <= xdim*ydim && (((yloc*xdim)+xloc) % xdim != 0) && (((board[(yloc*xdim)+xloc+xdim-1] - hiddenBit())) != 0x09)) {
			board[(yloc*xdim)+xloc+xdim-1] &= valueMask();
		}
	}
	return 0;
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
	if(board[(yloc*xdim)+xloc] < markedBit())      // If Already Revealed
		return 2;
	if(board[(yloc*xdim)+xloc] >= markedBit() + hiddenBit()){        //If Already Marked, unmark
		board[(yloc*xdim)+xloc] -= markedBit();
		return 0;
	}
	board[(yloc*xdim)+xloc] += markedBit();
	return 0;
}

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
	unsigned int count{0};
	for(unsigned int i{0}; i < xdim*ydim; i++){
		if(board[i] >= hiddenBit()){
			if(((board[i] & valueMask()) < 0x09)){
				return false;
			}
		}
	}
	return true;
}
