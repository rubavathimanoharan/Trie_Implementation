#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define the character size
#define N 26

// Data structure to store a Trie node
struct Trie
{
    char data;
    int isLeaf; // 1 when the node is a leaf node
    struct Trie *alpha[N];
};

typedef struct Trie trie;
// Function that returns a new Trie node
trie *newTrieNode()
{
    trie *node = (trie *)malloc(sizeof(trie));
    node->isLeaf = 0;

    for (int i = 0; i < N; i++)
    {
        node->alpha[i] = NULL;
    }

    return node;
}

// Iterative function to insert a string into a Trie
void insert(trie *head, char *str)
{
    // start from the root node
    trie *curr = head;

     int count=0;
char *s=str;
    while (*str)
    {
         
        int index = (*str|('A'^'a'))-'a';
        
        // create a new node if the path doesn't exist
        if (curr->alpha[index] == NULL)
        {
            curr->alpha[index] = newTrieNode();
            count--;
        }

        // go to the next node
        curr = curr->alpha[index];
        curr->data = *str;

        count++;
        // move to the next character
        str++;
    }
   
    if(count==strlen(s))
    printf("\nThis word is already inserted in the trie");
    

    // mark the current node as a leaf
    curr->isLeaf = 1;
}

// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int search(trie *head, char *str)
{
    // return 0 if Trie is empty
    if (head == NULL)
    {
        return 0;
    }

    trie *curr = head;
    while (*str)
    {
         int index = (*str|('A'^'a'))-'a';
        // go to the next node
        curr = curr->alpha[index];

        // if the string is invalid (reached end of a path in the Trie)
        if (curr == NULL)
        {
            return 0;
        }

        // move to the next character
        str++;
    }

    // return 1 if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}

// Returns 1 if a given Trie node has any children
int hasChildren(trie *curr)
{
    for (int i = 0; i < N; i++)
    {
        if (curr->alpha[i])
        {
            return 1; // child found
        }
    }

    return 0;
}

// Recursive function to delete a string from a Trie
int deletion(trie **curr, char *str)
{
    // return 0 if Trie is empty
    if (*curr == NULL)
    {
        printf("TRIE is empty");
        return 0;
    }

    // if the end of the string is not reached
    if (*str)
    
    {
         int index = (*str|('A'^'a'))-'a';
        // recur for the node corresponding to the next character in
        // the string and if it returns 1, delete the current node
        // (if it is non-leaf)
        if (*curr != NULL && (*curr)->alpha[index] != NULL &&
            deletion(&((*curr)->alpha[index]), str + 1) &&
            (*curr)->isLeaf == 0)
        {
            if (!hasChildren(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    // if the end of the string is reached
    if (*str == '\0' && (*curr)->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!hasChildren(*curr))
        {
            free(*curr); // delete the current node
            (*curr) = NULL;
            return 1; // delete the non-leaf parent nodes
        }

        // if the current node is a leaf node and has children
        else
        {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            (*curr)->isLeaf = 0;
            return 0; // don't delete its parent nodes
        }
    }

    return 0;
}

void print_trie(trie *root)
{
    // Prints the nodes of the trie

    if (!root)
        return;
    trie *temp = root;
    //  printf("%c -> ", temp->data);
    for (int i = 0; i < N; i++)
    {
        if (temp->alpha[i] != '\0')
            printf("%c -", root->alpha[i]->data);
        print_trie(temp->alpha[i]);
    }
}

int main()
{
    trie *head = newTrieNode();
    int ch, res;
    do
    {

        char *word = malloc(sizeof(char) * N);
        int result, len;
        printf("\n\n\n");
        printf("\n***********   TRIE IMPLEMENTAION   ***********");
        printf("\n\n1. Insert into trie \n2. Search from trie \n3. Delete from trie \n4. Traversal \n5. Exit \n\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\nEnter the word to be inserted: ");
            scanf("%s", word);
            len = strlen(word);
            word = realloc(word, sizeof(char) * len);
            insert(head, word);
            printf("\nInsertion successful!");
            break;
        case 2:
            printf("\nEnter the word to be searched: ");
            scanf("%s", word);
            len = strlen(word);
            word = realloc(word, sizeof(char) * len);
            result = search(head, word);
            if (result == 1)
                printf("\nSearch successful!\nThe word is present in the trie.");
            else
                printf("\nSearch unsuccessful!\nThe word is not present in the trie!");
            break;

        case 3:
        
            printf("\nEnter the word to be deleted: ");
            scanf("%s", word);
            len = strlen(word);
            word = realloc(word, sizeof(char) * len);
            result = search(head, word);
           
            if (result == 1)
            {
                deletion(&head, word);
                //if(res==1)
                printf("\nDeletion successful!");
            }
            else
                printf("\nDeletion unsuccessful!\nThe word is not present in the trie!");
            break;

        case 4:
            printf("Print the nodes in the trie\n");
            print_trie(head);
            break;
        case 5:
            exit(1);
        default:
            printf("Please enter a valid choice");
            break;
        }
    } while (ch <= 4); 

    return 0;
}
