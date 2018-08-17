#ifndef TEXT_MANIPULATION

#define TEXT_MANIPULATION

void wordToSmall(char word[]);
char charToSmall(char c);
int comapreChar(char c1, char c2);
int cmpText( const char word1[], const char word2[]);
void appendText (char * dest, const char * src );
void copyText (char * dest, const char * src );
int counText(const char * text);

#endif