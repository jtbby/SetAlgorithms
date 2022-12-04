/* Justin Thomas G01336576
    CS 262, Lab Section 203
    Project 3
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 50

typedef struct node{
    char String[SIZE];
    struct node * next;
}node_s; /*node_s = node string*/

int strcmpa(char *s1, char *s2){
    
    while (*s1 && tolower(*s1) == tolower(*s2)){
        s1++;
        s2++;
    }

    return tolower(*s1) - tolower(*s2);
}

void addNode(node_s **array, int setNumber, char string[SIZE]) {
    
    node_s *newNode = malloc(sizeof(node_s));
    strcpy(newNode->String, string);
    newNode->next = NULL;

    if (array[setNumber] == NULL) {
        array[setNumber] = newNode;
        return;
    }


    if (strcmpa(newNode->String, array[setNumber]->String) < 0) { /* Insert at beginning*/
            newNode->next = array[setNumber];
            array[setNumber] = newNode;
            return;
    }

    node_s *prev = NULL;
    node_s *current = array[setNumber];

    while(current->next != NULL) { /*Insert at middle*/

        if(strcmpa(newNode->String, current->String) == 0) {
            free(newNode);
            return;
        }
        
        if(strcmpa(newNode->String, current->String) < 0) {
            prev->next = newNode;
            newNode->next = current;
            return;
        }
        prev = current;        
        current = current->next;

    }
        current->next = newNode; /*Insert at end*/
}

void printOther(node_s **array, int setNumber) {/*print for union/intersection/symmetric*/
    node_s *current;

    if (array[setNumber] == NULL) {
        printf("{}\n", setNumber);
        return;
    }

    current = array[setNumber];

    printf("{");

    while(1) {
        if(current->next == NULL) {
            printf("%s}\n", current->String);
            break;
        }
        printf("%s, ", current->String);
        current = current->next;
    }
}

void print(node_s **array, int setNumber) {
    node_s *current;

    if (array[setNumber] == NULL) {
        printf("Set %d: {}\n", setNumber);
        return;
    }

    current = array[setNumber];

    printf("Set %d: {", setNumber);

    while(1) {
        if(current->next == NULL) {
            printf("%s}\n", current->String);
            break;
        }
        printf("%s, ", current->String);
        current = current->next;
    }
}

void clear(node_s **array, int setNumber) {

    node_s *current = array[setNumber];
    node_s *next = NULL;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    array[setNumber] = NULL; 

}

void removeNode(node_s **array, int setNumber, char string[SIZE]) {
    node_s *temp = array[setNumber], *prev = NULL;


    if(string == NULL) {
        return;
    }

    if(temp->String == string) {
        array[setNumber] = temp->next;
        free(temp);
        return;
    }

    while(temp != NULL && temp->String != string) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;
    free(temp);

}
void printSets(node_s **array, int sets) {
    node_s *current;
    int i;


    for(i = 0; i < sets; i++) {
        
        if(array[i] == NULL) {
            continue;
        }

        current = array[i];
        printf("Set %d: {", i);
        
        while(1) {
            if(current->next == NULL) {
                printf("%s}\n", current->String);
                break;
            }
            printf("%s, ", current->String);
            current = current->next;
            }

    }
}

void copy(node_s **array, int copyTo, int copyFrom) {
    node_s *current = array[copyFrom];
    while(current != NULL) {
        addNode(array, copyTo, current->String);
        current = current->next;
    }
}


void unionSets(node_s **array, int first, int second) {
    int i;
    node_s **temp, *current;
    temp = (node_s**)malloc(1 * sizeof(node_s));
    temp[0] = NULL;

    current = array[first];

    while (current != NULL) {
        addNode(temp,0,current->String);
        current = current->next;
    }

    current = array[second];

    while (current != NULL) {
        addNode(temp,0,current->String);
        current = current->next;
    }
    printOther(temp,0);
    
    clear(temp,0);
    free(temp);


}
void intersections(node_s **array, int first, int second) {
    node_s **temp, *current1, *current2;
    temp = (node_s**)malloc(1 * sizeof(node_s));
    temp[0] = NULL;

    current1 = array[first];
    current2 = array[second];

    
    
    while(current1 != NULL) {
        while (current2 != NULL) {
            if (strcmpa(current1->String, current2->String) == 0) {
                addNode(temp, 0, current1->String);
            }
            current2 = current2->next;
        }
    current1 = current1->next;
    current2 = array[second];
    }

    printOther(temp,0);
    clear(temp,0);
    free(temp);
    
}

void symmetricDifference(node_s **array, int first, int second) {
    int found;
    node_s **temp, *current1, *current2;
    temp = (node_s**)malloc(1 * sizeof(node_s));
    temp[0] = NULL;

    current1 = array[first];
    current2 = array[second];

    while(current1 != NULL) {/*checks if second list has any duplicates as the first then adds the non-duplicates*/
        found = 0;
        while(current2 != NULL) {
            if(strcmpa(current1->String, current2->String) == 0) {
                found = 1;
                break;
            }
            current2 = current2->next;
        }
        if(found == 1) {
            current2 = array[second];
            current1 = current1->next;
            continue;
        }
        else {
            addNode(temp,0,current1->String);
            current2 = array[second];
            current1 = current1->next;
        }
    }

    current1 = array[first];
    current2 = array[second];

    while(current2 != NULL) {/*checks if first list has any duplicates as the second then adds the non-duplicates*/
        found = 0;
        while(current1 != NULL) {
            if(strcmpa(current1->String, current2->String) == 0) {
                found = 1;
                break;
            }
            current1 = current1->next;
        }
        if(found == 1) {
            current1 = array[first];
            current2 = current2->next;
            continue;
        }
        else {
            addNode(temp,0,current2->String);
            current1 = array[first];
            current2 = current2->next;
        }
    }

    printOther(temp,0);
    clear(temp,0);
    free(temp);
}


int main() {
    int setNumber, sets, i, copyFrom, copyTo, first, second;
    char inBuf[SIZE], input, string[SIZE];
    node_s **array;
    
    printf("How many sets do you want?\n");
    fgets(inBuf, SIZE, stdin);
    sscanf(inBuf, "%d", &sets);

    array = (node_s**)malloc(sets * sizeof(node_s));

    for(i = 0; i < sets; i++) {
       array[i] = NULL;
    }
    

    while (input != 'q' && input != 'Q') {
        printf("***** Menu Options *****\n");
        printf("Add String:\t      a or A\n");
        printf("Remove String:\t      r or R\n");
        printf("Union:\t\t      u or U\n");
        printf("Intersection:\t      i or I\n");
        printf("Symmetric Difference: s or S\n");
        printf("Copy:\t\t      c or C\n");
        printf("Clear:\t\t      z or Z\n");
        printf("Print Set: \t      P\n");
        printf("Print All Sets:\t      p\n");
        printf("Quit:\t\t      q or Q\n");
        fgets(inBuf, SIZE, stdin);
        sscanf(inBuf, "%c", &input);

        if(input == 'a' || input == 'A') {
            
            do {
                printf("Enter set to add to\n");
                fgets(inBuf, SIZE, stdin);
                sscanf(inBuf, "%d", &setNumber);

                if (setNumber < sets && setNumber >= 0) {
                    break;
                }
                printf("Error! Set number out of range\n");
            }while (setNumber >= sets || setNumber < 0);

            printf("Enter a string to add\n");
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf,"%s", &string);


            addNode(array, setNumber, string);
        }

        if(input == 'r' || input == 'R') {

            do {
                printf("Enter a set to remove from\n");
                fgets(inBuf, SIZE, stdin);
                sscanf(inBuf, "%d", &setNumber);

                if (setNumber < sets && setNumber >= 0) {
                    break;
                }
                printf("Error! Set number out of range\n");
            }while (setNumber >= sets || setNumber < 0);

            printf("Enter the string to remove\n");
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf, "%s", &string);

            removeNode(array, setNumber, string);
        }

        if(input == 'P') {

            do {
                printf("Enter set to print\n");
                fgets(inBuf, SIZE, stdin);
                sscanf(inBuf, "%d", &setNumber);

                if (setNumber < sets && setNumber >= 0) {
                    break;
                }
                printf("Error! Set number out of range\n");
            }while (setNumber >= sets || setNumber < 0);

            print(array, setNumber);
        }

        if(input == 'p') {
            printSets(array, sets);
        }

        if(input == 'c' || input == 'C') {
            printf("Which set do you want to copy to?\n");
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf, "%d", &copyTo);

            printf("Which set do you want to copy from?\n");
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf, "%d", &copyFrom);

            copy(array, copyTo, copyFrom);

        }

        if(input == 'u' || input == 'U') {
            printf("Which is the first set you want to union with\n");
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf, "%d", &first);

            printf("Which is the second set you want to union with\n");
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf, "%d", &second);

            unionSets(array, first,second);
        }

        if(input == 'i' || input == 'I') {
            printf("Which is the first set you want to intersect with\n");
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf, "%d", &first);

            printf("Which is the second set you want to intersect with\n");
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf, "%d", &second);

            intersections(array,first,second);
        }

        if(input == 's' || input == 'S') {
            printf("Which is the first set you want to find the symmetric difference of\n");
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf, "%d", &first);

            printf("Which is the first set you want to find the symmetric difference of\n");
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf, "%d", &second);

            symmetricDifference(array,first,second);
        }
        else {
            printf("Invalid menu option, please select valid option:\n");
            continue;
        }

    }

    for(i = 0; i < sets; i++) {
        clear(array, i);
    }

    free(array);
    



    return 0;
}