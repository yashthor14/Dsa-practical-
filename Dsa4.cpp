#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int key) {
        value = key;
        left = right = nullptr;
    }
};

class BinarySearchTree {
public:
    Node* root;

    BinarySearchTree() {
        root = nullptr;
    }

    // Recursive insert
    Node* insert(Node* root, int key) {
        if (root == nullptr) {
            return new Node(key);
        }
        if (key < root->value) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }
        return root;
    }

    // Find minimum value
    int findMin(Node* root) {
        if (root == nullptr) {
            throw runtime_error("Tree is empty");
        }
        Node* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current->value;
    }

    // Search a value
    bool search(Node* root, int key) {
        if (root == nullptr) return false;
        if (root->value == key) return true;
        return key < root->value ? search(root->left, key) : search(root->right, key);
    }

    // Inorder traversal
    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->value << " ";
            inorder(root->right);
        }
    }

    // Wrapper methods
    void insert(int key) {
        root = insert(root, key);
    }

    bool search(int key) {
        return search(root, key);
    }

    int findMin() {
        return findMin(root);
    }

    void printTree() {
        if (root == nullptr) {
            cout << "The tree is empty.\n";
        } else {
            cout << "Tree (in inorder traversal): ";
            inorder(root);
            cout << endl;
        }
    }

    void displayMenu() {
        cout << "\n--- Binary Search Tree Menu ---\n";
        cout << "1. Insert a new value\n";
        cout << "2. Find the minimum value in the tree\n";
        cout << "3. Search for a value in the tree\n";
        cout << "4. Print the tree\n";
        cout << "5. Exit\n";
        cout << "Please select an option (1-5): ";
    }
};

int main() {
    BinarySearchTree bst;
    int choice, value;

    cout << "Welcome to the Binary Search Tree Program!" << endl;

    while (true) {
        bst.displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter a value to insert: ";
                cin >> value;
                bst.insert(value);
                cout << "Value " << value << " inserted successfully!\n";
                break;

            case 2:
                if (bst.root == nullptr) {
                    cout << "The tree is empty. Cannot find minimum value.\n";
                } else {
                    cout << "The minimum value in the tree is: " << bst.findMin() << endl;
                }
                break;

            case 3:
                cout << "Enter a value to search for: ";
                cin >> value;
                if (bst.search(value)) {
                    cout << "Value " << value << " found in the tree!\n";
                } else {
                    cout << "Value " << value << " not found in the tree.\n";
                }
                break;

            case 4:
                bst.printTree();
                break;

            case 5:
                cout << "Exiting the program. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please select a valid option (1-5).\n";
        }
    }

    return 0;
}
