// Parallel BFS using OpenMP
// Compile: g++ -fopenmp 1_dfs.cpp -o output
// Run:     ./output


#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

/* Node structure */
class node
{
public:
    int data;
    node *left;
    node *right;

    node(int val)
    {
        data = val;
        left = right = NULL;
    }
};

/* BFS Class */
class Breadthfs
{
public:
    node* insert(node*, int);
    void bfs(node*);
};

/* Insert node in level order */
node* Breadthfs::insert(node *root, int data)
{
    if (!root)
        return new node(data);

    queue<node*> q;
    q.push(root);

    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();

        if (!temp->left)
        {
            temp->left = new node(data);
            return root;
        }
        else
            q.push(temp->left);

        if (!temp->right)
        {
            temp->right = new node(data);
            return root;
        }
        else
            q.push(temp->right);
    }

    return root;
}

/* Parallel BFS traversal */
void Breadthfs::bfs(node *head)
{
    if (!head) return;

    queue<node*> q;
    q.push(head);

    while (!q.empty())
    {
        int qSize = q.size();

        #pragma omp parallel for
        for (int i = 0; i < qSize; i++)
        {
            node *currNode;

            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << currNode->data << " ";
            }

            #pragma omp critical
            {
                if (currNode->left)
                    q.push(currNode->left);

                if (currNode->right)
                    q.push(currNode->right);
            }
        }
    }
}

/* Main function */
int main()
{
    Breadthfs tree;
    node *root = NULL;

    int data;
    char ans;

    do
    {
        cout << "Enter data: ";
        cin >> data;

        root = tree.insert(root, data);

        cout << "Insert more nodes? (y/n): ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    cout << "\nParallel BFS Traversal:\n";
    tree.bfs(root);

    return 0;
}
