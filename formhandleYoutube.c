/*
File: formhandleYoutube.c
Author: Saul Lopez
Date: 4.1.17
Copyright (c) 2017

Description:
The program prints out a html file and uses variables obtained from the user
 through the form to format the page -- displays their output and a message.

Error and tips:
strtok and sscanf used to get and split string on '&' and '=' --not accounting encoding.
"" vs ''; matters when in need of string pointer or character
Form Data notes
    if lastname doesn't exist, gets nothing. (note for: sscanf (Token, "lastname=%s", LastName);) 
    if sscanf in token for 'lastname=%s' and it doesn't exist, breaks code. Adding more to query is fine, as long as variable exists.
    Ballpark: if form is different type of input, might get weired symbols--text vs radio button. 1. gives 8ze3 2. gives 8š®Û

*/

#include <stdio.h> //printf, scanf, FILE, fopen/fclose, fprintf, files & term or stream
#include <string.h> //strings mods, strcpy, strcat, strcmp, 
#include <stddef.h> 
#include <stdlib.h> //exit
#include "storeURL.c"

//define

//methods
void header (char *MIME_TYPE);
void start_page (char *Title);
void end_page ();
void linkCSS (char* file);

int main (int argc, char **argv) {
    char *query;
    
    //Start printing html to standard output
    header ("text/html");
    start_page ("Raspberry Pi powered Radio Station! Early Bird. :: confirmation");
    
    printf ("<h3>You have entered the following inputs: </h3>");
    if ( (query = getenv("QUERY_STRING")) ) { //Assuming the 'get' form worked,
        char Buffer[256]; //store info
        char *Token;
        char youtubeURL[256];
        strncpy(Buffer, query,255);

        Token = strtok(Buffer, "&");
        sscanf(Token, "yturl=%s", youtubeURL);

        printf ("<p>Sorry url decode feature not added so what you see is your input, but url encoded. For example: '%%2F' reppresents a slash '/' </p>");
        printf ("<p>The youtubeURL entered: %s</p>", youtubeURL);
        
        storeURL (youtubeURL); //TODO: save *decoded* url in a file //assumes url is a valid url
    }
    else {
        printf ("<p>Sorry, couldn't get form data. <br>Administrator, check QUERY_STRING.");
    }
    
    printf ("<h3><strong>Thank you for submitting a youtube link. We will listen to it on the raspberry Pi...</strong></h3>");
    
    end_page();
    return 0;
}

//see: https://www.tutorialspoint.com/html/mime_media_types.htm
void header (char *MIMEType) {
    // printf("Content-type:%s\n\n", MIMEType);

    //used system call with storeURL, so means need to use system call with this instead of C printf.
    system("printf 'Content-Type: text/html\n\n'");

}

void start_page (char* title) {
    printf("<html>");
    printf("<head>");
    linkCSS("mystyle.css");
    printf("<title>%s</title>", title);
    printf("</head>");
    printf("<body>");
}

void end_page () {
    printf("</body>");
    printf("</html>");
}

void linkCSS (char* file) {
    printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"%s\"/>", file);
}

