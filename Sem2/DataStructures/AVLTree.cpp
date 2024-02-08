#include <iostream>
#include <type_traits>
#include <algorithm>
#include <string>

class Tree
{
public:
    int key;
    int amount = 0;
    std::string get_values;
    int ht = 0;
    std::string value;
    Tree* left = nullptr;
    Tree* right = nullptr;
    Tree() {}
    Tree(int key, std::string value) :key(key), value(value) {}


    Tree* insert_(Tree* node, int key, std::string value)
    {

        if (node == NULL) 
        {
            node = new Tree(key, value);
            return node;
        }

        if (key < node->key)
            node->left = insert_(node->left, key, value);
        else if (key > node->key)
            node->right = insert_(node->right, key, value);
        else
            return node;


        node->ht = 1 + std::max(height(node->left),
            height(node->right));


        int balance = difference(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Tree* search(Tree* root, int key) 
    {
        if (root == nullptr || root->key == key)
            return root;

        if (root->key < key)
            return search(root->right, key);

        return search(root->left, key);
    }

    Tree* minValueNode(Tree* node)
    {
        Tree* current = node;


        while (current != nullptr && current->left != nullptr)
            current = current->left;

        return current;
    }

    Tree *rightRotate(Tree *y)
    {
        Tree *x = y->left;
        Tree *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->ht = std::max(height(y->left),
            height(y->right)) + 1;
        x->ht = std::max(height(x->left),
            height(x->right)) + 1;

        return x;
    }

    Tree *leftRotate(Tree *x)
    {
        Tree *y = x->right;
        Tree *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->ht = std::max(height(x->left),
            height(x->right)) + 1;
        y->ht = std::max(height(y->left),
            height(y->right)) + 1;

        return y;
    }

    Tree* deleteNode(Tree* root, int key)
    {

        if (root == NULL)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);

        else if (key > root->key)
            root->right = deleteNode(root->right, key);

        else
        {

            if ((root->left == NULL) || (root->right == NULL))
            {
                Tree *temp = root->left ? root->left :root->right;


                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }else
                {
                    *root = *temp;
                }
                free(temp);
            }else
            {

                Tree* temp = minValueNode(root->right);

                root->key = temp->key;

                root->right = deleteNode(root->right,
                    temp->key);
            }
        }

        if (root == NULL)
            return root;


        root->ht = 1 + std::max(height(root->left),
            height(root->right));

        int balance = difference(root);

        if (balance > 1 && difference(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && difference(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }


        if (balance < -1 && difference(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && difference(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }


    std::string& postorder(Tree* root) 
    {
        if (root == nullptr)
            return get_values;

        postorder(root->left);
        postorder(root->right);

        get_values += std::to_string(root->key);
        get_values += " ";
        get_values += root->value;
        get_values += "\n";
    }

    std::string& inorder(Tree* root) 
    {
        if (root == nullptr)
            return get_values;

        inorder(root->left);

        get_values += std::to_string(root->key);
        get_values += " ";
        get_values += root->value;
        get_values += "\n";

        inorder(root->right);
    }

    std::string& preorder(Tree* root) 
    {
        if (root == nullptr)
            return get_values;

        get_values += std::to_string(root->key);
        get_values += " ";
        get_values += root->value;
        get_values += "\n";
        postorder(root->left);

        postorder(root->right);
    }



    int height(Tree* node)
    {
        if (node == nullptr)
            return 0;
        return 1 + std::max(height(node->left), height(node->right));
    }

    int difference(Tree* node)
    {
        int l_height = height(node->left);

        int r_height = height(node->right);

        int b_factor = l_height - r_height;

        return b_factor;
    }
};


int main() 
{
    Tree tree;
    Tree* root = nullptr;

    root = tree.insert_(root, 10, "Node 10");
    root = tree.insert_(root, 15, "Node 10");
    std::cout<< tree.search(root, 15)->value;
}