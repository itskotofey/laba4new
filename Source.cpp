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
            printf("Ошибка выделения памяти");
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
    if (!search(root, data)) {  // если элемент не найден в дереве, то продолжаем как было
        if (r == NULL)
        {
            r = (struct Node*)malloc(sizeof(struct Node));
            if (r == NULL)
            {
                printf("Ошибка выделения памяти");
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

// поиск
bool search(struct Node* node, int value) {
    if (node == NULL) {
        return false;
    }

    if (node->data == value)
        return true; // нашли

    if (value < node->data) // если искомое меньше значения в текущем узле то ищем в правом поддереве перевернутого дерева
        return search(node->right, value);


    if (value > node->data)  // если искомое больше значения в текущем узле то ищем в левом поддереве перевернутого дерева
        return search(node->left, value);
}

// подсчет числа повторений
int count_repeats(struct Node* node, int val) {
    if (node == NULL)
        return 0;

    if (node->data == val) { // нашли искомый, считаем его повторения в правых узлах начиная с текущего
        struct Node* current = node;
        int counter = 1;
        while ((current = current->right) != NULL && current->data == val)
            counter++;
        return counter;
    }
    else if (val > node->data) {
        return count_repeats(node->left, val); // ищем в левом поддереве
    }
    else if (val < node->data) {
        return count_repeats(node->right, val); // ищем в правом поддереве
    }
}

int main()
{
    setlocale(LC_ALL, "");
    int D, start = 1;

    root = NULL;
    printf("-1 - окончание построения дерева\n");

    while (start)
    {
        printf("Введите число: ");
        scanf("%d", &D);

        if (D == -1)
        {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            //root = CreateTree(root, root, D);
            root = CreateTreeUnique(root, root, D);
        }
    }

    print_tree(root, 0);

    // Поиск 
    printf("Введите число для поиска: ");
    scanf("%d", &D);

    if (D != -1) {
        if (search(root, D)) {
            printf("Найдено\n");
            printf("Число повторений: %d\n", count_repeats(root, D));
        }
        else
            printf("Не найдено\n");
    }

    return 0;
}

