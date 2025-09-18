#include <stdio.h>    // Dùng cho việc nhập/xuất (printf)
#include <stdlib.h>   // Dùng cho cấp phát bộ nhớ (malloc, free)
#include <stdbool.h>  // Dùng cho kiểu dữ liệu bool (true/false)
#include <limits.h>   // Dùng cho hằng số INT_MIN

// Định nghĩa cấu trúc của một node (nút)
typedef struct node {
    int data;
    struct node *next;
} node;

node *createNode(int value) {
    // Cấp phát bộ nhớ cho một node
    node *newNode = (node*)malloc(sizeof(node));

    // Kiểm tra xem cấp phát có thành công không
    if (newNode == NULL) {
        fprintf(stderr, "Loi: Khong the cap phat bo nho!\n");
        return NULL;
    }

    newNode->data = value;
    newNode->next = NULL; // Node mới chưa trỏ đi đâu cả
    return newNode;
}

void push_back(node** head, int value) {
    node* newNode = createNode(value);
    if (newNode == NULL) return; // Không thêm được nếu tạo node thất bại

    if (*head == NULL) { // Nếu danh sách rỗng
        *head = newNode;
        return;
    }

    node* temp = *head;
    while (temp->next != NULL) { // Duyệt đến node cuối cùng
        temp = temp->next;
    }
    temp->next = newNode; // Cho node cuối trỏ tới node mới
}

void push_front(node **head, int value) {
    node* newNode = createNode(value);
    if (newNode == NULL) return;

    newNode->next = *head; // Node mới trỏ vào đầu danh sách cũ
    *head = newNode;       // Cập nhật lại đầu danh sách là node mới
}

void pop_back(node **head) {
    if (*head == NULL) return; // Danh sách rỗng

    if ((*head)->next == NULL) { // Danh sách chỉ có 1 phần tử
        free(*head);
        *head = NULL;
        return;
    }

    node* temp = *head;
    // Duyệt đến node kế cuối
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);  // Giải phóng bộ nhớ node cuối
    temp->next = NULL; // Cập nhật con trỏ node kế cuối
}

void pop_front(node **head) {
    if (*head == NULL) return; // Danh sách rỗng

    node* temp = *head;      // Giữ lại node đầu để xóa
    *head = (*head)->next;   // Cập nhật head
    free(temp);              // Giải phóng bộ nhớ
}

int front(node *head) {
    if (head == NULL) {
        fprintf(stderr, "Loi: Danh sach rong!\n");
        return INT_MIN; // Giá trị báo lỗi
    }
    return head->data;
}

int back(node *head) {
    if (head == NULL) {
        fprintf(stderr, "Loi: Danh sach rong!\n");
        return INT_MIN;
    }
    node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp->data;
}

void insert(node **head, int value, int pos) {
    if (pos < 0) {
        fprintf(stderr, "Loi: Vi tri chen khong hop le!\n");
        return;
    }
    if (pos == 0) {
        push_front(head, value);
        return;
    }

    node* temp = *head;
    // Duyệt đến vị trí ngay trước vị trí cần chèn
    for (int i = 0; i < pos - 1 && temp != NULL; ++i) {
        temp = temp->next;
    }

    if (temp == NULL) { // Vị trí chèn vượt quá kích thước danh sách
        fprintf(stderr, "Loi: Vi tri chen khong hop le!\n");
        return;
    }

    node* newNode = createNode(value);
    if (newNode == NULL) return;

    newNode->next = temp->next;
    temp->next = newNode;
}

void erase(node **head, int pos) {
    if (*head == NULL || pos < 0) {
        fprintf(stderr, "Loi: Vi tri xoa khong hop le!\n");
        return;
    }
    if (pos == 0) {
        pop_front(head);
        return;
    }

    node* temp = *head;
    // Duyệt đến vị trí ngay trước vị trí cần xóa
    for (int i = 0; i < pos - 1 && temp != NULL; ++i) {
        temp = temp->next;
    }

    // Nếu vị trí không hợp lệ
    if (temp == NULL || temp->next == NULL) {
        fprintf(stderr, "Loi: Vi tri xoa khong hop le!\n");
        return;
    }

    node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
}

int size(node *head) {
    int count = 0;
    node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int get(node *head, int pos) {
    if (pos < 0) {
        fprintf(stderr, "Loi: Vi tri khong hop le!\n");
        return INT_MIN;
    }

    node* temp = head;
    for (int i = 0; i < pos; ++i) {
        if (temp == NULL) { // Nếu vị trí vượt quá kích thước
             fprintf(stderr, "Loi: Vi tri khong hop le!\n");
             return INT_MIN;
        }
        temp = temp->next;
    }

    if (temp == NULL) {
        fprintf(stderr, "Loi: Vi tri khong hop le!\n");
        return INT_MIN;
    }
    return temp->data;
}

bool empty(node *head) {
    return head == NULL;
}

void clear(node** head) {
    node* current = *head;
    node* nextNode = NULL;
    while (current != NULL) {
        nextNode = current->next; // Lưu lại node tiếp theo
        free(current);            // Giải phóng node hiện tại
        current = nextNode;       // Di chuyển đến node tiếp theo
    }
    *head = NULL; // Đặt con trỏ đầu về NULL
}