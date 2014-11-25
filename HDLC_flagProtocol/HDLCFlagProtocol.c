/*  ENGR 476 ASSIGNMENT NO. 2   SPRING 2013
    
    File: HDLCFlagProtocol.c
    By: Marcian Diamond
    Date: 2. 26. 2013

    Compile:    cc HDLCFlagProtocol.c
    Usage:      ./a.out
    System:     MS-DOS console

    Description:    This program accepts keyboard data and detects HDLC flags.
                    When a flag is first detected, keystrokes are printed to the
                    console.  Once the flag is received again, console will no 
                    longer print keystrokes.  This program runs on DOS environments
                    and utilizes conio.h to capture screen output.
*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<string.h>
#include<stdbool.h>

char flag[] = "01111110";

int capt(void){
    
    char flagIn[9] = " ";
    char ch;
    int i = 0;
    bool flagBegin =  false;

    while(1){
        strcpy(flagIn, " ");
        i = 0;
        flagBegin = false;
        ch = getche();
        
        if(ch == '0'){
            flagIn[i++] = ch;
            flagBegin = true;
            
            while(flagBegin == true){
                flagIn[i] = getche();
                if(flagIn[i++] != '1' && i < 7){
                    break;
                }
                if(i == 7){
                    flagIn[i] = getche();
                    if(strcmp(flagIn, flag) == 0){ 
                       printf("%s", "\nHDLC flag detected! Data capture stopped.\n");
                       return 0;
                    }else{
                        flagBegin = false;
                        break;
                    } 
                }
            }                
        }
    }    
    return 0;
}

int main(void){

    char input[9] = " ";
    char ch;
    int i = 0;
    bool flagBegin = false;

    while(1){
        strcpy(input, " ");
        flagBegin = false;
        i = 0; //reset index
        ch = getche();
        if(ch == '0'){
            flagBegin = true;
            input[i++] = ch;

            while(flagBegin == true){
                input[i] = getche();
                
                if(input[i++] != '1' && i < 7){
                    break;
                }
                if(i == 7){
                    input[i] = getch();
               
                    if(strcmp(input, flag) == 0){ 
                       printf("%s\n", "HDLC flag detected! Printing keystrokes to console!\n");
                       capt();
                       flagBegin = false;
                    }else{
                        flagBegin = false;
                    } 
                }
            }                
        }               
    }
    return 0;
}



