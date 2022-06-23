/****************************String parsing function*********************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char *str;
    unsigned num;
}DICT;

char parseString(int start, int end, char *input, char  *substring){
    int len = end-start;
    printf("start: %d, end: %d\n", start, end);
    int j=0;
    for(int i=start; i <=end ; i++){
        substring[j] = input[i];
        j++;
    }
    substring[j] = '\0';
    return substring;
}

int matchDict(char *input, DICT dict[], int structLen, int *output){
    int i=0;
    int start = i;
    int end = 0;
    char *substring;
    int subslen=0;
    int count=0;
    int out=0;
    int substringCount=0;
    while(input[i]!='\0'){
        if(input[i]==',') {
            end = i-1;
            subslen = end-start;
            substring = malloc(sizeof(char)*subslen);
            parseString(start, end, input, substring);
            substringCount++;
            
            printf("substring: %s\n", substring);
            
            for(int k=0; k<structLen;k++){
                out = strcmp(substring, dict[k].str);
                if(out==0) {
                    output[count] = dict[k].num;   
                    count++;
                    break;
                }
            }
            if(out!=0){
                output[count] = 0xff;   
                count++;
            }
            start = i+1;
            free(substring);
        }
        i++;
    }
     //Last substring which is not followed by comma ','
     end = strlen(input);
     substring = malloc(sizeof(char)*subslen);
     parseString(start, end, input, substring);
     substringCount++;
     printf("substring: %s\n", substring);
     free(substring);
     return substringCount;
}

int main () {
   char str[] = "aaa,bbb,ccc,ddd,eee,dsa";
   DICT dictionary[2] = {{"ccc", 0x03}, 
                         {"ddd", 0x04}};
   
   int size = sizeof(dictionary)/sizeof(dictionary[0]);
   int *output = (int *)malloc(sizeof(int)*(strlen(str)));
   int substringCount = matchDict(&str, dictionary, size, output);
   
   for(int i=0; i<substringCount; i++){
       printf("%d\n", output[i]);
   }
   return(0);
}

