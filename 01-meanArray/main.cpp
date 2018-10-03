#include <iostream>
#include <map>
#include <vector>
#include <set>

#include <cstdlib>
#include <stdexcept>
#include <iostream>
using namespace std;

template<typename Key, typename Value>
class RedBlack
{
public:
    RedBlack()
            : root(NULL), numElems(0)
    {
    }

    ~RedBlack()
    {
        DeleteNode(root);
    }

    ///************************* INSERT *****************************************************************
    void Insert(const Key& key, const Value& value)
    {
        numElems++;
        Node *node, *parent, *z;
        parent = NULL;
        node = root;
        while (node)
        {
            parent = node;
            if (key < node->key)
            {
                node->cntLeft++;
                node = node->left;
            }
            else if (key > node->key)
            {
                node->cntRight++;
                node = node->right;
            }
            else
            {
                node->value++;
                return;
            }
        }

        if (!parent)
        {
            z = root = new Node();
            z->key = key;
            z->value = value;
            z->colour = BLACK;
            z->parent = z->left = z->right = NULL;
        }
        else
        {
            z = new Node();
            z->key = key;
            z->value = value;
            z->colour = RED;
            z->parent = parent;
            z->left = z->right = NULL;

            if (z->key < parent->key)
            {
                parent->left = z;
            }
            else
            {
                parent->right = z;
            }
        }

        Node *uncle;
        bool side;
        while (z->parent && z->parent->colour == RED)
        {
            if ((side = (z->parent == z->parent->parent->left)))
            {
                uncle = z->parent->parent->right;
            }
            else
            {
                uncle = z->parent->parent->left;
            }

            if (uncle && uncle->colour == RED)
            {
                z->parent->colour = BLACK;
                uncle->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == (side ? z->parent->right : z->parent->left))
                {
                    z = z->parent;
                    side ? RotateLeft(z) : RotateRight(z);
                }

                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                side ? RotateRight(z->parent->parent) : RotateLeft(z->parent->parent);
            }
        }

        root->colour = BLACK;
    }


    ///********************************** FIND ********************************************************
    int64_t  FindSmallerEqual(const Key &key) //Value&
    {
        int64_t positionFromBegin = 0;

        if(this->numElems == 0)
            return 0;


        Node *node = root;
        while (node)
        {
            if (key < node->key)
                node = node->left;

            else if (key > node->key)
            {
                positionFromBegin += node->cntLeft + node->value;
                node = node->right;
            }
            else
            {
                int64_t val = node->value + node->cntLeft;
                positionFromBegin += val;
                return positionFromBegin; // return node->value;
            }

            ///if ( ! node ) hodnota neexistuje;
            if(!node)
                return positionFromBegin;
        }

        throw std::runtime_error("Key not found");
    }

    int64_t  FindBiggerEqual(const Key &key) //Value&
    {
        int64_t positionFromBegin = 0;

        if(this->numElems == 0)
            return 0;


        Node *node = root;
        while (node)
        {
            if (key < node->key)
            {
                positionFromBegin += node->cntRight + node->value;
                node = node->left;
            }


            else if (key > node->key)
            {
                node = node->right;
            }
            else
            {
                int64_t val = node->value + node->cntRight;
                positionFromBegin += val;
                return positionFromBegin; // return node->value;
            }

            ///if ( ! node ) hodnota neexistuje;
            if(!node)
                return positionFromBegin;
        }

        throw std::runtime_error("Key not found");
    }


    ///********************************** DELETE ********************************************************
    void Delete(const Key& key)
    {
        Node *node = root;
        while (node)
        {
            if (node->key > key)
            {
                node = node->left;
            }
            else if (node->key < key)
            {
                node = node->right;
            }
            else
            {
                break;
            }
        }

        if (!node || node->key != key)
        {
            return;
        }

        Colour original;
        Node *sub, *old;
        if (!node->left)
        {
            Transplant(node, sub = node->right);
        }
        else if (!node->right)
        {
            Transplant(node, sub = node->left);
        }
        else
        {
            old = Minimum(node->right);
            original = old->colour;
            sub = old->right;

            if (old->parent == node)
            {
                sub->parent = node;
            }
            else
            {
                Transplant(old, old->right);
                old->right = node->right;
                old->right->parent = old;
            }

            Transplant(node, old);
            old->left = node->left;
            old->left->parent = old;
            old->colour = node->colour;
        }

        delete node;
        if (original == BLACK)
        {
            bool side;
            Node *sibling;
            while (old != root && old->colour == BLACK)
            {
                if ((side = (old == old->parent->left)))
                {
                    sibling = old->parent->right;
                }
                else
                {
                    sibling = old->parent->left;
                }

                if (sibling->colour == RED)
                {
                    sibling->colour = BLACK;
                    old->parent->colour = RED;
                    side ? RotateLeft(old->parent) : RotateRight(old->parent);
                    sibling = side ? old->parent->right : old->parent->left;
                }

                if (sibling->left->colour == BLACK && sibling->right->colour == RED)
                {
                    sibling->colour = RED;
                    old = old->parent;
                }
                else
                {
                    if (BLACK == side ? sibling->right->colour : sibling->left->colour)
                    {
                        sibling->colour = RED;
                        if (side)
                        {
                            sibling->left->colour = BLACK;
                            RotateRight(sibling);
                            sibling = old->parent->right;
                        }
                        else
                        {
                            sibling->right->colour = BLACK;
                            RotateLeft(sibling);
                            sibling = old->parent->left;
                        }
                    }

                    sibling->colour = old->parent->colour;
                    old->parent->colour = BLACK;
                    if (side)
                    {
                        sibling->left->colour = BLACK;
                        RotateLeft(old->parent);
                    }
                    else
                    {
                        sibling->right->colour = BLACK;
                        RotateRight(old->parent);
                    }

                    old = root;
                }
            }
        }
    }


    void Dump()
    {
        Dump(root, 0);
    }

    int64_t Size() {
        return numElems;
    }

private:
    enum Colour
    {
        RED,
        BLACK
    };

    struct Node
    {
        Colour colour;
        Key key;
        Value value;
        Node *parent;
        Node *left;
        Node *right;

        int64_t cntLeft;
        int64_t cntRight;

        Node()
        {
            cntLeft = 0;
            cntRight = 0;
        }
    };

    Node *root;
    int64_t numElems;

    ///********************************** ROTATE LEFT ********************************************************
    void RotateLeft(Node *a)
    {
        Node *y;
        y = a->right;


        /// zmena hodnot
        a->cntRight = y->cntLeft;
        y->cntLeft = a->value + a->cntLeft + a->cntRight;


        /// 1. krok + 2. krok - pravy potomek a = levy potomek praveho potomka a
        a->right = y->left;
        if (y->left)
            y->left->parent = a;

        /// 3. krok
        y->parent = a->parent;

        /// 4.krok
        y->left = a;
        /// 5. krok - nastavit potomka rodice a na y
        if (!a->parent)
            root = y;
        else if (a == a->parent->left)
            a->parent->left = y;
        else
            a->parent->right = y;

        /// 6. krok - natavit rodice a na y
        a->parent = y;
    }

    ///********************************** ROTATE RIGHT ********************************************************
    void RotateRight(Node *y)
    {
        Node *x;

        x = y->left;
     //   exit(12);

        //todo ASIK BLBE
        y->cntLeft = x->cntRight;
        x->cntRight = y->value + y->cntLeft + y->cntRight;

        /// 1. krok + 2. krok
        y->left = x->right;
        if (x->right)
            x->right->parent = y;

        x->parent = y->parent;
        x->right = y;

        if (!y->parent)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        y->parent = x;
    }

    ///********************************** TRANSPLANT ********************************************************
    void Transplant(Node *dest, Node *src)
    {
        if (dest->parent == NULL)
        {
            root = src;
        }
        else if (dest == dest->parent->left)
        {
            dest->parent->left = src;
        }
        else
        {
            dest->parent->right = src;
        }

        if (src)
        {
            src->parent = dest->parent;
        }
    }

    ///********************************** MINIMUM ********************************************************
    Node *Minimum(Node *tree)
    {
        while (tree->left)
        {
            tree = tree->left;
        }

        return tree;
    }

    void Dump(Node *node, int64_t tabs)
    {
        if (!node)
        {
            return;
        }

        Dump(node->left, tabs + 1);

        for (int64_t i = 0; i < tabs; ++i)
        {
            std::cout << "\t\t";
        }
        std::cout << node->key << "("<< node->value<< ")" << "L" << node->cntLeft << ",R" << node->cntRight  << std::endl;// (node->colour ? "B" : "R") << std::endl;

        Dump(node->right, tabs + 1);
    }

    void DeleteNode(Node *node)
    {
        if (!node)
        {
            return;
        }

        if (node->left)
        {
            DeleteNode(node->left);
        }

        if (node->right)
        {
            DeleteNode(node->right);
        }

        delete node;
    }
};


int main()
{
    int numElem, minMean;
    scanf("%d%d", &numElem, &minMean);

    std::vector<int64_t > arrayRedux;
    for(int64_t i = 0; i < numElem; ++i) { int n; scanf("%d", &n);int64_t nn = n;arrayRedux.push_back(nn - minMean); }

    RedBlack<int64_t , int64_t> tree;
    int64_t  sum = 0;
    unsigned long long cnt = 0;
    for(auto number : arrayRedux)
    {
        sum += number;
        if(sum >= 0)
            cnt++;
        cnt += tree.FindSmallerEqual(sum);
        tree.Insert(sum,1);
    }

    printf("%llu\n", cnt);
    return 0;
}