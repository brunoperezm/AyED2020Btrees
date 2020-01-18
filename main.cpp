// CPP program to implement B* tree
#include <bits/stdc++.h>
using namespace std;

// This can be changed to any value -
// it is the order of the B* Tree
#define N 4
class node {
public:
    // key of N-1 nodes
    int key[N - 1];

    // Child array of 'N' length
    node* child[N];

    // To state whether a leaf or not; if node
    // is a leaf, isleaf=1 else isleaf=0
    int isleaf;

    // Counts the number of filled keys in a node
    int n;

    // Keeps track of the parent node
    node* parent;
};

class BTreep {
public:
    node* searchforleaf(node* root, int numeroAInsertar, node* parent, int chindex);
    node* insert( node* root, int k);
};

/**
 * @details busca la hoja donde se podría insertar el nro numeroAInsertar
 *  si el nodo root es null crea una hoja en el padre en la posición chidex
 *  y la retorna
 *  @param root el nodo root a partir del cual buscar
 *  @param numeroAInsertar el nro a insertar
 *  @param parent el padre del root
 *  @param chindex la posición en la que se insertaría un nuevo nodo en el parent si el root es nulo
 *  */
// This function searches for the leaf
// into which to insert element 'numeroAInsertar'
node* BTreep::searchforleaf(node* root, int numeroAInsertar, node* parent, int chindex)
{
    if (root) {

        // If the passed root is a leaf node, then
        // numeroAInsertar can be inserted in this node itself
        if (root->isleaf == 1)
            return root;

            // If the passed root is not a leaf node,
            // implying there are one or more children
        else {
            int i;

            /*If passed root's initial key is itself g
                reater than the element to be inserted,
                we need to insert to a new leaf left of the root*/
            if (numeroAInsertar < root->key[0])
                root = searchforleaf(root->child[0], numeroAInsertar, root, 0);

            else
            {
                // Find the first key whose value is greater
                // than the insertion value
                // and insert into child of that key
                for (i = 0; i < root->n; i++)
                    if (root->key[i] > numeroAInsertar)
                        root = searchforleaf(root->child[i], numeroAInsertar, root, i);

                // If all the keys are less than the insertion
                // key value, insert to the right of last key
                if (root->key[i - 1] < numeroAInsertar)
                    root = searchforleaf(root->child[i], numeroAInsertar, root, i);
            }
        }
    }
    else {

        // If the passed root is NULL (there is no such
        // child node to search), then create a new leaf
        // node in that location
        node* newleaf = new node;
        newleaf->isleaf = 1;
        newleaf->n = 0;
        parent->child[chindex] = newleaf;
        newleaf->parent = parent;
        return newleaf;
    }
}

/**
 * @brief inserta un numero en el el lugar que corresponda según B*trees
 * @param root es el nodo a partir del cual se puede insertar
 * @param k es el numero a insertar
 * */
node* BTreep::insert(node* root, int k)
{
    if (root) {
        node* p = searchforleaf(root, k, NULL, 0);
        node* q = NULL;
        int e = k;

        // Este bucle for dice: seguir hasta que p no sea nulo y en cada iteración el nodo p se va al padre.
        // Notar que p arranca con la hoja del nodo root
        for (int e = k; p; p = p->parent) {
            // si el nodo tiene 0 elementos insertar el numero y retornar
            if (p->n == 0) {
                p->key[0] = e;
                p->n = 1;
                return root;
            }
            // Si el nodo tiene menos numeros que el máximo
            if (p->n < N - 1) {
                int i;
                for (i = 0; i < p->n; i++) {
                    if (p->key[i] > e) {
                        for (int j = p->n - 1; j >= i; j--)
                            p->key[j + 1] = p->key[j];
                        break;
                    }
                }
                p->key[i] = e;
                p->n = p->n + 1;
                return root;
            }

            //Si el número de claves llenas es igual al máximo
            // y no es root y hay espacio en el padre
            if (p->n == N - 1 && p->parent && p->parent->n < N) {
                int m;
                for (int i = 0; i < p->parent->n; i++)
                    if (p->parent->child[i] == p) {
                        m = i;
                        break;
                    }

                // If right sibling is possible
                if (m + 1 <= N - 1)
                {
                    // q is the right sibling
                    q = p->parent->child[m + 1];

                    if (q) {

                        // If right sibling is full
                        if (q->n == N - 1) {
                            node* r = new node;
                            int* z = new int[((2 * N) / 3)];
                            int parent1, parent2;
                            int* marray = new int[2 * N];
                            int i;
                            for (i = 0; i < p->n; i++)
                                marray[i] = p->key[i];
                            int fege = i;
                            marray[i] = e;
                            marray[i + 1] = p->parent->key[m];
                            for (int j = i + 2; j < ((i + 2) + (q->n)); j++)
                                marray[j] = q->key[j - (i + 2)];

                            // marray=bubblesort(marray, 2*N)
                            // a more rigorous implementation will
                            // sort these elements

                            // Put first (2*N-2)/3 elements into keys of p
                            for (int i = 0; i < (2 * N - 2) / 3; i++)
                                p->key[i] = marray[i];
                            parent1 = marray[(2 * N - 2) / 3];

                            // Put next (2*N-1)/3 elements into keys of q
                            for (int j = ((2 * N - 2) / 3) + 1; j < (4 * N) / 3; j++)
                                q->key[j - ((2 * N - 2) / 3 + 1)] = marray[j];
                            parent2 = marray[(4 * N) / 3];

                            // Put last (2*N)/3 elements into keys of r
                            for (int f = ((4 * N) / 3 + 1); f < 2 * N; f++)
                                r->key[f - ((4 * N) / 3 + 1)] = marray[f];

                            // Because m=0 and m=1 are children of the same key,
                            // a special case is made for them
                            if (m == 0 || m == 1) {
                                p->parent->key[0] = parent1;
                                p->parent->key[1] = parent2;
                                p->parent->child[0] = p;
                                p->parent->child[1] = q;
                                p->parent->child[2] = r;
                                return root;
                            }

                            else {
                                p->parent->key[m - 1] = parent1;
                                p->parent->key[m] = parent2;
                                p->parent->child[m - 1] = p;
                                p->parent->child[m] = q;
                                p->parent->child[m + 1] = r;
                                return root;
                            }
                        }
                    }
                    else // If right sibling is not full
                    {
                        int put;
                        if (m == 0 || m == 1)
                            put = p->parent->key[0];
                        else
                            put = p->parent->key[m - 1];
                        for (int j = (q->n) - 1; j >= 1; j--)
                            q->key[j + 1] = q->key[j];
                        q->key[0] = put;
                        p->parent->key[m == 0 ? m : m - 1] = p->key[p->n - 1];
                    }
                }
            }
        }

        /*Cases of root splitting, etc. are omitted
        as this implementation is just to demonstrate
        the two-three split operation*/
    }
    else
    {
        // Create new node if root is NULL
        node* root = new node;
        root->key[0] = k;
        root->isleaf = 1;
        root->n = 1;
        root->parent = NULL;
    }
}

// Driver code
int main()
{
    /* Consider the following tree that has been obtained
    from some root split:
                6
                / \
            1 2 4 7 8 9

            We wish to add 5. This makes the B*-tree:
                4 7
                / \ \
            1 2 5 6 8 9

        Contrast this with the equivalent B-tree, in which
        some nodes are less than half full

            4 6
            / \ \
            1 2 5 7 8 9

            */

    // Start with an empty root
    BTreep btree = BTreep();
    node* root = NULL;
    // Insert 6
    root = btree.insert(root, 6);

    // Insert 1, 2, 4 to the left of 6
    root->child[0] = btree.insert(root->child[0], 1);
    root->child[0] = btree.insert(root->child[0], 2);
    root->child[0] = btree.insert(root->child[0], 4);
    root->child[0]->parent = root;


    // Insert 7, 8, 9 to the right of 6
    root->child[1] = btree.insert(root->child[1], 7);
    root->child[1] = btree.insert(root->child[1], 8);
    root->child[1] = btree.insert(root->child[1], 9);
    root->child[1]->parent = root;


    cout << "Original tree: " << endl;
    for (int i = 0; i < root->n; i++)
        cout << root->key[i] << " ";
    cout << endl;
    for (int i = 0; i < 2; i++) {
        cout << root->child[i]->key[0] << " ";
        cout << root->child[i]->key[1] << " ";
        cout << root->child[i]->key[2] << " ";
    }
    cout << endl;


    cout << "After adding 5: " << endl;

    // Inserting element '5':

    root->child[0] = btree.insert(root->child[0], 5);

    // Printing nodes

    for (int i = 0; i <= root->n; i++)
        cout << root->key[i] << " ";
    cout << endl;
    for (int i = 0; i < N - 1; i++) {
        cout << root->child[i]->key[0] << " ";
        cout << root->child[i]->key[1] << " ";
    }

    return 0;
}
