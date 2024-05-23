/**============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Christopher Deluigi
| Language: c
|
| To Compile:
| gcc -o pa01 pa01.c
|
|
| To Execute:
|
| c -> ./pa01 kX.txt pX.txt
|
|
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2023
| Instructor: McAlpin
| Due Date: 10/8/2023 per assignment
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <ctype.h>   

#define limit 9999
#define row 80

void matrix_multiply(int **result, int **matrix1, int **matrix2, int n) {//Function to perform matrix multiplication
    for (int i = 0; i < n; i++) {               
        for (int j = 0; j < n; j++) {   //for loop sets up and sets matrix for all the cases
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] %= 26; //keeps it within alphebaet
        }
    }
}

//function to encrypt the plaintext using the Hill cipher
void encrypt(char *plaintext, int **key_matrix, int n) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += n) {  //for loop sets plain text to get encrypted
        int block[n]; //sets size of matrix
        for (int j = 0; j < n; j++) {
            block[j] = plaintext[i + j] - 'a'; //convert to numerical  numbers
        }

        int result[n];
        for (int j = 0; j < n; j++) {
            result[j] = 0;
            for (int k = 0; k < n; k++) {
                result[j] += key_matrix[j][k] * block[k];
            }
            result[j] %= 26; //keeps it within alphebaet
        }

        for (int j = 0; j < n; j++) {
            plaintext[i + j] = result[j] + 'a'; //chages back to characters
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s key_file.txt plaintext_file.txt\n", argv[0]);
        return 1;
    }

    FILE *key_file = fopen(argv[1], "r"); //line reads the key matrix from the key file and passes it on
    int n;
    fscanf(key_file, "%d", &n);
    int **key_matrix = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        key_matrix[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            fscanf(key_file, "%d", &key_matrix[i][j]);
        } //scans file and then closes
    }
    fclose(key_file);



    FILE *plaintext_file = fopen(argv[2], "r");     //read the plaintext from the plaintext file
    char plaintext[10000];
    //fgets(plaintext, sizeof(plaintext), plaintext_file);
    int len = strlen(plaintext);
    char c;
    while ((c = fgetc (plaintext_file)) != EOF) 
    {
         //converts plaintext to lowercase and remove non-alphabetic characters from plainetezt
        
        if (isalpha(c))
        {
            plaintext[len++] = tolower(c);
        }
    }
    int padding = 0;
        if (len % n !=0)
        {
            padding = n - (len % n);
            for (int index = 0; index < padding; index++) //does padding if needed using x
            {
            plaintext[len++] = 'x'; //adds x if needed to end
            }
        }
    //prints output the key matrix to terminal
    printf("\nKey matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", key_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //print plaintext to terminal
    printf("Plaintext:\n");
    for(int index  = 0; index < len; index += row )
    {
        for (int j = index; (j < index + row) && (j < len); j++)
        {
            putchar(plaintext[j]);
        }
        putchar('\n');
    }
        printf("\n");

    //encrypts the plaintext
    encrypt(plaintext, key_matrix, n);

    

    
    printf("Ciphertext:\n"); //prints cipher text to terminal
    len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        putchar(plaintext[i]);
        if ((i + 1) % 80 == 0) {
            putchar('\n');
        }
    }
    putchar('\n');

    for (int i = 0; i < n; i++) {
        free(key_matrix[i]);//frees alocated memory
    }
    free(key_matrix);

    fclose(plaintext_file);
    return 0;
}
/*=============================================================================
| I [Christopher Deluigi] (Ch554452) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/