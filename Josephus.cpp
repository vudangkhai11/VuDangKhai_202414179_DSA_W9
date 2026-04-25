#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

// Tạo danh sách liên kết vòng
Node* taoVong(int n)
{
    Node* head = new Node{1, nullptr};
    Node* prev = head;

    for(int i = 2; i <= n; i++) {
        Node* temp = new Node{i, nullptr};
        prev->next = temp;
        prev = temp;
    }

    prev->next = head; // nối vòng
    return head;
}

int josephus(int n, int k) {
    Node* head = taoVong(n);

    Node* prev = head;
    while (prev->next != head) prev = prev->next;

    Node* curr = head;


    while (curr->next != curr) {
        // di chuyển k-1 bước
        for (int i = 1; i < k; i++) {
            prev = curr;
            curr = curr->next;
        }

        // xóa node thứ k
        prev->next = curr->next;
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }

    int result = curr->data;
    delete curr;
    return result;
}

int main()
{
    int n, k;
    cout << "Nhap n: ";
    cin >> n;
    cout << "Nhap k: ";
    cin >> k;

    cout << "Vi tri an toan: " << josephus(n, k) << endl;

    return 0;
}