#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *str;

void skip_spaces() {
    while (isspace(*str)) str++;
}

int check() {
    skip_spaces();
    if (*str != '(') return 0;
    str++;

    skip_spaces();
    if (!isalpha(*str)) return 0;
    str++;

    int kids = 0;

    while (1) {
        skip_spaces();
        if (*str != '(') break;

        if (!check()) return 0;
        kids++;
        if (kids > 2) return 0;
    }
    skip_spaces();
    if (*str != ')') return 0;
    str++;

    return 1;
}

int main() {
    char buf[300];
    printf("트리를 입력하세요. : ");
    fgets(buf, 300, stdin);

    int len = strlen(buf);
    if (buf[len - 1] == '\n') buf[len - 1] = '\0';

    str = buf;

    if (check()) {
        skip_spaces();
        if (*str == '\0') {
            printf("이진트리가 맞습니다.\n");
            return 0;
        }
    }
    printf("이진트리가 아닙니다.\n");
    return 0;
}
