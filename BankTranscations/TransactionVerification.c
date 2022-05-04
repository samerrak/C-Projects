//Name: Samer Abdulkarim
//Student Number: 260964596

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//node struct like java linkedlist has fields
struct ACCOUNT
{
   int accountNumber;
   double startingBalance;
   double endingBalance;
   struct ACCOUNT *next;
};

//creates a reverse order linked list.
struct ACCOUNT* addNode(struct ACCOUNT *ptr, int aNumber, double sBalance, double eBalance){
    struct ACCOUNT *temp = (struct ACCOUNT*)malloc(sizeof(struct ACCOUNT));
    if (temp == NULL){
        return NULL;
    }
    temp->accountNumber = aNumber;
    temp->startingBalance = sBalance;
    temp->endingBalance = eBalance;

    if(ptr == NULL){
        temp->next=NULL;
    }
    else{
        temp->next=ptr;
    }
    return temp;
};


//sorts the elements of the linked list instead of swapping the nodes, insert sort could be used.
void sortLinkedList(struct ACCOUNT *head){
    struct ACCOUNT *curr = head;
    struct ACCOUNT *currNext = NULL;
    int aValue;
    float sBL, eBL;

    while(curr!=NULL){
        currNext = curr->next;
        while(currNext!=NULL){
            if (curr->accountNumber > currNext->accountNumber){
                aValue = curr->accountNumber;
                sBL = curr->startingBalance;
                eBL = curr->endingBalance;
                curr->accountNumber = currNext->accountNumber;
                currNext->accountNumber = aValue;
                curr->startingBalance = currNext->startingBalance;
                currNext->startingBalance = sBL;
                curr->endingBalance = currNext->endingBalance;
                currNext->endingBalance = eBL;


            }
            currNext = currNext->next;
        }
        curr=curr->next;
    }

}

//helper function to check if node values are correct
void printNodes(struct ACCOUNT *head){
    while (head != NULL){
        printf("%d ", head->accountNumber); printf("%f ", head->startingBalance); printf("%f \n", head->endingBalance);
        head = head->next;
    }
}

int main(int argc, char *argv[])
{
    if ((argc != 3))
    {
         printf("Wrong number of arguments!\nProgram syntax:\n./tv STATE TRANSACTIONS\nLegal usage examples:\n./tv state.csv transaction.csv\n./tv ../state.csv /data/log/transaction.csv\n");
         exit(1); // terminate with errorcode 1 if arguments less than 2.
    }

    FILE *preSpend = fopen(argv[1],"rt");
    FILE *postSpend = fopen(argv[2],"rt");

    //checks if we are unable to open the files.
    if (preSpend == NULL) {
        printf("Unable to open filename %s\n", argv[1]);
        exit(2);}
    else if (postSpend == NULL){
        printf("Unable to open filename %s\n", argv[2]);
        exit(2);}


    char m,z,c;
    m = fgetc(preSpend);
    z = fgetc(postSpend);
    char gArray[200], gArray1[200];
    char array[3000];
    char array1[3000];
    int aCounter=0;
    int i,j,k,d;
    int i1,j1,k1,d1;
    char aNum[2000], sBalance[2000], eBalance[2000];
    struct ACCOUNT *head = NULL; //initializes head struct;
    int tempAcc;
    float tempSBalance, tempEBalance;
    char b = ',';
    char p = '\n';
    int tempAcc1;
    char mode[100];
    char md;
    char aNum1[2000], absVal[2000];
    float absVal1;



    //checks if state.csv is empty
    if(m==EOF && z!=EOF)
    {
        printf("File %s is empty. Unable to validate %s.\n", argv[1], argv[2]);
        exit(3);
    }

    //if both files are empty then nothing happens so return 0
    if(m==EOF && z==EOF){
        return 0;
    }

    //this just stores the first line of both because we dont want to iterate through them.
    if(!feof(preSpend))
    {
        fgets(gArray, 100, preSpend);
         //reads the strings of the file
    }

    if(!feof(postSpend))
    {
        fgets(gArray1, 100, postSpend);
        //reads the strings of the file
    }

    if (m!=EOF){


        while(!feof(preSpend))
        {
            //the following gets the string values of each entry by checking if there's a comma and skipping it
            fgets(array,2000,preSpend);
            int x1 = 0;
            for (i = 0; array[i] != b; i++)
                aNum[i] = array[i];
            i++;
            aNum[i]='\0';
            tempAcc = atoi(aNum);

            for (j=0; array[i]!=b;i++, j++)
            {
                sBalance[j] = array[i];
            }
            i++;
            sBalance[j]='\0';
            tempSBalance = atof(sBalance);


            for (k=0; array[i]!=p;i++, k++)
            {

                eBalance[k] = array[i];
            }

            i++;
            eBalance[k]='\0';
            tempEBalance = atof(eBalance);


            //iterates through list to check duplicates
            struct ACCOUNT *curr = head;
            while(curr!=NULL){
                if (curr->accountNumber == tempAcc)
                {
                    x1++;

                }
                curr=curr->next;
            }


            if (head != NULL && x1>0) //head != NULL && head->accountNumber==tempAcc
            {
                printf("Duplicate account number [account, start, end]: %d %.2f %.2f\n", tempAcc, tempSBalance, tempEBalance);
            }
            else if (tempAcc!=0){
                head = addNode(head, tempAcc, tempSBalance, tempEBalance);

            }

            aCounter++;

        }

        sortLinkedList(head);
        //printNodes(head);
        fclose(preSpend); //close the file
    }

    if(z!=EOF) {

        while (!feof(postSpend)) {
            fgets(array1, 2000, postSpend);
            //follows the same method as the first file but stores a char instead now
            for (i1 = 0; array1[i1]!= b; i1++)
                aNum1[i1] = array1[i1];
            i1++;
            aNum[i1] = '\0';
            tempAcc1 = atoi(aNum1);

            for (j1=0; array1[i1]!=b;i1++, j1++)
            {
                mode[j1] = array1[i1];
                md = mode[j1];
            }
            i1++;
            //j1++;
            mode[j1]='\0';

            for (k1=0; array1[i1]!=p;i1++, k1++)
            {

                absVal[k1] = array1[i1];
            }

            i1++;
            d1=0;
            absVal[k1]='\0';
            absVal1= atof(absVal);



            //parses through each node to check if balance is less than zero
            struct ACCOUNT *curr = head;
            while(curr!=NULL){
                if (curr->accountNumber == tempAcc1)
                {
                    if (md == 'd'){
                        curr->startingBalance = curr->startingBalance + absVal1;
                    }
                    else if (md == 'w'){
                        float tempi = curr->startingBalance;
                        curr->startingBalance = curr->startingBalance - absVal1;
                        if (curr->startingBalance < 0 )
                        {
                            printf("Balance below zero error (account,mode, transaction, startingBalance before): %d %c %.2f %.2f\n", tempAcc1, md, absVal1, tempi);
                            curr->startingBalance = 0;

                        }
                    }
                    d1++;

                }
                curr=curr->next;
                //d1=0;
                }

            if (d1 == 0) {
                if(tempAcc1!=0) { //checks if account is there or not by using a counter d1
                    printf("Account not found (account, mode,amount): %d %c %.2f\n", tempAcc1, md, absVal1);
                }
            }
        }
        //printNodes(head);
        fclose(postSpend); //closes file
    }

    //parses through the list and checks if each variable exists

    struct ACCOUNT *curr = head;
    while (curr != NULL){
        float fr;
        fr = curr->startingBalance-curr->endingBalance;
        if (fr < 0)
        {
            fr= fr * -1;
        }
        if (fr > 0.005)
        {
            printf("End of day balances do not agree (account, starting, ending): %d %.2f %.2f\n", curr->accountNumber, curr->startingBalance, curr->endingBalance);
        }

        curr = curr->next;
    }

    free(head);
    free(curr);
    return 0;
}
