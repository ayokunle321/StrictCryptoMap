#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Reverses the given string 'str' in place.
    Parameters:
        - str: Pointer to the input string to be reversed.
    Returns: 
        None
*/
void reverse_string(char* str);

/*
    Appends a character 'c' to the end of the string 's'.
    Parameters:
        - s: Pointer to the destination string where 'c' will be appended.
        - c: The character to be appended.
    Returns:
        None
*/
void append(char* s, char c);

/*
    Clears the content of the given string 'str'.
    Parameters:
        - str: Pointer to the string to be cleared.
    Returns:
        None
*/
void clear_string(char* str);

/*
    Encrypts and reverses the words in the input text file by replacing each plain character with its corresponding cipher.
    Parameters:
        - text: Pointer to the input text file to be encrypted.
        - mapping: Pointer to the file containing the cipher-to-plain character mapping.
    Returns:
        None
*/
void encrypt(FILE* text, FILE* mapping);

/*
    Decrypts and reverses the words in the input text file by replacing each cipher character with its corresponding plain character.
    Parameters:
        - text: Pointer to the input text file to be decrypted.
        - mapping: Pointer to the file containing the cipher-to-plain character mapping.
    Returns:
        None
*/
void decrypt(FILE* text, FILE* mapping);


int main(int argc, char *argv[]){

    char *ext = NULL; 
    char *mapping_name = NULL;
    char *input_name = NULL;
    int arg_count = 0;
    int mode = 0;
    
    FILE* text;
    FILE* mapping;

    if (argc != 7) {
    fprintf(stderr,"Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>\n");
    exit(7);
    }
    
    // checking validity of command line arguments
    for (int i = 1; i < argc; i++) {
        ext = strrchr(argv[i], '.'); //gets the extension of a file if it has one
        
        if (ext != NULL){
            if (strcmp(ext+1, "csv") == 0) {
                mapping_name = argv[i];
                arg_count++;
                if (strcmp(argv[i-1], "-t") == 0){
                    arg_count++;
                }
            } 
            
            else if (strcmp(ext+1, "txt") == 0) {
                input_name = argv[i];
                arg_count++;
                if (strcmp(argv[i-1], "-i") == 0){
                    arg_count++;
                }
            }
        }

        else{
        
            if (strcmp(argv[i], "-m") == 0){
                arg_count++;
                mode = atoi(argv[i+1]);
                arg_count++;
            }
        }
    }
    
    if (arg_count != 6) {
        fprintf(stderr,"Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>\n");
        exit(7);
    }
    
    else{
            
        if ((mapping = fopen(mapping_name, "r")) == NULL) {
            fprintf(stderr,"Error: Mapping file %s does not exist\n", mapping_name);
            exit(3);
        }

        else if ((text = fopen(input_name, "r")) == NULL) {
            fprintf(stderr,"Error: Input word file %s does not exist\n", input_name);
            exit(5);
        }

        else if ((mode != 1) && (mode != 2)){
            fprintf(stderr,"You entered %d. Sorry, your mode must be 1 for encryption or 2 for decryption\n", mode);
            exit(6);
        }

        else{

            char line[100] = {0};
            int plains_array[26] = {0};
            int ciphers_array[26]= {0};
            char plains;
            char ciphers;
            int line_count = 0;
            
            //checking format of mapping file
            while (fgets(line, 100, mapping) != NULL) {
                int len = strlen(line);
                sscanf(line, "%c,%c\n", &plains, &ciphers);
                
                //adjusting for alphabet arrays
                int plains_index = plains - 'a';
                int ciphers_index = ciphers - 'a';

                if (len > 4) {
                    fprintf(stderr,"Error: The format of mapping file %s is incorrect\n", mapping_name);
                    exit(4);
                }
                
                //checking validity of charachter (in the alphabet?)
                else if (plains_index < 0 || plains_index >= 26 || ciphers_index < 0 || ciphers_index >= 26){
                    fprintf(stderr,"Error: The format of mapping file %s is incorrect\n", mapping_name);
                    exit(4);
                }

                plains_array[plains_index] += 1;
                ciphers_array[ciphers_index] += 1;

                line_count++;
            }

            fclose(mapping);
            
            //cheking if any of the alphabets are repeated or missing
            int is_repeated = 0;
            for (int i = 0; i < 26; i++) {
                if ((plains_array[i] != 1) || (ciphers_array[i] != 1)) {
                    is_repeated = 1;
                    break;
                }
            }
            
            //checking if the mapping file has more than 26 lines
            if (line_count != 26){
                fprintf(stderr,"Error: The format of mapping file %s is incorrect\n", mapping_name);
            }

            else if (is_repeated == 1){
                fprintf(stderr,"Error: The format of mapping file %s is incorrect\n", mapping_name);
            }

            else{
                //encryption
                if (mode == 1){
                    mapping = fopen(mapping_name, "r");
                    encrypt(text,mapping);
                }
                //decryption
                else if (mode == 2){
                    mapping = fopen(mapping_name, "r");
                    decrypt(text,mapping);
                }
            }
        }
    }

    return 0;

}

void reverse_string(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

void append(char* s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

void clear_string(char *str) {
    str[0] = '\0';
}

void encrypt (FILE *text, FILE *mapping){
    char plains_array[26] = {0};
    char ciphers_array[26]= {0};
    char line[100] = {0};
    int i = 0;

    while (fgets(line, 100, mapping) != NULL) {
        sscanf(line, "%c,%c\n", &plains_array[i], &ciphers_array[i]);
        i++;
    }
    
    char c;
    char cs[100];
    clear_string(cs);
        
    while ((c = fgetc(text)) != EOF) {
        if (c != '\n'){
            for (int i = 0; i < 26; i++){
                if (c == plains_array[i]){
                    append(cs, ciphers_array[i]);
                    break;
                }
            }
        }
        
        else{
            reverse_string(cs);
            fprintf(stdout,"%s\n", cs);
            clear_string(cs);

        }
    }
    
    reverse_string(cs);
    fprintf(stdout,"%s\n", cs);
    
    fclose(mapping);
    fclose(text);

}

void decrypt (FILE *text, FILE* mapping){
    char plains_array[26] = {0};
    char ciphers_array[26]= {0};
    char line[100] = {0};
    int i = 0;

    while (fgets(line, 100, mapping) != NULL) {
        sscanf(line, "%c,%c\n", &plains_array[i], &ciphers_array[i]);
        i++;
    }
    
    char c;
    char cs[100];
    clear_string(cs);
        
    while ((c = fgetc(text)) != EOF) {
        if (c != '\n'){
            for (int i = 0; i < 26; i++){
                if (c == ciphers_array[i]){
                    append(cs, plains_array[i]);
                    break;
                }
            }
        }
        
        else{
            reverse_string(cs);
            fprintf(stdout,"%s\n", cs);
            clear_string(cs);

        }
    }
    
    reverse_string(cs);
    fprintf(stdout,"%s\n", cs);

    fclose(mapping);
    fclose(text);

}


