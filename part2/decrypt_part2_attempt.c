
/* 
 * File:   decrypt_part2_attempt.c
 * Author: Brendan Luna
 *
 * Created on September 16, 2014
 */

#include "header.h"

#define EXIT_FAILURE 1
#define KEY_SIZE 21

/*
 * 
 */
int main(int argc, char* argv[]) {

    FILE *textFile;
    FILE *textFileTwo;
    char *string;
    int fileSize, fileSizeTwo;
    int x, y;

    char userKey[KEY_SIZE];
    char fileNameTwo[100000];

    char defaultKey[KEY_SIZE];
    int user_choice, user_choice2, user_choice3;

    printf ("\nAttempting decryption...");

        // gather file user wants to decrpyt
        printf("\nPlease provide the name of the file you'd like to decrypt (.txt): ");
        scanf("%s", fileNameTwo);
        textFileTwo = fopen(fileNameTwo, "r");
        printf("Opening %s...\n", fileNameTwo);

        if(textFileTwo == NULL){
            perror("Error while opening the file.\n");
            exit(EXIT_FAILURE);
        }

        // printf("The contents of %s are: \n", fileNameTwo);

        // get size of input file and allocate memory for it.
        fseek(textFileTwo, 0L, SEEK_END);
        fileSizeTwo = ftell(textFileTwo);
        string = malloc(fileSizeTwo * sizeof(char));
        fseek(textFileTwo, 0L, SEEK_SET);

        // read text file into array pointed to by 'string'
        if (textFileTwo){
            char *iterator = string;
            while((y = getc(textFileTwo)) != EOF){
                *iterator = (char)y;
                // debug print statement of unencrypted text
                // printf("%c", *iterator);            
                iterator++;
            }
            iterator = string;        
        }

        printf("GOT HERE");

        char decrypted[fileSizeTwo];

        decrypt_attempt(string, decrypted);
        printf("\nDecrypted text: %s\n\n", decrypted);

    return 0;

}


    // LEASE decryption alorithm
    void decrypt_attempt(char* encryptedText, char *decryptedText){

        int i;
        printf("Stringlen of encryptedText is: %lu", strlen(encryptedText));
        for(i = 0; i < strlen(encryptedText); i++){
            // XOR bitwise flipping by 10
            int flip = encryptedText[i];
            // set output to NOT bitwise shift of the previous XOR
            // will create NON-ASCII chars, adding a layer of diffusion
            decryptedText[i] = ~flip;
        }
    }
    


