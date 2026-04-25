#include<iostream>
#include<string.h>
using namespace std;

struct Ngay
{
    int ngay, thang, nam;
};

struct SinhVien
{
    char maSV[10];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node
{
    SinhVien data;
    Node *link;
};

struct List 
{
    Node *first;
    Node *last;
};

void init(List &l)
{
    l.first = l.last = NULL;
};

Node* createNode(SinhVien x) 
{
    Node *p = new Node;
    p->data = x;
    p->link = NULL;
    return p;
}

void them_SV(List &l, SinhVien x)
{
    Node *p = createNode(x);
    if(l.first == NULL)
    {
        l.first = l.last= p;
        return;
    }
    if (strcmp(p->data.maSV, l.first->data.maSV) < 0)
    {
        p->link = l.first;
        l.first = p;
        return;
    }
    Node *q = l.first;
    while (q->link != NULL &&  strcmp(q->link->data.maSV, p->data.maSV) < 0)
        q = q->link;
    
    p->link = q->link;
    q->link = p;
    if (p->link == NULL) l.last = p;
}

void print_SV(const List &l)
{
    Node *p = l.first;
    while (p != NULL)
    {
        cout << p->data.maSV << " - " << p->data.hoTen << endl;
        p = p->link;
    }
}

int main()
{
    List l;
    init(l);

    // test du lieu
    SinhVien a = {"202400005", "Vu An"};
    SinhVien b = {"202400002", "Nguyen Binh"};
    SinhVien c = {"202400009", "Xuan Cuong"};
    SinhVien d = {"202400001", "Bui Dung"};

    them_SV(l, a);
    them_SV(l, b);
    them_SV(l, c);
    them_SV(l, d);

    cout << "Danh sach sau khi sap xep:\n";
    print_SV(l);

    return 0;
}