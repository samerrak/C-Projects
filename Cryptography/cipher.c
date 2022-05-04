//Name: Samer Abdulkarim 
//Student #:260964596

#include <stdio.h> //libraries
#include <stdlib.h>
#include <string.h>
#include <math.h>

char inputData[500];
char matrix[500][500]; //global variables

void errorMsg(char *msg)
{
    printf("%s\n", msg); //based on inputted message
    printf("Program Syntax:\n./cipher SWITCH KEY LENGTH < FILENAME\n");
    printf("Legal usage examples:\n./cipher -e 10 100 < filename.txt\n./cipher -d 10 200 < filename.e\n");

}

void encrypt(int key, int length)
{
    int i,y;
    int z=0;

    for (i=0; i<length; i++)
    {
        char c = getc(stdin); //gets stdin from file  
        inputData[i] = c;   //stores our data in inputData
    }

    inputData[i] = '\0';
    
    //print out columns then rows
    //[row][columns]

    int modkey;

    for(y=0; y<length; y++) //loop 
    {
        modkey = (y % key); //checks the mod of the y % key if it equals zero then we go to a new row and start writing their
        
        if (y>0){
        if (modkey == 0)
        {
            z++; //increases row if everything is filled
        }}

        matrix[z][modkey] = inputData[y]; //stores inputData
        
    }

    matrix[z][key] = '\0';
    
    for (int f = 0; f<key; f++){ //prints column values then rows
        for (int j = 0; j<z+1; j++){
            printf("%c", matrix[j][f]);
        }
    }

    //two for loops one going through the rows and the next columns
}
void decrypt(int key, int length)
{
    int lk = length/key;
    int lengkey = lk +1; // ceils the value
    int i,y;
    int z=0;

    for (i=0; i<length; i++)
    {
        char c = getc(stdin); //gets standard input
        inputData[i] = c;
    }

    inputData[i] = '\0';
    int modkey;

    for(y=0; y<length; y++) //loop 
    {
        modkey = (y % lengkey); //checks the mod of the y % lengkey if it equals zero then we go to a new row 
        
        if (y>0){
        if (modkey == 0)
        {
            z++; //increases row if everything is filled
        }}

        matrix[modkey][z] = inputData[y]; //stores inputData   
    }

    for (int f = 0; f<lengkey; f++){
        for (int j = 0; j<key; j++){  //print function opposite to encrypt
            printf("%c", matrix[f][j]);
        }
    }
}



int main(int argc, char *argv[])
{
    if ((argc != 4)) // arguments start at 1 so if theres 3 check if theres 4 
    {
         errorMsg("Wrong number of arguments, please input 3 arguments");
         exit(EXIT_FAILURE); // exit if not
    }

    int x = strcmp(argv[1],"-d"); //compares strings if true == 0
    //printf("%s %s %s %s %d\n", argv[1], argv[2], argv[3], argv[4], x);
    int length = atoi(argv[3]); // converts char argument to int
    int key = atoi(argv[2]);

    if (strcmp(argv[1],"-e")!=0 && strcmp(argv[1],"-d")!=0) //case if both switches are not provided
    {
        errorMsg("Wrong switch, use -e or -d");
        exit(EXIT_FAILURE);
        
    }
    if (length > 500) //case if length exceeds 500
    {
        errorMsg("Length value exceeds limit of 500");
        exit(EXIT_FAILURE);
    }
    if (key >= length) //case if key is equal or exceeding length
    {
        errorMsg("Key value exceeds or equals length value");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1],"-e")==0) //call encrypt if arg1 -e
    {
         encrypt(key,length);
    }

     else if (strcmp(argv[1],"-d")==0) //call encrypt if arg1 -d
     {
         decrypt(key,length);
     }

     return 0;


}


