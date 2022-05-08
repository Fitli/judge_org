#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int number_names;
    char letter;
    struct Node *left;
    struct Node *right;
    struct Node *down;
};

struct Node *new_node(char letter) {
    struct Node *node = malloc(sizeof(struct Node));
    node->down = NULL;
    node->left = NULL;
    node->right = NULL;
    node->number_names = 0;
    node->letter = letter;
    return node;
}

void insert(char *name, struct Node *node) {
    unsigned int index = 0;
    unsigned int len = strlen(name);
    while (index <= len) {
        if(node->letter == name[index]) {
            node->number_names++;
            if(index == len) {
                break;
            }
            if(!node->down) {
                node->down = new_node(name[index + 1]);
            }
            node = node->down;
            index++;
        }
        else if (node->letter > name[index]){
            if(!node->left) {
                node->left = new_node(name[index]);
            }
            node = node->left;
        }
        else if (node->letter < name[index]){
            if(!node->right) {
                node->right = new_node(name[index]);
            }
            node = node->right;
        }
    }
}

void query(char *name, struct Node *node) {
    unsigned int index = 0;
    printf("%s:", name);
    while (name[index] != '\0') {
        if (node == NULL) {
            printf(" 0");
            break;
        }
        if(node->letter == name[index]) {
            printf(" %d", node->number_names);
            index++;
            node = node->down;
        }
        else if (node->letter > name[index]) {
            node = node->left;
        }
        else if (node->letter < name[index]) {
            node = node->right;
        }
    }
    printf("\n");
}

int main() {
    char input[4000];
    char false_names[4000];
    struct Node *tree = NULL;
    while(scanf("%s", input) > 0) {
        char white = getchar();
        if(white == ' ') {
            scanf("%s", false_names);
            getchar();
            if(!tree) {
                tree = new_node(input[0]);
            }
            insert(input, tree);
        }
        else {
            query(input, tree);
        }
    }
    return 0;
}
