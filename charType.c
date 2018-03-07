/* Tyler MacIntosh, tmacinto, 12M, 2/9/18
 * charType.c
 * takes two command line arguments giving the input and output file names,
 * then classifies the characters on each line of the input file into the
 * following categories: alphabetic, numeric, punctuation, & whitespace
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>

#define MAX_STRING_LENGTH 100
int a_quant=0, d_quant=0, p_quant=0, w_quant=0;

// function prototype
void extract_chars(char* s, char* a, char* d, char* p, char* w);

// function main which takes command line argumets
int main(int argc, char* argv[]){
        FILE* in;       //handle for input file
        FILE* out;      //handle for output file
        char* line;     //string holding input line
        char* alpha;    //string holding all alpha chars
        char* digits;   //string holding all digit chars
        char* punct;    //string holding all punctuation chars
        char* whitesp;  //string holding all whitespace chars
        int counter = 1;
        // check command line for correct number of arguments
        if( argc != 3){
                printf("Usage: %s input-file output-file\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        // open input file for reading
        if( (in=fopen(argv[1], "r"))==NULL ){
                printf("Unable to read from file %s\n", argv[1]);
                exit(EXIT_FAILURE);
        }

        // open output file for writing
        if( (out=fopen(argv[2], "w"))==NULL ){
                printf("Unable to write to file %s\n", argv[2]);
                exit(EXIT_FAILURE);
        }

        // allocate strings line, alpha, digits, punct, & whitesp on the heap
        line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        digits = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        punct = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        whitesp = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        assert( line!=NULL && alpha!=NULL && digits!=NULL && punct!= NULL
                && whitesp!=NULL );

        // read each line in input file, extract characters
        while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
                extract_chars(line, alpha, digits, punct, whitesp);
                fprintf(out, "line %d contains:\n", counter);
                fprintf(out, "%d alphabetic characters: %s\n", a_quant, alpha);
                fprintf(out, "%d numeric characters: %s\n", d_quant, digits);
                fprintf(out, "%d punctuation characters: %s\n", p_quant, punct);
                fprintf(out, "%d whitespace characters: %s\n", w_quant, whitesp);
                counter++;
                a_quant = 0;
                d_quant = 0;
                p_quant = 0;
                w_quant = 0;
        }

        // free heap memory associated with string variables line, alpha
        // digits, punctm & whitesp
        free(line);
        free(alpha);
        free(digits);
        free(punct);
        free(whitesp);

        // close input and output files
        fclose(in);
        fclose(out);

        return EXIT_SUCCESS;
}

// definition of function extract_chars
void extract_chars(char* s, char* a, char* d, char* p, char* w){
        int i=0;
        while(s[i]!='\0' && i<MAX_STRING_LENGTH){
                if( isalpha(s[i]) ){
                        a[a_quant] = s[i];
                        a_quant++;
                } else if( isdigit(s[i]) ){
                        d[d_quant] = s[i];
                        d_quant++;
                } else if( ispunct(s[i]) ){
                        p[p_quant] = s[i];
                        p_quant++;
                } else if( isspace(s[i]) ){
                        w[w_quant] = s[i];
                        w_quant++;
                }
                i++;
        }
        a[a_quant] = '\0';
        d[d_quant] = '\0';
        p[p_quant] = '\0';
        w[w_quant] = '\0';
        //reset all quantites back to 0
}
