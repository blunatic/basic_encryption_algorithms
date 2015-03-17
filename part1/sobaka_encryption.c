
/* 
 * File:   main.c
 * Author: Alex Kibis & Brendan Luna
 *
 * Created on September 8, 2014, 9:45 PM
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
    char fileNameTwo[50];

    char defaultKey[KEY_SIZE];
    int user_choice, user_choice2, user_choice3;

    printf ("\nPlease choose either\n(1.)encryption\nor\n(2.)decryption\n\nfor a file: ");
    scanf ("%d", &user_choice);

// Main Encryption choice
if(user_choice == 1){
    printf("You've chosen ENCRYPTION\n\nWould you like to create a (1.)custom user key or a (2.)random default key for your encryption?\n");
    scanf("%d", &user_choice2);
    if(user_choice2 == 1){
        printf("Please enter your custom 20-digit key:\n");
        scanf("%s", userKey);

        if(strlen(userKey) != 20){
            printf("Key must be at least 20 digits long. Please try another: \n");
            scanf("%s", userKey);
        }
    }

    // Use auto-generated key.
    else if(user_choice2 == 2){
        // ASCII 33-126, 20-digit key
            int i;
            int randomNumber;
            for (i=0; i < KEY_SIZE - 2; i++){
                srand((int)fopen("/dev/urandom", "r"));
                randomNumber = 33 + rand() % 93;
                // printf("Random number: %d\n", randomNumber);
                defaultKey[i] = (char)randomNumber;
            }
            defaultKey[20] = '\0';

            // Provide user their auto-generated key for 
            // them to save for decrytion later
            printf("[SAVE THIS!] Auto-generated encryption key: %s\n", defaultKey);
            
    } else {
        printf("Invalid choice.\n");
    }

    printf("\nWould you like to open a (1.)custom file or use the (2.)default file for your encryption?\n");
    scanf("%d", &user_choice3);
    if(user_choice3 == 1){
        printf("Please provide the custom file name: ");
        scanf("%s", fileNameTwo);
        textFile = fopen(fileNameTwo, "r");
        printf("Opening %s...\n", fileNameTwo);
    } else if(user_choice3 == 2){
        printf("Using default file: test.txt\n");
        textFile = fopen("test.txt", "r");
    } else{
        printf("Invalid choice.\n");
    }

    if(textFile == NULL){
        printf("Error opening file.");
        exit(EXIT_FAILURE);
    }
        // get size of input file and allocate memory for it.
        fseek(textFile, 0L, SEEK_END);
        fileSize = ftell(textFile);
        string = malloc(fileSize * sizeof(char));
        fseek(textFile, 0L, SEEK_SET);

        // read text file into array pointed to by 'string'
        if (textFile){
            char *iterator = string;
            while((x = getc(textFile)) != EOF){
                *iterator = (char)x;
                // debug print statement of unencrypted text
                // printf("%c", *iterator);            
                iterator++;
            }
            iterator = string;        
        }

        char encrypted[fileSize];

        // Check whether user has chosen their own key or auto-generated key
        if (userKey[0] == '\0'){
            // Run actual text encryption through Sobaka method
            sobaka(defaultKey, string, encrypted);
            printf("\nEncrypted text: %s\n", encrypted);

            // Write the encrypted text to new file
            printf("Writing encrypted string...\n");
            textFile = fopen("encryptedText.txt", "w+");
            fputs(encrypted, textFile);

        } else{
            sobaka(userKey, string, encrypted);
            printf("\nEncrypted text: %s\n", encrypted);
            printf("Your encryption key is: %s\n", userKey);
            printf("DO NOT LOSE IT!\n");

            printf("Writing encrypted string to file...\n");
            textFile = fopen("encryptedText.txt", "w+");
            fputs(encrypted, textFile);
        }

        // Free resources and close
        fclose(textFile);
        free(string);

}


// Main Decryption choice
else if(user_choice == 2){
        char file_name[50];
        char ch;

        // gather file user wants to decrpyt
        printf("You've chosen DECRYPTION\n\nPlease provide the name of the file you'd like to decrypt (.txt): ");
        scanf("%s", file_name);
        textFileTwo = fopen(file_name, "r");
        printf("Opening %s...\n", file_name);

        if(textFileTwo == NULL){
            perror("Error while opening the file.\n");
            exit(EXIT_FAILURE);
        }

        printf("The contents of %s are: \n", file_name);

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
                printf("%c", *iterator);            
                iterator++;
            }
            iterator = string;        
        }

        printf("\nNow please provide the key to decrypt the file: ");
        scanf("%s", userKey);

        char decrypted[fileSizeTwo];

        povodok(userKey, string, decrypted);
        printf("\nDecrypted text: %s\n\n", decrypted);

    } else{
        printf("Invalid choice.\n");
    }
    return 0;

}

    // DOG encryption algorithm
    void sobaka(char* key, char* fileInMemory, char *encryptedText){
        int i, j;

        for(i = 0; i < strlen(fileInMemory); i++){
            // Since key will only be length of 20, take modulus once i hits 20
            // and continue bitwise between key fileInMemory (the encrypted text)
            // until i reaches the total length of fileInMemory
            // The Povodok Decryption method below will use same concept
            if(i % 20 == 0){
                j = 0;
            }
            // XOR bitwise flipping
            int flip = fileInMemory[i] ^ key[j % (sizeof(key)/sizeof(char))];
            // set output to NOT bitwise shift of the previous XOR
            // will create NON-ASCII chars, adding a layer of diffusion
            encryptedText[i] = ~flip;
            j++;
        }
    }

    // LEASE decryption alorithm
    void povodok(char* key, char* encryptedText, char *decryptedText){

        int i, j;

        for(i = 0; i < strlen(encryptedText); i++){
            if (i % 20 == 0){
                j = 0;
            }
            // XOR bitwise flipping
            int flip = encryptedText[i] ^ key[j % (sizeof(key)/sizeof(char))];
            // set output to NOT bitwise shift of the previous XOR
            // will create NON-ASCII chars, adding a layer of diffusion
            decryptedText[i] = ~flip;
            j++;
        }
    }
    


