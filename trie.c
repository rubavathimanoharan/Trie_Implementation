#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define the character size
#define CHAR_SIZE 26

// Data structure to store a Trie node
struct Trie
{
    char data;
    int isLeaf; // 1 when the node is a leaf node
    struct Trie *character[CHAR_SIZE];
};

// Function that returns a new Trie node
struct Trie *getNewTrieNode()
{
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->isLeaf = 0;

    for (int i = 0; i < CHAR_SIZE; i++)
    {
        node->character[i] = NULL;
    }

    return node;
}

// Iterative function to insert a string into a Trie
void insert(struct Trie *head, char *str)
{
    // start from the root node
    struct Trie *curr = head;

    while (*str)
    {
        // create a new node if the path doesn't exist
        if (curr->character[*str - 'a'] == NULL)
        {
            curr->character[*str - 'a'] = getNewTrieNode();
        }

        // go to the next node
        curr = curr->character[*str - 'a'];
        curr->data = *str;

        // move to the next character
        str++;
    }

    // mark the current node as a leaf
    curr->isLeaf = 1;
}

// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int search(struct Trie *head, char *str)
{
    // return 0 if Trie is empty
    if (head == NULL)
    {
        return 0;
    }

    struct Trie *curr = head;
    while (*str)
    {
        // go to the next node
        curr = curr->character[*str - 'a'];

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
int hasChildren(struct Trie *curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i])
        {
            return 1; // child found
        }
    }

    return 0;
}

// Recursive function to delete a string from a Trie
int deletion(struct Trie **curr, char *str)
{
    // return 0 if Trie is empty
    if (*curr == NULL)
    {
        return 0;
    }

    // if the end of the string is not reached
    if (*str)
    {
        // recur for the node corresponding to the next character in
        // the string and if it returns 1, delete the current node
        // (if it is non-leaf)
        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
            deletion(&((*curr)->character[*str - 'a']), str + 1) &&
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

void print_trie(struct Trie *root)
{
    // Prints the nodes of the trie

    if (!root)
        return;
    struct Trie *temp = root;
    //  printf("%c -> ", temp->data);
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (temp->character[i] != '\0')
            printf("%c -", root->character[i]->data);
        print_trie(temp->character[i]);
    }
}

int main()
{
    struct Trie *head = getNewTrieNode();
    int ch, res;
    do
    {

        char *word = malloc(sizeof(char) * CHAR_SIZE);
        int result, len;
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

        case 5:
            exit(1);
        default:
            break;
        }
    } while (ch <= 4);

    return 0;
}
