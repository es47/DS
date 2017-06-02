#include <stdio.h>
#include <stdlib.h>

typedef struct avl_node
{
    struct avl_node *left;
    struct avl_node *right;
    int value;
} Node;

typedef struct avl_tree
{
    struct avl_node *root;
} Tree;

int height(Node *node)
{
    int height_left = 0;
    int height_right = 0;
    if (node->left)
        height_left = height(node->left);
    if (node->right)
        height_right = height(node->right);
    return (height_right > height_left)? ++height_right : ++height_left;
}

int balance_factor(Node *node)
{
    int bf = 0;
    if(node->left)
        bf += height(node->left);
    if(node->right)
        bf -= height(node->right);
    return bf;
}

Node *rotate_LL(Node *node)
{
    Node *a = node;
    Node *b = a->left;
    a->left = b->right;
    b->right = a;
    return b;
}

Node *rotate_LR(Node *node)
{
    Node *a = node;
    Node *b = a->left;
    Node *c = b->right;
    a->left = c->right;
    b->right = c->left;
    c->left = b;
    c->right = a;
    return c;
}

Node *rotate_RL(Node *node)
{
    Node *a = node;
    Node *b = a->right;
    Node *c = b->left;
    a->right = c->left;
    b->left = c->right;
    c->right = b;
    c->left = a;
    return c;
}

Node *rotate_RR(Node *node)
{
    Node *a = node;
    Node *b = a->right;
    a->right = b->left;
    b->left = a;
    return b;
}

Node *balance_node(Node *node )
{
    Node *newroot = NULL;
    if (node->left)
        node->left = balance_node(node->left);
    if (node->right)
        node->right = balance_node(node->right);
    int bf = balance_factor(node);
    if (bf >= 2)
    {
        if (balance_factor(node->left) <= -1)
            newroot = rotate_LR(node);
        else
            newroot = rotate_LL(node);
    }
    else if(bf <= -2)
    {
        if(balance_factor(node->right) >= 1)
            newroot = rotate_RL(node);
        else
            newroot = rotate_RR(node);
    }
    else
        newroot = node;
    return newroot;
}

void balance(Tree *tree )
{
    Node *newroot = NULL;
    newroot = balance_node(tree->root);
    if(newroot != tree->root)
        tree->root = newroot;
}

void insert(Tree *tree, int value)
{
    Node *node = NULL;
    Node *next = NULL;
    Node *last = NULL;
    if (tree->root == NULL)
    {
        node = (Node *)malloc(sizeof(Node));
        node->right = NULL;
        node->left = NULL;
        node->value = value;
        tree->root = node;
    }
    else
    {
        next = tree->root;
        while (next != NULL)
        {
            last = next;
            if (value < next->value)
                next = next->left;
            else
                next = next->right;
        }
        node = (Node *)malloc(sizeof(Node));
        node->right = NULL;
        node->left = NULL;
        node->value = value;
        if (value < last->value )
            last->left = node;
        if (value > last->value )
            last->right = node;
    }
    balance(tree);
}

void DFS_in(Node *node, int depth, int *i)
{
    if(node->left)
        DFS_in(node->left, depth + 2, &(*i));
    if (*i != 0)
        printf(",");
    printf("%d", node->value);
    (*i)++;
    if(node->right)
        DFS_in(node->right, depth + 2, &(*i));
}

void DFS_post(Node *node, int depth, int *i)
{
    if(node->left)
        DFS_post(node->left, depth + 2, &(*i));
    if(node->right)
        DFS_post(node->right, depth + 2, &(*i));
    if (*i != 0)
        printf(",");
    printf("%d", node->value);
    (*i)++;
}

int main(void)
{
    int N, i, n;
    Tree *tree = NULL;
    scanf("%d", &N);
    while(N--)
    {
        tree = (Tree *)malloc(sizeof(Tree));
        tree->root = NULL;
        while(1)
        {
            scanf("%d", &n);
            if (n == -1) break;
            insert(tree, n);
        }
        i = 0;
        DFS_in(tree->root, 0, &i);
        printf("\n");
        i = 0;
        DFS_post(tree->root, 0, &i);
        printf("\n");
    }
    return 0;
}
