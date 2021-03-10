#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);
bool searchhoriLR(char** arr, char** list, int column, int listColumn, int listRow, int row);
bool searchhoriRL(char** arr, char** list, int column, int listColumn, int listRow, int row);
bool searchverti(char** arr, char** list, int column, int listColumn, int listRow, int row);
bool searchdiagLR(char** arr, char** list, int column, int listColumn, int listRow, int row);
bool searchdiagRL(char** arr, char** list, int column, int listColumn, int listRow, int row);

int main(int argc, char **argv) {
    int bSize = 15;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
    char **words = (char**)malloc(50 * sizeof(char*));
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }
    for(i=0; i<bSize; i++){
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
    fclose(fptr);
    fptr = fopen("states.txt", "r");
    if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
    for(i=0; i<50; i++){
        *(words+i) = (char*)malloc(20 * sizeof(char));
        fgets(*(words+i), 20, fptr);
    }
    for(i=0; i<49; i++){
        *(*(words+i) + strlen(*(words+i))-2) = '\0';
    }
    printf("Printing list of words:\n");
    for(i=0; i<50; i++){
        printf("%s\n", *(words + i));
    }
    printf("\n");
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
    printf("\n");
    searchPuzzle(block, bSize, words, 50);
    printf("\n");
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
    printf("\n");
    
    return 0;
}

void printPuzzle(char** arr, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%c ", (*(*(arr+i)+j)));
        }
        printf("\n");
    }
}

void searchPuzzle(char** arr, int n, char** list, int listSize){
    bool check = false;
    char **sortArray = list;
    for(int i = 0; i < listSize; i++) {
        for (int j = 0; j < listSize; j++) {
            if(*(*(list+i)+j) >= 97 && *(*(list+i)+j) <= 122){
                *(*(list+i)+j) = *(*(list+i)+j)-32; 
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int column = 0; column < listSize; column++){
            for(int j = 0; j < n; j++){
                for(int row = 0; row < strlen(*(list+column)); row++){
                    if(*(*(arr+i)+j) == *(*(list+column)+row) || *(*(arr+i)+j) == *(*(list+column)+row) + 32 || *(*(arr+i)+j) >= 65 && *(*(arr+i)+j) <= 90 || *(*(arr+i)+j) >= 97 && *(*(arr+i)+j) <= 122 ){
                    
                        check = searchhoriRL(arr, list, i, column, row, j);

                        if (check == true) {
                            printf("\nWord found: ");
                            for(int k = 0; k < strlen(*(list+column)); k++){
                                if(k != 0){
                                    printf("%c",*(*(arr+i-k)+j-k)+32);
                                }else{
                                    printf("%c",*(*(arr+i)+j+k));
                                }
                            
                                if(*(*(arr+i)+j-k) >= 65 && *(*(arr+i)+j-k) <= 90){
                                    *(*(arr+i)+j-k) = (*(*(arr+i)+j-k)) + 32;
                                }
                            
                            }
                            
                        }

						check = searchhoriLR(arr, list, i, column, row, j);

                        if (check == true) {
                            printf("\nWord found: ");
                            for(int k = 0; k < strlen(*(list+column)); k++){
                                if(k != 0){
                                printf("%c",*(*(arr+i)+j+k)+32);
                                }else{
                                    printf("%c",*(*(arr+i)+j+k));
                                }
                            
                                if(*(*(arr+i)+j+k) >= 65 && *(*(arr+i)+j+k) <= 90){
                                *(*(arr+i)+j+k) = (*(*(arr+i)+j+k)) + 32;
                                }
                            
                            }
                           
                        }

                        check = searchverti(arr, list, i, column, row, j);

                        if (check == true) {
                            printf("\nWord found: ");
                            for(int k = 0; k < strlen(*(list+column)); k++){
                                if(k != 0){
                                    printf("%c",*(*(arr+i+k)+j)+32);
                                }else{
                                    printf("%c",*(*(arr+i+k)+j));
                                }
                            
                                if(*(*(arr+i+k)+j) >= 65 && *(*(arr+i+k)+j) <= 90){
                                    *(*(arr+i+k)+j) = (*(*(arr+i+k)+j)) + 32;
                                }
                            
                            }
                        

                        }

                        check = searchdiagRL(arr,list,i, column, row, j);

                        if(check == true){
                            printf("\nWord found: ");
                            for(int k = 0 ; k < strlen(*(list+column)); k++){
                                if(k != 0 && *(*(arr+i+k)+j+k) >= 65 && *(*(arr+i+k)+j+k) <=90){
                                    printf("%c",*(*(arr+i+k)+j+k)+32);
                                }
                                else if(k == 0 && *(*(arr+i+k)+j+k) >= 97 && *(*(arr+i+k)+j+k) <=122){
                                    printf("%c",*(*(arr+i+k)+j+k)-32);
                                }
                                else{
                                printf("%c",*(*(arr+i+k)+j+k));
                                }

                                if(*(*(arr+i+k)+j+k) >= 65 && *(*(arr+i+k)+j+k) <=90){
                                *(*(arr+i+k)+j+k) = (*(*(arr+i+k)+j+k))+32;
                                }
                
                            }
                        }

                        check = searchdiagLR(arr, list, i, column, row, j);

                        if (check == true) {
                            printf("\nWord found: ");
                            for(int k = 0; k < strlen(*(list+column)); k++){
                                 if(k != 0 && *(*(arr+i+k)+j+k) >= 65 && *(*(arr+i+k)+j+k) <=90){
                                    printf("%c",*(*(arr+i+k)+j+k)+32);
                                }
                                else if(k == 0 && *(*(arr+i+k)+j+k) >= 97 && *(*(arr+i+k)+j+k) <=122){
                                    printf("%c",*(*(arr+i+k)+j+k)-32);
                                }
                                else{
                                printf("%c",*(*(arr+i+k)+j+k));
                                }

                                if(*(*(arr+i+k)+j+k) >= 65 && *(*(arr+i+k)+j+k) <=90){
                                *(*(arr+i+k)+j+k) = (*(*(arr+i+k)+j+k))+32;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


bool searchhoriLR(char** arr, char** list, int column, int listColumn, int listRow, int row){
    for(int i = 0; i < strlen(*(list+listColumn)); i++){  
        if(*(*(list + listColumn ) + listRow + i) != *(*(arr + column) + row + i)){
            return false;
        }   
    }
    return true;
}

bool searchhoriRL(char** arr, char** list, int column, int listColumn, int listRow, int row){
    for (int i = 0; i < strlen(*(list+listColumn)); i++) {
        if(*(*(arr + column) + row - i) != *(*(list + listColumn) + listRow + i)){
            return false;
        }
    }
    return true;
}

bool searchverti(char** arr, char** list, int column, int listColumn, int listRow, int row){
    for(int i=0; i < strlen((*(list+listColumn))); i++){
        if (column + i < 15 && listRow + i < 15 ){
            if(* (* ( arr + column + i) + row) >= 65 && * (* ( arr + column +i ) + row) <= 90 || * ( *( arr + column + i) + row) >= 97 && * ( *( arr + column + i) + row) <= 122){
                if(* (* ( arr + column + i)+ row) == * (* ( list + listColumn ) + listRow + i) || * ( *( arr + column+i)+row) == * ( *( list + listColumn) + listRow + i)+ 32){
                   continue;
                }else{
                	return false;
                }
            }else{
            	return false;
            }
        }else{
            return false;
        }
    }
    return true;
}

bool searchdiagLR(char** arr, char** list, int column, int listColumn, int listRow, int row){
    for(int i = 0; i < strlen((*(list+listColumn))); i++){
        if (column + i < 15 && listRow + i < 15 && row - i > 0){
            if(*(*(arr+column+i)+row-i) == *(*(list+listColumn)+listRow+i)){
                continue;
            }else{
                return false;
            }
        }else{
            return false;
        }
        
    }
    return true;
}

bool searchdiagRL(char** arr, char** list, int column, int listColumn, int listRow, int row){
    for(int i=0;i< strlen((*(list+listColumn)));i++){
        if (column + i < 15 && listRow + i <= 15 && row + i <= 15){
            if(*(*(arr+column+i)+row+i) == *(*(list+listColumn)-listRow+i) || *(*(arr+column+i)+row+i) == *(*(list+listColumn)+listRow+i)+32||(*(arr+column+i)+row+i) == *(*(list+listColumn)+listRow+i)+90){
                continue;
            }else{
			 	return false;
			}
        }else{
			return false;
		}
    }
	return true;
    
}


