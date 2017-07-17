/*
 * Description: This file contains a method to allow a page to be cgi friendly.
 *      Note that spaces in a page are sometimes not accounted and will cause source to minify in the browser.
 *      Should add a way to find all quotes and convert them to \" so string is not confused.
 *      Wierd begining symbol made when obtaining file info, don't know how to remove it safetly, 
 *          so just put something together that seemed to work--program probably still has huge problems. 
 *          Probably a fault if a file contains slashes /\ or maybe even carrots <>^.
 *      Wierd, ending symbol of closing curly }, just checked if was last position, don't include it. Wasn't there in other examples.
 *      
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//methods
void cgiFriendly();
void printFileContents (char* pageFile);

// int main (){
//     printf("Content-Type: text/css \n\n");
//     cgiFriendly ("mystyleOriginal.css");

//     return 0;
// }

void cgiFriendly (char* pageFile){
    FILE *file;
    file = fopen (pageFile , "r");
    if (file == NULL) {
      perror ("Error opening file");
    }

    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET); //position back to begining of file for reading.

    char c [fileSize];
    char fileString [fileSize];
    while ( (fgets (c, fileSize, file)) != NULL ){
        strcat(fileString, c);
    }
    fclose (file);

    //trying to remove wierd symbol at start of print. In browser source, it is a bullet. In html it is a square symbol. In print it is a whitespace.
    int fileStringSize = sizeof(fileString);
    char stripped[fileStringSize];
    int i;
    int j = 0;
    // int count = 0;
    //see for filtering: http://icecube.wisc.edu/~dglo/c_class/charfunc.html
    for (i = 0; i < strlen(fileString); i++) {
        if ( (isalpha( fileString[i])) ) {
            stripped[j] = fileString[i];
            j++;
        }
        else if ( (isdigit( fileString[i])) ) {
            stripped[j] = fileString[i];
            j++;
        }
        else if ( (isspace( fileString[i])) ) {
            stripped[j] = fileString[i];
            j++;
        }
        else if ( (ispunct( fileString[i])) ) {
            if (i != fileStringSize) {
                stripped[j] = fileString[i];
                j++;
            }
        }
    }
    stripped[j] = '\0';
    printf ("%s", stripped);

}


























/* SCRATCH
------------------------AFTER FCLOSE...------------------------
    // char* string = fileString;


    // int fileStringSize = sizeof(fileString);
    // printf ("%d", string[fileStringSize]);
    // printf("--%.*string--", 1, string+2);
    // printf("part1\n");


    // int fileStringSize = sizeof(fileString) + 1;
    // char* string= (char*) malloc(fileStringSize);
    // memcpy(string, fileString, fileStringSize);
    // string[fileStringSize] = '\0'; 


    // int strLen = getLength(src) + 1;
    // char *string = calloc(strLen, sizeof(char)); // Allocate strLen * sizeof(char)
    // if (str == NULL) {
    //     // Error allocating str - handle error
    // }
    // string [strLen - 1] = '\0'; // zero-based, so char is after final character


    // strcat(string, "\0");
------------------------AFTER STRIPPING IF------------------------
        // else if ( iscntrl( fileString[i]) ) {
        //     printf ("iscntrl: %c", fileString[i]);
        // }
        // else if ( isprint( fileString[i]) ) {
        //     printf ("isprint: %c", fileString[i]);
        // }
        // else if ( isgraph( fileString[i]) ) {
        //     printf ("isgraph: %c", fileString[i]);
        // }
        // else if ( isspace( fileString[i]) ) {
        //     printf ("isspace: %c", fileString[i]);
        // }
        // else if ( isupper( fileString[i]) ) {
        //     printf ("isupper: %c", fileString[i]);
        // }
        // else if ( islower( fileString[i]) ) {
        //     printf ("islower: %c", fileString[i]);
        // }
        // else if ( isalpha( fileString[i]) ) {
        //     printf ("isalpha: %c", fileString[i]);
        // }
        // else if ( isdigit( fileString[i]) ) {
        //     printf ("isdigit: %c", fileString[i]);
        // }
        // else if ( isxdigit( fileString[i]) ) {
        //     printf ("isxdigit: %c", fileString[i]);
        // }
        // else if ( ispunct( fileString[i]) ) {
        //     printf ("ispunct: %c", fileString[i]);
        // }
        
        // else if ( 
        //     (fileString[i] == "\n") || (fileString[i] == "\n") || (fileString[i] == "\n") || (fileString[i] == "\n") || 
        //     (fileString[i] == "\n") || (fileString[i] == "\n") || (fileString[i] == "\n") || (fileString[i] == "\n") || 
        //     (fileString[i] == "\n") || (fileString[i] == "\n") || (fileString[i] == "\n") || (fileString[i] == "\n") || 
        //     (fileString[i] == "\n") || (fileString[i] == "\n") || (fileString[i] == "\n") || (fileString[i] == "\n") || 
        //     (fileString[i] == "\n") || (fileString[i] == "\n") || (fileString[i] == "\n") || (fileString[i] == "\n")
        //     "\/'{}();:-_
        //     (total == total1) && (total == total2)
        //     ) {
        //     stripped[j] = fileString[i];
        //     j++;
        // }
------------------------CGI FRIENDLY END------------------------
    // printf ("%s", string);
    // printf ("\n");

    // printf ("%s", fileString);
    // printf ("\n");
   
    // return string;
------------------------s------------------------

------------------------s------------------------

*/
