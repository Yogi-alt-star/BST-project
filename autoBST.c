#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *root;
    struct node *left;
    struct node *right;
};
// Inserting
void insert(struct node **root)
{

    int option;
    struct node *New_Node = (struct node *)malloc(sizeof(struct node));
    printf("Enter the Data You Want to Insert::");
    scanf("%d", &New_Node->data);
    New_Node->left = NULL;
    New_Node->right = NULL;
    New_Node->root = NULL;
    struct node *parent = NULL;
    while (*root != NULL)
    {
        parent = *root;
        if (New_Node->data < (*root)->data)
        {
            root = &(*root)->left;
        }
        else
        {
            root = &(*root)->right;
        }
    }
    New_Node->root = parent;
    *root = New_Node;
}
// travers Pre Order
void Pre_Order(struct node *Root)
{
    if (Root == NULL)
    {
        return;
    }
    else
    {
        printf("%d ", Root->data);
        Pre_Order(Root->left);
        Pre_Order(Root->right);
    }
}
// In Order Travers
void In_Order(struct node *Root)
{
    if (Root == NULL)
    {
        return;
    }
    else
    {
        In_Order(Root->left);
        printf("%d ", Root->data);
        In_Order(Root->right);
    }
}
// post Order travers
void Post_Order(struct node *Root)
{
    if (Root == NULL)
    {

        return;
    }
    else
    {
        Post_Order(Root->left);
        Post_Order(Root->right);
        printf("%d ", Root->data);
    }
}
// Memory Free
void Deallocating(struct node *root) 
{ 
    if (root == NULL) 
    return; 
    Deallocating(root->left); 
    Deallocating(root->right); 
    free(root); 
}
// search
int search(struct node *root, char *ptr, int data, int *i)
{
    if (root == NULL) // base Case
    {
        return 0;
    }
    else
    {
        if (*i == 0)
        {
            ptr[0] = 'r'; // root = r
            (*i)++;
        }
    }
    if (root->data == data)
    {
        return 1;
    }
    else if (root->data > data)
    {

        ptr[*i] = '0'; // left = 0
        (*i)++;
        return search(root->left, ptr, data, i);
    }
    else
    {

        ptr[*i] = '1'; // right = 1
        (*i)++;
        return search(root->right, ptr, data, i);
    }
    return 0;
}
// peekup element by address
struct node *peek(struct node *root, const char *ptr)
{
    int x = 0;
    if (root == NULL)
    {
        return NULL;
    }
    if (ptr[0] != 'r')
    {
        return NULL;
    }
    x = 1;

    while (ptr[x] != '\0')
    {
        if (ptr[x] == '1')
        {
            if (root->right == NULL)
            {
                return NULL;
            }
            root = root->right;
        }
        else if (ptr[x] == '0')
        {
            if (root->left == NULL)
            {
                return NULL;
            }
            root = root->left;
        }
        else
        {
            return NULL;
        }
        x++;
    }
    return root;
}
// smallest Node from left
struct node *smallest(struct node *point)
{
    if (point->left == NULL)
    {
        return point;
    }
    return smallest(point->left);
}
// sub fun of Deleting
int subdel(struct node **root, struct node *point)
{
    if (point->left == NULL && point->right == NULL)
    {
        if (point == *root) // deleting Main root with no Leaf
        {
            *root = NULL;
            free(point);
            return 1;
        }
        if (point->root->data > point->data) // deleting non-root node with  no leaf --left side
        {
            point->root->left = NULL;
            free(point);
            return 1;
        }
        else // deleting non-root node with  no leaf --Right side
        {
            point->root->right = NULL;
            free(point);
            return 1;
        }
    }
    else if (point->right == NULL) // deleting nodes having one leaf
    {
        if (point == *root) // deleting Main root with left leaf
        {
            *root = point->left;
            (*root)->root = NULL;
            free(point);
            return 1;
        }

        if (point->root->data > point->left->data) //
        {
            point->root->left = point->left;
            point->left->root=point->root;
            free(point);
            return 1;
        }
        else
        {

            point->root->right = point->left;
            point->left->root = point->root;
            free(point);
            return 1;
        }
    }
    else if (point->left == NULL)
    {

        if (point == *root) // deleting Main root with Right leaf
        {
            *root = point->right;
            (*root)->root = NULL;
            free(point);
            return 1;
        }
        if (point->root->data < point->right->data)
        {
            point->root->right = point->right;
            point->right->root = point->root;
            free(point);
            return 1;
        }
        else
        {
            point->root->left = point->right;
            point->right->root = point->root;
            free(point);
            return 1;
        }
    }
    else
    {
        struct node *low = smallest(point->right);
        point->data = low->data; 
        return subdel(root, low);
    }

    return 0;
}
// Deleting Node
void del(struct node **root, const char *ptr)
{
    struct node *point;
    point = peek(*root, ptr);
    if (point == NULL)
    {
        printf("Please Check your Location For Deletion!!!\n");
        return;
    }
    if (subdel(root, point))
    {
        printf("Node is deleted succesfully!!\n");
        return;
    }
    printf("Error!!!\n");
    return;
}
int main()
{
    char c;
    char Address[100];
    struct node *Root = NULL;
    printf("=============================================================\n");
    printf("What You Want To Do!!!\n");
    while (1)
    {
        printf("1-Insert New Node\n2-Pre Order Traverse\n3-In Order Travers\n4-Post Order Travers\n5-search\n6-Peek Data\n7-Delete Node\n8-exit::");
        scanf(" %c", &c);
        switch (c)
        {
        case '1':
        {
            insert(&Root);
            printf("\n");
            break;
        }

        case '2':
        {
            Pre_Order(Root);
            printf("\n");
            break;
        }

        case '3':
        {
            In_Order(Root);
            printf("\n");
            break;
        }

        case '4':
        {
            Post_Order(Root);
            printf("\n");
            break;
        }
        case '5':
        {
            int data, i = 0;
            printf("Enter the Data you Want To Search in BST::");
            scanf("%d", &data);
            if (search(Root, Address, data, &i))
            {

                printf("Your Searching Data is found and Exact Location in BST is::");

                int j = 0;
                while (i >= 1)
                {
                    printf("->%c ", Address[j]);
                    j++;
                    i--;
                }
                printf("\n");
            }
            else
            {
                printf("Your Data is not found\n");
            }
            break;
        }
        case '6':
        {
            char add[100];
            struct node *data;
            printf("Enter the Exact Address of Your Element::");
            scanf("%s", add);
            data = peek(Root, add);
            if (data == NULL)
            {
                printf("Data Not found please check your Laction!!\n");
            }

            else
            {
                printf("Your data is Found = %d\n", data->data);
            }

            break;
        }
        case '7':
        {
            char add[100];
            printf("Enter the Exact Address of Your Element::");
            scanf("%s", add);
            del(&Root, add);
            break;
        }
        case '8':
        {
            goto label;
        }
        default:
        {
            printf("Invalid Entry Please try again!!!!\n");
            break;
        }
        }
    }
label:
    Deallocating(Root);
    printf("Data Deleted SuccessfullY!!\n");
    return 0;
}