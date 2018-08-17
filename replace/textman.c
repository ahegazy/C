#include "textman.h"

void wordToSmall(char word[]){
    int i=0;
    char c;
    do{
        c = word[i];
        word[i] = charToSmall(c);
        i++;
    }while(c != '\0');
    return;
}

char charToSmall(char c){
    if( (c >= 'A') && (c <= 'Z') ){
        c += 32;
    }
    return c;
}

int comapreChar(char c1, char c2){
    int same = 0;
    if(c1 == c2 ){
        same = 1;
    }
    return same;
}

int cmpText(const char word1[], const char word2[]){

    int exist = 1; /* 1 means two words are the same .*/
    int i=0;
    char c1,c2;
    do{
        c1 = word1[i];
        c2 = word2[i];
        if ( comapreChar(c1,c2) == 0 ) {
            exist = 0;
            break;
        }else {
            /* DO NOTHING */
        }
        i++;
    }while(c1 != '\0' && c2 != '\0');
    return exist;
}


void appendText (char * dest, const char * src ){
    unsigned char i = 0,j =0;
    char c;
    /* calculate string length of dest */
    while( dest[i] != '\0')
        i++;
    do{
        c = src[j];
        dest[i] = c;
        j++;
        i++;
    }while( c != '\0');
}

void copyText (char * dest, const char * src ){
    unsigned char i = 0;
    char c;
    /* calculate string length of dist */

    do{
        c = src[i];
        dest[i] = c;
        i++;
    }while( c != '\0');
}

int counText(const char * text){
    char c;
    int count = 0;
    do{
        c = text[count];
        count++;
    }while( c != '\0');
    return count;
}