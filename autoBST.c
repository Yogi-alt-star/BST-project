#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
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
label:
    if (*root == NULL)
    {
        *root = New_Node;
        printf("Data insertion Successfull!!\n");
        return;
    }
    if (New_Node->data < (*root)->data)
    {
        root = &(*root)->left;
    }
    else
    {
        root = &(*root)->right;
    }
    goto label;
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
    {
        return;
    }
    if (root->left == NULL && root->right == NULL)
    {
        free(root);
        root = NULL;
        return;
    }
    Deallocating(root->left);
    Deallocating(root->right);
    free(root);
    return;
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
int peek(struct node *root, const char *ptr)
{
    int x = 0;
    if (root == NULL)
    {
        return 101;
    }
    if (ptr[0] != 'r')
    {
        return 404;
    }
    x = 1;
    
    while (ptr[x] != '\0')
    {
        if (ptr[x] == '1')
        {
            if (root->right == NULL)
            {
                return 404;
            }
            root = root->right;
        }
        else if (ptr[x] == '0')
        {
            if (root->left == NULL)
            {
                return 404;
            }
            root = root->left;
        }
        else
        {
            return 404;
        }
        x++;
    }
    return root->data;
}
int main()
{
    int c;
    char Address[100];
    struct node *Root = NULL;
    printf("=============================================================\n");
    printf("What You Want To Do!!!\n");
    while (1)
    {
        printf("1-Insert New Node\n2-Pre Order Traverse\n3-In Order Travers\n4-Post Order Travers\n5-search\n6-Peek Data\n7-exit::");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
        {
            insert(&Root);
            printf("\n");
            break;
        }

        case 2:
        {
            Pre_Order(Root);
            printf("\n");
            break;
        }

        case 3:
        {
            In_Order(Root);
            printf("\n");
            break;
        }

        case 4:
        {
            Post_Order(Root);
            printf("\n");
            break;
        }
        case 5:
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
        case 6:
        {
            char add[100];
            int data;
            printf("Enter the Exact Address of Your Element::");
            scanf("%s", add);
            data = peek(Root, add);
            if (data == 404)
            {
                printf("Data Not found please check your Laction!!\n");
            }
            else if (data == 101)
            {
                printf("Tree is Empty!!!!\n");
            }
            else
            {
                printf("Your data is Found = %d\n", data);
            }

            break;
        }
        case 7:
        {
            goto label;
        }
        default:
        {
            printf("Invalid Entry Please try again!!!!\n");
        }
        }
    }
label:
    Deallocating(Root);
    printf("Data Deleted SuccessfullY!!\n");
    return 0;
}