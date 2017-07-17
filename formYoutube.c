/*
File: formYoutube.c
Author: Saul Lopez
Date: 4.1.17
Copyright (c) 2017

Description:
The program just prints out a html file.
This html file contains a form that uses GET method to take the data to a form handler.
*/

#include <stdio.h>
int main (void){
    printf("Content-Type: text/html \n\n");
    printf (" "
        "<!DOCTYPE html><html><head> <link rel=\"stylesheet\" type=\"text/css\" href=\"mystyle.css\"> <title>Raspberry Pi powered Radio Station! Early Bird.</title></head><body> <!--input received method. post from stdin. get from QUERY_STRING--> <!--just making it complex to pick from.--> <!--Later, form used to obtain file uploads form users, an/or text styled as a youtube link--> <!--files received added to list and/or have media player play stright from youtube url.--> <form action='formhandleYoutube' method='GET'> Please Enter a youtube url: <input type='text' name='yturl' /><br><br> <input type='submit' value='Submit' /> </form></body></html>"
    );
    
    printf("\n");
    return 0;
}