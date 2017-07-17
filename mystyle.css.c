#include <stdio.h>
#include <stdlib.h>
#include "pageFormatCGI.c"

//methods

//code
int main (){
    printf("Content-Type: text/css \n\n");
    cgiFriendly ("mystyleOriginal.css");

    return 0;
}



