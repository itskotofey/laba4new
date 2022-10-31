#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <locale.h>


struct Node {
    Node* left;
    Node* right;
    int data;
};

struct Node* root = NULL;

bool search(struct Node* node, int value);

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("������ ��������� ������");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;

        if (root == NULL)
            return r;

        if (data > root->data)
            root->left = r;
        else
            root->right = r;

        return r;
    }

    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}

struct Node* CreateTreeUnique(struct Node* root, struct Node* r, int data)
{
    if (!search(root, data)) {  // ���� ������� �� ������ � ������, �� ���������� ��� ����
        if (r == NULL)
        {
            r = (struct Node*)malloc(sizeof(struct Node));
            if (r == NULL)
            {
                printf("������ ��������� ������");
                exit(0);
            }

            r->left = NULL;
            r->right = NULL;
            r->data = data;

            if (root == NULL)
                return r;

            if (data > root->data)
                root->left = r;
            else
                root->right = r;

            return r;
        }

        if (data > r->data)
            CreateTreeUnique(r, r->left, data);
        else
            CreateTreeUnique(r, r->right, data);
    }

    return root;
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL)
    {
        return;
    }

    print_tree(r->right, l + 1);

    for (int i = 0; i < l; i++)
    {
        printf(" ");
    }

    printf("%d\n", r->data);

    print_tree(r->left, l + 1);
}

// �����
bool search(struct Node* node, int value) {
    if (node == NULL) {
        return false;
    }

    if (node->data == value)
        return true; // �����

    if (value < node->data) // ���� ������� ������ �������� � ������� ���� �� ���� � ������ ��������� ������������� ������
        return search(node->right, value);


    if (value > node->data)  // ���� ������� ������ �������� � ������� ���� �� ���� � ����� ��������� ������������� ������
        return search(node->left, value);
}

// ������� ����� ����������
int count_repeats(struct Node* node, int val) {
    if (node == NULL)
        return 0;

    if (node->data == val) { // ����� �������, ������� ��� ���������� � ������ ����� ������� � ��������
        struct Node* current = node;
        int counter = 1;
        while ((current = current->right) != NULL && current->data == val)
            counter++;
        return counter;
    }
    else if (val > node->data) {
        return count_repeats(node->left, val); // ���� � ����� ���������
    }
    else if (val < node->data) {
        return count_repeats(node->right, val); // ���� � ������ ���������
    }
}

int main()
{
    setlocale(LC_ALL, "");
    int D, start = 1;

    root = NULL;
    printf("-1 - ��������� ���������� ������\n");

    while (start)
    {
        printf("������� �����: ");
        scanf("%d", &D);

        if (D == -1)
        {
            printf("���������� ������ ��������\n\n");
            start = 0;
        }
        else {
            //root = CreateTree(root, root, D);
            root = CreateTreeUnique(root, root, D);
        }
    }

    print_tree(root, 0);

    // ����� 
    printf("������� ����� ��� ������: ");
    scanf("%d", &D);

    if (D != -1) {
        if (search(root, D)) {
            printf("�������\n");
            printf("����� ����������: %d\n", count_repeats(root, D));
        }
        else
            printf("�� �������\n");
    }

    return 0;
}

