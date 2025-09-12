#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 1000

typedef struct Node {
    char val;
    int childCount;
    struct Node* parent;
} Node;

int main() {
    char input[MAX];
    if (!fgets(input, sizeof(input), stdin)) {
        printf("ERROR 0\n");
        return 0;
    }

    char str[MAX];
    int idx = 0;
    for (int i = 0; input[i]; i++) {
        if (!isspace((unsigned char)input[i])) {
            str[idx++] = input[i];
        }
    }
    str[idx] = '\0';

    Node* stack[MAX];
    int top = -1;

    Node* root = NULL;
    int error = 0;
    int tooMany = 0;

    for (int i = 0; str[i] && !error && !tooMany; i++) {
        char c = str[i];
        if (isupper(c)) {
            Node* node = (Node*)malloc(sizeof(Node));
            node->val = c;
            node->childCount = 0;
            node->parent = NULL;

            if (top >= 0) {
                Node* parent = stack[top];
                parent->childCount++;
                if (parent->childCount > 2) {
                    tooMany = 1;
                    break;
                }
                node->parent = parent;
            } else {
                if (root != NULL) {
                    error = 1;
                    break;
                }
                root = node;
            }
            stack[++top] = node;
        } else if (c == '(') {
            if (top < 0) {
                error = 1;
                break;
            }
        } else if (c == ')') {
            if (top < 0) {
                error = 1;
                break;
            }
            top--;
        } else {
            error = 1;
            break;
        }
    }

    if (!error && !tooMany && top != -1) {
        error = 1;
    }

    if (error) {
        printf("ERROR 0\n");
    } else if (tooMany) {
        printf("FALSE 2\n");
    } else {
        printf("TURE 1\n");
    }

    return 0;
}
