#include<iostream>
#include<string.h>
using namespace std;

struct Ngay
{
    int ngay, thang, nam;
};

bool soSanhNgay(Ngay n1, Ngay n2) {
    return (n1.ngay == n2.ngay && n1.thang == n2.thang && n1.nam == n2.nam);
}

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

void print_SV_trung_NgaySinh(List l)
{
    bool found = false;
    Node *p = l.first;

    while (p != NULL)
    {
        // Chỉ xử lý nếu ngày sinh này chưa được in (tránh in nhóm trùng lặp)
        // Kiểm tra xem p có bị xử lý bởi vòng lặp trước chưa
        bool daIn = false;
        Node *check = l.first;
        while (check != p)
        {
            if (soSanhNgay(check->data.ngaySinh, p->data.ngaySinh))
            {
                daIn = true;
                break;
            }
            check = check->link;
        }

        if (!daIn)
        {
            // Đếm số SV cùng ngày sinh với p
            int count = 0;
            Node *q = l.first;
            while (q != NULL)
            {
                if (soSanhNgay(p->data.ngaySinh, q->data.ngaySinh))
                    count++;
                q = q->link;
            }

            // Nếu có từ 2 người trở lên → in cả nhóm
            if (count >= 2)
            {
                cout << "Ngay sinh: " << p->data.ngaySinh.ngay << "/"
                     << p->data.ngaySinh.thang << "/"
                     << p->data.ngaySinh.nam << endl;

                Node *q = l.first;
                while (q != NULL)
                {
                    if (soSanhNgay(p->data.ngaySinh, q->data.ngaySinh))
                        cout << "  " << q->data.maSV << " - " << q->data.hoTen << endl;
                    q = q->link;
                }

                found = true;
            }
        }

        p = p->link;
    }

    if (!found)
        cout << "Khong co sinh vien nao trung ngay sinh." << endl;
}

void xoa_SV_trung_NgaySinh(List &l)
{
    // Bước 1: Thu thập maSV cần xóa
    char canXoa[100][10];
    int soLuong = 0;

    Node *p = l.first;
    while (p != NULL)
    {
        int count = 0;
        Node *q = l.first;
        while (q != NULL)
        {
            if (soSanhNgay(p->data.ngaySinh, q->data.ngaySinh))
                count++;
            q = q->link;
        }
        if (count >= 2)
        {
            strcpy(canXoa[soLuong], p->data.maSV);
            soLuong++;
        }
        p = p->link;
    }

    // Bước 2: Xóa từng maSV trong danh sách canXoa
    for (int i = 0; i < soLuong; i++)
    {
        // Xóa node đầu
        while (l.first != NULL && strcmp(l.first->data.maSV, canXoa[i]) == 0)
        {
            Node *del = l.first;
            l.first = l.first->link;
            if (l.first == NULL) l.last = NULL;
            delete del;
        }

        // Xóa node giữa/cuối
        Node *prev = l.first;
        while (prev != NULL && prev->link != NULL)
        {
            if (strcmp(prev->link->data.maSV, canXoa[i]) == 0)
            {
                Node *del = prev->link;
                prev->link = del->link;
                if (del == l.last) l.last = prev;
                delete del;
            }
            else
            {
                prev = prev->link;
            }
        }
    }
}

int main()
{
    List l;
    init(l);

    SinhVien a = {"202400005", "Vu An",      0, {1, 1, 2003}};
    SinhVien b = {"202400002", "Nguyen Binh",0, {1, 1, 2003}};
    SinhVien c = {"202400009", "Xuan Cuong", 0, {5, 5, 2004}};
    SinhVien d = {"202400001", "Bui Dung",   0, {1, 1, 2003}};
    SinhVien e = {"202400003", "Tran Em",    0, {5, 5, 2004}};
    SinhVien f = {"202400007", "Le Phuong",  0, {9, 9, 2005}}; // không trùng ai

    them_SV(l, a);
    them_SV(l, b);
    them_SV(l, c);
    them_SV(l, d);
    them_SV(l, e);
    them_SV(l, f);

    cout << "Danh sach sinh vien trung ngay sinh:\n";
    print_SV_trung_NgaySinh(l);

    cout << "\nSau khi loai bo SV trung ngay sinh:\n";
    xoa_SV_trung_NgaySinh(l);
    print_SV(l);

    return 0;
}