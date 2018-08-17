#include<stdio.h>
#include<string.h>
#include<stdlib.h> // for exit();
#include <errno.h>
#include "replace.h"
#include "textman.h"

int main(int argc, char *argv[]){
    char FLAGS[4] = {0,0,0,0}; /* -b backup -f first occur  -l last occur -i ignore case */
    char * FLAGNAMES[4] = {"-b","-f","-l","-i"};

    char * FILES[100] = {};
    int filesc = -1; /* files count */
    char * from = NULL;
    char * to = NULL;
    int chk = 0; /* check file replacement success */
    int i; /* [argv] arguments loop , [replace] loop */
    char txtCompare = 0; 
    if(argc < 5){
        fprintf(stderr,"No suffecient arguments\nPlease use `replace OPT <from> <to> -- <filename> [<filename>]*\nExitting. \n");
        exit(1); 
    }else if(argc > 99){
        fprintf(stderr,"Too many arguments.\n");
        exit(2);
    }
    for(i=1;i<argc;i++){
        if(filesc != -1){
            FILES[filesc] = argv[i];
            filesc++;
            continue;
        }

        if( cmpText(argv[i],"-b") == 1 ){
            FLAGS[0] = 'b';
        }else if( cmpText(argv[i],"-f") == 1 ){
            FLAGS[1] = 'f';
        }else if( cmpText(argv[i],"-l") == 1 ){
            FLAGS[2] = 'l';
        }else if( cmpText(argv[i],"-i") == 1 ){
            FLAGS[3] = 'i';
        }else if( cmpText(argv[i],"--") == 1 ){
            filesc = 0;
        }else{
            if(from == NULL){
                from = argv[i];
            }else if(to == NULL ){
                to = argv[i];
            }
        }
        
    }

    #if 0
        /* useless statement handeled before arguments' loop. */
        if( (from == NULL)|| (to == NULL) || FILES[0] == NULL ){
            fprintf(stderr,"No suffecient arguments\nPlease use `replace OPT <from> <to> -- <filename> [<filename>]*`. \n");
            exit(1); 
        }
    #endif

    for(i=0;i<filesc;i++){
        chk = findnReplace(FILES[i],from,to,FLAGS);
        if(chk != 0){
            fprintf(stderr,"Error %d opening file '%s' : %s \n",chk,FILES[i],strerror( chk ));
            /*  
                will continue to other files. no need to exit 
            */
            #if 0
            exit(chk);
            #endif
        }
    }

    return 0;
}