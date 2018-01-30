#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
<<<<<<< HEAD
//Hello
=======
>>>>>>> cc96caa30e9db5e943b8a229a971f6989257ed4f
typedef struct wordNode{   //This is a struct to lay out a basic node in the linked list used later in the program to hold all the "words" in the long string
        char * word;        //The data of this node is the word
        struct wordNode * next; //pointer to next node of LL
}wordNode;  //alias of node is wordNode

//Below are the declarations of all functions and variables that will be used in the program
wordNode * insertNode(char* word, wordNode * head);
wordNode * sort(wordNode * head);
int numTokens;
wordNode * nodeAtIndex(int index, wordNode * head);
void makeSpaces(char * str);
void fillDels(char delims[], char * longString);
int allUsed(int used[]);
int main(int argc, char* argv[])
{
	if (argc == 1)	//if more than 1 argument then return error
	{
		puts("");//if empty input string print empty output string
		return 0;
	}
	else if (argc > 2)
	{
		puts("Error too many inputs");
	}
	char * longString = argv[1]; //input string is the second element in argv
	if (strlen(longString) == 0)//if empty input string print empty output string
	{
		puts("");
		return 0;
	}
    makeSpaces(longString);
    char delims[1] = " ";   //create char array delims with just the space
    char * token=strtok(longString, delims);    //initiate string tokenizer by setting it equal to the first token in the string
    wordNode * head = NULL; //set first node to null
    numTokens = 0;          //this counts the number of "words" in the string
    while(token != NULL)    //while the end of the string is not reached
    {
     if (token == NULL)     //if null token found in middle of the string e.g. two deliminators next to each other, continue to next token
     {
         token = strtok(NULL, delims);
         continue;
     }
     head = insertNode(token, head); //insert word into the LL of all the words in the string
     token = strtok(NULL, delims);  //move to next token
     numTokens++;   //increase number of tokens per iteration
    }
    wordNode * ans = sort(head);    //sort the LL
    wordNode * ptr = ans;           //dummy pointer to traverse LL
    puts("Sorted List:");
    while(ptr != NULL)     //prints out words in the LL
    {
        puts(ptr->word);
        ptr = ptr->next;
    }
}
wordNode * insertNode(char * word, wordNode * head)
{
    wordNode * temp = (wordNode *)malloc(sizeof(wordNode)); //allocates memory in heap to store temp;
    temp->word = word;  //sets temp node's word as the word that is to be inserted into the LL
    temp->next = NULL;
    if (head == NULL) //if no word in LL, make temp node the head
    {
       head = temp;
    }
    else
    {
        wordNode * p = head;
        while(p->next != NULL)//traverse to the last node in the LL
        {
            p = p->next;
        }
        p->next = temp; //place temp at the end of the LL
    }
    return head;
}

wordNode * sort(wordNode * head){
    wordNode * answer = NULL; //this will hold the sorted LL
    wordNode * node1;   //two traversal nodes that will help compare the words in the LL
    wordNode * node2;
    int used[numTokens]; //boolean array that shows if a certain word has already been sorted
    int i;
    for(i = 0; i < numTokens; i++)//initialize all elements of the array to 0
    {
        used[i] = 0;
    }
    while(!allUsed(used)) //loop runs as long as there are unused words in the LL
    {
        int i = 0;
        while(used[i])//move to the closest unused word starting from head
        {
            i++;
        }
        int indexMin = i;//this will hold the index of the word that comes first in the alphabet compared to the used unused words
        int j;
        for(j = i+1; j < numTokens; j++)//loop through LL and find the node whose word is first alphabetically
        {
            node1 = nodeAtIndex(indexMin, head);
            node2 = nodeAtIndex(j,head);
            if(strcmp((*node2).word,(*node1).word) <= 0 && !used[j])//compare indexMin node and other node
            {
                indexMin = j;//if other node's word is smaller then make the other word the smallest
            }
        }
        used[indexMin] = 1;//node at indexMin is now used so change used array element to 1
        wordNode * smallest = nodeAtIndex(indexMin, head);
        answer = insertNode(smallest->word, answer);//insert smallest node into answer LL
    }
    return answer;
}

wordNode * nodeAtIndex(int index, wordNode * head)//get the node at a certain index from the LL filled with all the words
{
    wordNode * ptr = head;//pointer to help traversal
    int i;
    for (i = 0; i < numTokens; i++)
    {
        if(i == index)return ptr;//when i equals the desired index, return the node
        ptr = (*ptr).next;
    }
    return NULL;
}

void makeSpaces(char * longString)
{
    int charind = 0;

    while (longString[charind] != '\0')//while the character does not equal the string terminating character
    {
        if (!isalpha(longString[charind]))longString[charind] = ' ';//if non letter found replace it with a space
        charind++;
    }
}

int allUsed(int used[])
{
    int i;
    for(i = 0; i < numTokens; i++)//loop through the used array and if an index is unused return false
    {
        if(!used[i])return 0;
    }
    return 1;
}