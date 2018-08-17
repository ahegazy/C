#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for exit();
#include <errno.h>
#include "textman.h"
#include "replace.h"

static void replace_src(const char * destfname,FILE * src);

int findnReplace(const char * srcfname,char * from,const char * to,const char * FLAGS){
    char buff[255];
    char rep[255];/* replace string */
    int eofcheck;    
    char spchk ,nchar; /* space and next line check ..*/
    
    int wcount = 0; /* word  count */
    int max = 0; /* unlimited */
    char bkup[] = "\0";
    char txtCompare = 0;
    char err = 0;

    FILE *srcfp = NULL; /* srcfp is a pointer to a file structure */
    FILE *tmpfp = NULL;

    srcfp = fopen(srcfname,"r"); /* fopen will return an address of a pointer to a file structure */
    tmpfp = tmpfile(); //fopen(tmpf,"r+");
    if( srcfp == NULL ){
        fclose(tmpfp);
        err = errno;
    }else {

        if (FLAGS[0] == 'b'){
            /* 
            create Backup
            */
            copyText(bkup,srcfname);
            appendText(bkup,".bkup");
            replace_src(bkup,srcfp);
        }

        if(FLAGS[3] == 'i'){
            wordToSmall(from);
        }

        rewind(srcfp); /* moving pointer to the begining */
        if (FLAGS[1] == 'f'){
            max = 1;
        }
        if ( FLAGS[2] == 'l' ){ /* gets only the last occurance of the word. */
            max = 0;
            do
            {
                nchar = 0;
                eofcheck = fscanf(srcfp, "%255s%c", buff,&nchar); /* gets word by word  waits for space or newline or 255 character. */
                txtCompare = cmpText(buff, from);
                if ( txtCompare == 1 ){
                    max++;
                }
            }while(eofcheck == 2);
            rewind(srcfp);
        }

        /* word by word*/
        do
        {
            nchar = 0;
            spchk = 0;
            eofcheck = fscanf(srcfp, "%255s%c%c", buff,&nchar,&spchk); /* gets word by word  waits for space or newline. */
            
            copyText(rep,buff);
            /* heck for small and capital requirment */
            if( FLAGS[3] == 'i'){
                wordToSmall(buff);
            }

            txtCompare = cmpText(buff, from);
            if ( txtCompare == 1 ){
                /* replace the text */
                if( (max == 0) || ((max - 1) == wcount) || ( (FLAGS[1] == 'f') && (wcount == 0) ) ){
                    copyText(rep,to);
                }
                wcount++;
                //rep = to;
            }

            if(nchar == '\n'){
                appendText(rep,"\n");
            }else if (nchar == 0x20){
                appendText(rep," ");
            }else{
                appendText(rep,"");
            }
            /* check if the dumpass has put a space before the newline */
            if(spchk == 0x20){
                appendText(rep," ");
            }else if(spchk == '\n'){
                appendText(rep,"\n");        
            }else{
                fseek(srcfp,-1,SEEK_CUR);
            }

            fputs(rep,tmpfp);
            /* write to another file the whole string */

        }while(eofcheck == 3);
        printf ("found # %d occurrence of the word in %s.\n",wcount,srcfname);

        /* copy tmp file content to another file */

        fclose (srcfp);
        
        replace_src(srcfname,tmpfp);
        fclose (tmpfp);
    }
    return err;
}

static void replace_src(const char * destfname,FILE * srcfp){

    FILE *destfp = NULL; /* destfp is a pointer to a file structure */

    char c;
    destfp = fopen(destfname,"w");
    rewind(srcfp);

    c = fgetc(srcfp);
    while(c != EOF){
        fputc(c,destfp);
        c = fgetc(srcfp);
    }
}

#if 0

int findnReplaceChar(const char * srcfname,char * from,const char * to,const char * FLAGS){
    FILE *srcfp = NULL; /* srcfp is a pointer to a file structure */
    FILE *tmpfp = NULL;

    srcfp = fopen(srcfname,"r"); /* fopen will return an address of a pointer to a file structure */
    tmpfp = tmpfile(); //fopen(tmpf,"r+");
    if( srcfp == NULL ){
        fclose(tmpfp);
        return errno;
    }
    
    if (FLAGS[0] == 'b'){
        /* 
        create Backup
        */
        char bkup[] = "\0";
        copyText(bkup,srcfname); 
        appendText(bkup,".bkup"); /* appending .bkup to the filename. */
        replace_src(bkup,srcfp);
    }

    if(FLAGS[3] == 'i'){
        wordToSmall(from);
    }

    rewind(srcfp); /* moving pointer to the begining */
    char buff[255];
    char rep[255];/* replace string */
    int eofcheck;    
    char spchk ,nchar; /* space and next line check ..*/
    
    int wcount = 0; /* word  count */

    /* char BY char */
    char c = 0;
    int i = 0 ;
    int same = 0;
    int fromCount = counText(from); 
    
    while(c != EOF){
        do {
            c = fgetc(srcfp);
            buff[i] = c;
            if( comapreChar(c,from[i]) == 1 ){
                rep[i] = to[i];
            }else{
                rep[i] = c;
            }
            i++;
        }while(i < fromCount);
     } /**/

    printf ("found # %d occurrence of the word in %s.\n",wcount,srcfname);

    /* copy tmp file content to another file */

    fclose (srcfp);
    
    replace_src(srcfname,tmpfp);
    fclose (tmpfp);
    return 0;
}
#endif