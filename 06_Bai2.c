#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 100

typedef struct Text {
    char text[MAX_LEN];
} Text;

typedef struct Stack {
    Text text[100];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == 99;
}

void push(Stack* s, char* text) {
    if (isFull(s)) {
        printf("Clipboard is full\n");
        return;
    }
    s->top++;
    strcpy(s->text[s->top].text, text);
}

char* pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Clipboard is empty\n");
        return NULL;
    }
    static char temp[MAX_LEN];
    strcpy(temp, s->text[s->top].text);
    s->top--;
    return temp;
}

char* peek(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->text[s->top].text;
}

void clear(Stack* s) {
    s->top = -1;
}

int main() {
    Stack clipboard;
    Stack redo;
    initStack(&clipboard);
    initStack(&redo);
    int choice;
    char current[MAX_LEN] = "example";
    char text[MAX_LEN];

    do {
        printf("=============MENU===========\n");
        printf("Văn bản hiện tại: %s\n\n", current);
        printf("1. Copy\n");
        printf("2. Paste\n");
        printf("3. Undo\n");
        printf("4. Redo\n");
        printf("5. History\n");
        printf("6. Exit\n");
        printf("============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                while (getchar() != '\n');
                printf("Enter text to copy: ");
                fgets(text, MAX_LEN, stdin);
                text[strcspn(text, "\n")] = 0;
                push(&clipboard, text);
                clear(&redo);
                break;

            case 2:
                if (isEmpty(&clipboard)) {
                    printf("Clipboard is empty\n");
                } else {
                    char* temp = pop(&clipboard);
                    if (temp != NULL) {
                        push(&redo, current);
                        strcpy(current, temp);
                        printf("Text pasted: %s\n", current);
                    }
                }
                break;

            case 3:
                if (isEmpty(&redo)) {
                    printf("Nothing to undo\n");
                } else {
                    char* temp = pop(&redo);
                    if (temp != NULL) {
                        push(&clipboard, current);
                        strcpy(current, temp);
                        printf("Undo successful\n");
                    }
                }
                break;

            case 4:
                if (isEmpty(&clipboard)) {
                    printf("Nothing to redo\n");
                } else {
                    char* temp = pop(&clipboard);
                    if (temp != NULL) {
                        push(&redo, current);
                        strcpy(current, temp);
                        printf("Redo successful\n");
                    }
                }
                break;

            case 5:
                printf("\nClipboard History:\n");
                if (isEmpty(&clipboard)) {
                    printf("Clipboard is empty\n");
                } else {
                    Stack tempStack;
                    initStack(&tempStack);


                    while (!isEmpty(&clipboard)) {
                        char* temp = pop(&clipboard);
                        if (temp != NULL) {
                            printf("- %s\n", temp);
                            push(&tempStack, temp);
                        }
                    }
                    while (!isEmpty(&tempStack)) {
                        char* temp = pop(&tempStack);
                        if (temp != NULL) {
                            push(&clipboard, temp);
                        }
                    }
                }
                break;


            case 6:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}