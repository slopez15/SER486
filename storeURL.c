/*
File: storeURL.c
Author: Saul Lopez
Date: 4.1.17
Copyright (c) 2017

Description:
    This file is to obtain URL from formhandleYoutube and store it in a file.
    Also, for soundplay to read the file with the stored url to play that url.

easier to just use some bash then C for writing and reading, if C can get info.
echo url >> store1
cat chum | head -1 //get 1st one
tail -n +2 "chum" > chum.tmp && mv chum.tmp chum //remove 1st one

Tips:
    Based on how I was able to get variables, means that system calls don't go first, but that the prints do.
    Order of logic:
        all code is in order.
        The order of displaying in browser is system prints first before C program prints.
    Debugging
        check /var/log/apache2 for errors why crash

*/
#include <stdio.h> //printf, scanf, FILE, fopen/fclose, fprintf, files & term or stream
#include <string.h> //strings mods, strcpy, strcat, strcmp, 
#include <stddef.h> 
#include <stdlib.h> //exit
#include <ccgi.h>
// #include "ccgi.h"

//define

//methods
void storeURL (char* url);
// char* getNextURL(char* url);


//global vars


//storeURL called by formhandle
void storeURL(char* url) {
    //decode url
    url = CGI_decode_url(url);
    //store urls in urlList.
    char command [256];
    sprintf(command, "URL=%s && sudo echo $URL >> /home/pi/Desktop/cgi-bin/main/bin/urlList && sudo chmod ug+rw /home/pi/Desktop/cgi-bin/main/bin/urlList", url);
    system (command);

    //creating a string for command and executing means I can write url to a file, but cannot get url from a file to store in C, unless I use C to read the file or run strait in bash environment var
    //debugging in page
    system ("echo");
    system ("URLS=`cat /home/pi/Desktop/cgi-bin/main/bin/urlList` && echo '<p>stored in urlList: ' $URLS '</p>' ");
    system ("echo");
    
}










// char* getNextURL (char* url) {
    
//     system ("printf \"urlList content: \" && cat /home/pi/Desktop/cgi-bin/main/bin/urlList");
//     //How to get url from file: get first url in urlList file into variable. Then update file by removing first url in urlList file.
//     system ("export PLAYURL=`cat /home/pi/Desktop/cgi-bin/main/bin/urlList | head -1` && tail -n +2 \"/home/pi/Desktop/cgi-bin/main/bin/urlList\" > /home/pi/Desktop/cgi-bin/main/bin/urlList.tmp && mv /home/pi/Desktop/cgi-bin/main/bin/urlList.tmp /home/pi/Desktop/cgi-bin/main/bin/urlList");
//     system ("printf \"urlList content: \" && cat /home/pi/Desktop/cgi-bin/main/bin/urlList");

//     //obtain url from urlList file and return it to be used by soundplay.c (below from soundplay). use tbd
//     // FILE *fp;
//     // char string [5];
//     // if ( ! ( fp = fopen("/home/pi/Desktop/cgi-bin/main/bin/ISPLAYING", "r") ) ) {
//     //     printf ("Sorry, file not exists.");
//     // }
//     // fgets (string, 5, (FILE*)fp);
//     // fclose(fp);
//     // // convert string to int
//     // checkPlaying = atoi(string);//atoi is 'ascii to integer'

    
    
    
//     //run 'sudo program $PLAYURL' to play song -- do this in soundplay
//     return url;
// }

