#include <iostream>

using namespace std;

class node
{
public:
    int data;
    class node *left;
    class node *right;
};

//Height of avl tree
int height(class node *ptr)
{
    int h = 0;
    if (ptr != NULL)
    {
        int l_height = height(ptr->left);
        int r_height = height(ptr->right);
        int maxheight = max(l_height, r_height);
        h = maxheight + 1;
    }
    return h;
}
//Find balance  factor
int height_diff(class node *ptr)
{
    int l_height = height(ptr->left);
    int r_height = height(ptr->right);
    int b_factor = l_height - r_height;
    return b_factor;
}
// Right-Right rotation
class node *rr_rot(class node *ptr)
{
    class node *temp;
    temp = ptr->right;
    ptr->right = temp->left;
    temp->left = ptr;
    return temp;
}
//Left -Left rotation
class node *ll_rot(class node *ptr)
{
    class node *temp;
    temp = ptr->left;
    ptr->left = temp->right;
    temp->right = ptr;
    return temp;
}
//Left-right rotation
class node *lr_rot(class node *ptr)
{
    class node *temp;
    temp = ptr->left;
    ptr->left = rr_rot(temp);
    return ll_rot(ptr);
}
//Right-Left rotation
class node *rl_rot(class node *ptr)
{
    class node *temp;
    temp = ptr->right;
    ptr->right = ll_rot(temp);
    return rr_rot(ptr);
}
//Balancing avl tree
class node *balance(class node *ptr)
{
    int bal_fact = height_diff(ptr);
    if (bal_fact > 1)
    {
        if (height_diff(ptr->left) > 0)
        {
            ptr = ll_rot(ptr);
        }
        else
        {
            ptr = lr_rot(ptr);
        }
    }
    else if (bal_fact < -1)
    {
        if (height_diff(ptr->right) > 0)
        {
            ptr = rr_rot(ptr);
        }
        else
        {
            ptr = rl_rot(ptr);
        }
    }
    return ptr;
}
class node *create(int value)
{
    class node *ptr = new node();
    ptr->data = value;
    ptr->left = NULL;
    ptr->right = NULL;
    return ptr;
}
class node *insertion(class node *ptr, int value)
{
    if (ptr == NULL)
    {
        return create(value);
    }
    else if (value < ptr->data)
    {
        ptr->left = insertion(ptr->left, value);
        ptr = balance(ptr);
    }
    else if (value >= ptr->data)
    {
        ptr->right = insertion(ptr->right, value);
        ptr = balance(ptr);
    }
    return ptr;
}

void inorder(class node *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    inorder(ptr->left);
    cout << ptr->data;
    cout << " ";
    inorder(ptr->right);
}
void preorder(class node *ptr)
{
    if (ptr != NULL)
    {
        cout << ptr->data << " ";

        preorder(ptr->left);
        preorder(ptr->right);
    }
    return;
}
int main()
{
    class node *root = create(56);
    insertion(root, 34);
    insertion(root, 89);
    insertion(root, 67);
    inorder(root);
    preorder(root);
}