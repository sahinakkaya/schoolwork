#include <stdio.h>  // printf, fgets, feof, fopen, fscanf
#include <stdlib.h> // EXIT_FAILURE, EXIT_SUCCESS
#include <string.h> // strlen, strtok, strcpy, strcat

#define NUMBER_OF_LINES 10000
#define MAX_LINE_LENGTH 200

typedef struct instruction_s {
    int step;
    int index;
} instructions_s;

/*
 * Takes a file pointer and a char pointer array
 * to store each line of the file.
 * @param file a pointer to the file that is going to read.
 * @param lines a pointer sequence (array) that is used to store each line.    
*/
void read_the_book(char* file, char* lines[])
{
    FILE* fp = fopen(file, "r");
    int i = 0;
    while (!feof(fp)) {
        fgets(lines[i], MAX_LINE_LENGTH, fp);
        i++;
    }
    fclose(fp);
}

/*
 * Takes a file pointer and an instructions_s pointer
 * and finaly returns the number of lines in the file.
 * @param file a pointer to the file that is going to read.
 * @param inst an instruction_s pointer sequence that is used to store the instructions for each line.    
 * @return number of lines in the file.
*/
int read_the_instructions(char* file, instructions_s* inst)
{
    FILE* fp = fopen(file, "r");
    int i = 0;
    while (!feof(fp)) {
        fscanf(fp, "%d %d", &inst[i].step, &inst[i].index);
        i++;
    }
    fclose(fp);
    return i - 1;
}

/*
 * Takes a char pointer to a word, replaces uppercase letters with lowercase letters
 * and removes all characters except numbers and lowercase letters.
 * @param n_word a char pointer to a word
 * @return a pointer to the final string 
*/
char* make_lower_and_rm_punc(char* n_word)
{
    char* str = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    int word_length = strlen(n_word);
    int str_length = 0;
    for (int i = 0; i < word_length; i++) {
        if (n_word[i] >= 'A' && n_word[i] <= 'Z') {
            n_word[i] += 32; // To make it lowercase we need to add 32.
        }
        if ((n_word[i] >= 'a' && n_word[i] <= 'z') || (n_word[i] >= '0' && n_word[i] <= '9')) {
            str[str_length++] = n_word[i];
        }
    }
    str[str_length] = '\0';
    return str;
}

/*
 * Takes a char pointer to a sentence and an integer n,
 * returns nth word of the sentence. 
 * @param s a char pointer to a sentence
 * @param n an integer that tells the index of the word which is going to be returned  
 * @return a pointer to a string that contains only numbers or lowercase letters.
*/
char* get_word(char* s, int n)
{
    char* tokenized_word = strtok(s, " ");
    while (n-- > 0) {
        tokenized_word = strtok(NULL, " ");
    }
    tokenized_word = make_lower_and_rm_punc(tokenized_word);
    return tokenized_word;
}

/*
 * Takes a bunch of lines, instructions and an empty string that is going to store 
 * extracted sentence.
 * @param lines a pointer sequence (array) that contains the lines from the book.
 * @param instructions an instruction_s pointer sequence that contains instructions.
 * @param n_instructions number of lines in the instructions file.
 * @param sentence a char pointer that is going to store the extracted sentence.
*/
void get_sentence(char** lines, struct instruction_s* instructions,
    int n_instructions, char* sentence)
{
    int line_index = 0;
    for (int i = 0; i < n_instructions; i++) {
        int step = instructions[i].step;
        int index_of_word = instructions[i].index;
        line_index += step;
        char* word = get_word(lines[line_index - 1], index_of_word - 1);
        if (i == 0) {
            strcpy(sentence, word);
        } else {
            strcat(sentence, word);
        }
        if (i + 1 != n_instructions) {
            strcat(sentence, " ");
        }
        free(word);
    }
    strcat(sentence, "\n");
}

int main(int argc, char* argv[])
{
    // Checks whether the program is started with 3 arguments (i.e. ./assignment4 foo bar).
    if (argc != 3) {
        printf("You entered %d argument%s.\n", argc, argc == 1 ? "" : "s");
        printf("Please enter exactly 3 arguments!\n");
        return EXIT_FAILURE;
    }
    // Allocates memory for storing the lines from the book.
    char* lines[NUMBER_OF_LINES];
    for (int i = 0; i < NUMBER_OF_LINES; i++) {
        lines[i] = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));
    }
    // Allocates memory for storing the instructions from instructions file.
    instructions_s* instructions = (instructions_s*) malloc(NUMBER_OF_LINES * sizeof(instructions_s));
    
    // Allocates memory for storing the hidden sentence.
    char* sentence = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));

    // Reads and stores the information from given files.
    read_the_book(argv[1], lines);
    int number_of_instructions = read_the_instructions(argv[2], instructions);

    // Gets the hidden sentence and prints it.
    get_sentence(lines, instructions, number_of_instructions, sentence);
    printf("%s", sentence);

    // Frees the memories that is allocated before.
    for (int i = 0; i < NUMBER_OF_LINES; i++) {
        free(lines[i]);
    }
    free(instructions);
    free(sentence);

    return EXIT_SUCCESS;
}
