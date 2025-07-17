//
// Created by Cachiu on 17/7/25.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Project {
    int id;
    char title[50];
    char onwer[50];
    int priority;
} Project;

typedef struct Node1 {
    Project project;
    struct Node1 *next;
} Node1;

typedef struct Node2 {
    Project project;
    struct Node2 *next;
    struct Node2 *prev;
} Node2;

Node1 *addProject(Node1 *head, int *id) {
    char title[50];
    char onwer[50];
    int priority;
    while (getchar() != '\n');
    printf("Nhập tên Project: ");
    fgets(title, 50,stdin);
    title[strcspn(title, "\n")] = 0;
    printf("Nhập người sở hữu: ");
    fgets(onwer, 50,stdin);
    onwer[strcspn(onwer, "\n")] = 0;
    do {
        printf("Nhập độ ưu tiên (1-10): ");
        scanf("%d", &priority);
        if (priority < 1 || priority > 10) {
            printf("Độ ưu tiên không hợp lệ, vui lòng nhập lại.\n");
        }
    } while (priority < 1 || priority > 10);
    Node1 *newNode = (Node1 *) malloc(sizeof(Node1));
    newNode->project.id = ++*id;
    strcpy(newNode->project.title, title);
    strcpy(newNode->project.onwer, onwer);
    newNode->project.priority = priority;
    if (head == NULL) {
        newNode->next = head;
        head = newNode;
    } else {
        Node1 *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = NULL;
    }
    printf("\n=============================\n");
    printf("|Đã thêm thành công project.|\n");
    printf("=============================\n\n");

    return head;
}

void display(Node1 *head, Node2 *head2) {
    if (head == NULL) {
        printf("\n===================\n");
        printf("|Chưa có project.|\n");
        printf("===================\n\n");
        return;
    }
    Node1 *current = head;
    printf("\n===============LIST PROJECT=============\n");
    while (current != NULL) {
        printf("|ID: %d |NAME: %s |ONWER: %s |Priority: %d\n", current->project.id, current->project.title,
               current->project.onwer, current->project.priority);
        current = current->next;
    }
    printf("========================================\n\n");
    if(head2!=NULL) {
        Node2 *current2 = head2;
        printf("\n===============LIST COMPLETE PROJECT=============\n");
        while (current2 != NULL) {
            printf("|ID: %d |NAME: %s |ONWER: %s |Priority: %d\n", current2->project.id, current2->project.title,
                   current2->project.onwer, current2->project.priority);
            current2 = current2->next;
        }
        printf("========================================\n\n");
    }
    int out = -1;
    while (out != 0) {
        printf("Ấn 0 để thoát: ");
        scanf("%d", &out);
    }

    return;
}

Node1 *deleteProject(Node1 *head, int *id) {
    if (head == NULL) {
        printf("\n===================\n");
        printf("|Chưa có project.|\n");
        printf("===================\n\n");
        return head;
    } else {
        int dltId;
        do {
            printf("Nhập ID Project bạn muốn xóa:");
            scanf("%d", &dltId);
            if (dltId < 0 || dltId > (*id)) {
                printf("ID không hợp lệ vui lòng nhập lại.\n");
            }
        } while (dltId < 0 || dltId > (*id));

        Node1 *current = head;
        Node1 *prev = NULL;
        while (current->project.id != dltId) {
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            head = current->next;
            free(current);
        } else {
            prev->next = current->next;
            free(current);
        }
        printf("\n=====================================\n");
        printf("|Đã xóa thành công Project với ID %d|\n", dltId);
        printf("=====================================\n\n");
        return head;
    }
}

Node1 *updateProject(Node1 *head, int *id) {
    if (head == NULL) {
        printf("\n===================\n");
        printf("|Chưa có project.|\n");
        printf("===================\n\n");
        return head;
    } else {
        int updateId;
        do {
            printf("Nhập ID Project bạn muốn chỉnh sửa:");
            scanf("%d", &updateId);
            if (updateId < 0 || updateId > (*id)) {
                printf("ID không hợp lệ vui lòng nhập lại.\n");
            }
        } while (updateId < 0 || updateId > (*id));
        char title[50];
        char onwer[50];
        int priority;
        while (getchar() != '\n');
        printf("Nhập tên mới cho Project: ");
        fgets(title, 50,stdin);
        title[strcspn(title, "\n")] = 0;
        printf("Nhập người sở hữu mới: ");
        fgets(onwer, 50,stdin);
        onwer[strcspn(onwer, "\n")] = 0;
        do {
            printf("Nhập độ ưu tiên mới (1-10): ");
            scanf("%d", &priority);
            if (priority < 1 || priority > 10) {
                printf("Độ ưu tiên không hợp lệ, vui lòng nhập lại.\n");
            }
        } while (priority < 1 || priority > 10);
        Node1 *current = head;
        while (current->project.id != updateId) {
            current = current->next;
        }
        strcpy(current->project.title, title);
        strcpy(current->project.onwer, onwer);
        current->project.priority = priority;
        return head;
    }
}

Node1 *completeProject(Node1 *head, Node2 **head2, int *id) {
    if (head == NULL) {
        printf("\n===================\n");
        printf("|Chưa có project.|\n");
        printf("===================\n\n");
        return head;
    } else {
        int completeId;
        do {
            printf("Nhập ID Project bạn muốn đánh dấu: ");
            scanf("%d", &completeId);
            if (completeId < 0 || completeId > (*id)) {
                printf("ID không hợp lệ vui lòng nhập lại.\n");
            }
        } while (completeId < 0 || completeId > (*id));
        Node1 *current = head;
        Node1 *prev = NULL;
        while (current != NULL && current->project.id != completeId) {
            prev = current;
            current = current->next;
        }
        if (current == NULL) {
            printf("Không tìm thấy project với ID %d\n", completeId);
            return head;
        }
        Node2 *newNode = (Node2 *)malloc(sizeof(Node2));
        newNode->project = current->project;
        newNode->next = NULL;
        newNode->prev = NULL;
        if (*head2 == NULL) {
            *head2 = newNode;
        } else {
            Node2 *tail = *head2;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = newNode;
            newNode->prev = tail;
        }


        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);

        printf("\n=======================================\n");
        printf("|Đã đánh dấu hoàn thành Project ID %d|\n", completeId);
        printf("=======================================\n\n");

        return head;
    }
}
Node1* sort(Node1* head) {
    if (head == NULL) {
        printf("\n===================\n");
        printf("|Chưa có project.|\n");
        printf("===================\n\n");
        return head;
    } else {
        Node1 *i, *j;
        Project temp;

        for(i = head; i != NULL; i = i->next) {
            for(j = i->next; j != NULL; j = j->next) {
                if(i->project.priority > j->project.priority) {
                    temp = i->project;
                    i->project = j->project;
                    j->project = temp;
                }
            }
        }

        printf("\n================================\n");
        printf("|Đã sắp xếp theo độ ưu tiên.   |\n");
        printf("================================\n\n");
        return head;
    }
}
Node1* search(Node1* head) {
    if (head == NULL) {
        printf("\n===================\n");
        printf("|Chưa có project.|\n");
        printf("===================\n\n");
        return head;
    }
    char title[50];
    while (getchar() != '\n');
    printf("Nhập tên dự án bạn muốn tìm kiếm: ");
    fgets(title, 50,stdin);
    title[strcspn(title, "\n")] = 0;
    Node1*current=head;
    int found=0;
    printf("\n===============LIST PROJECT=============\n");
    while (current!=NULL) {

        if (strstr(current->project.title,title)!=NULL) {
            found=1;

                printf("|ID: %d |NAME: %s |ONWER: %s |Priority: %d\n", current->project.id, current->project.title,
                       current->project.onwer, current->project.priority);


        }
        current=current->next;
    }

    if (found==0) {
        printf("Không tìm thấy Project nào.\n");
    }
    printf("========================================\n\n");
    int out = -1;
    while (out != 0) {
        printf("Ấn 0 để thoát: ");
        scanf("%d", &out);
    }
    return head;
}
int main() {
    int choice;
    int id = -1;
    Node1 *head = NULL;
    Node2 *head2 = NULL;
    do {
        printf("=============MENU============\n");
        printf("1. Thêm dự án mới.\n");
        printf("2. Hiển thị danh sách dự án cá nhân.\n");
        printf("3. Xóa dự án.\n");
        printf("4. Cập nhật thông tin dự án.\n");
        printf("5. Đánh dấu dự án hoàn thành.\n");
        printf("6. Sắp xếp dự án theo độ ưu tiên.\n");
        printf("7. Tìm kiếm dự án theo tên.\n");
        printf("8. Thoát chương trình.\n");
        printf("===============================\n");
        printf("Nhập lựa chọn của bạn: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                head = addProject(head, &id);
                break;
            case 2:
                display(head,head2);
                break;
            case 3:
                head = deleteProject(head, &id);
                break;
            case 4:
                head = updateProject(head, &id);
                break;
            case 5:
                head = completeProject(head, &head2, &id);
                break;
            case 6:
                head=sort(head);
                break;
            case 7:
                head=search(head);
                break;
            case 8:
                printf("Đang thoát chương trình...");
                break;
            default:
                printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
                printf("|Lựa chọn không hợp lệ vui lòng chọn lại từ 1-8|\n");
                printf("++++++++++++++++++++++++++++++++++++++++++++++++\n\n");

                break;
        }
    } while (choice != 8);
}
