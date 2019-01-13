#ifndef Employees_H
#define Employees_H

class Employees
{
    private:
        struct TreeNode
        {
            int employeeID;
            string employeeName;
            TreeNode *right;
            TreeNode *left;
        };

        TreeNode *root;

        /// Print using post order transversal
        void print(TreeNode* r) const
        {
            /// If node is empty, do nothing
            if( r == NULL )
                return;

            /// Traverse left subtree of node
            print(r->left);     /// recursively call print, giving it r's left child

            /// Traverse right subtree of node
            print(r->right);    /// recursively call print, giving it r's right child

            /// Process data in node
            cout << r->employeeID << ": ";
            cout << r->employeeName << endl;
        }

        void insert(TreeNode *&r, int id, string name)
        {
            /// Case 1. If tree is empty, insert the new node as the root node
            if( r == NULL )
            {
                TreeNode *newTreeNode = new TreeNode;   /// dynamically create a new node

                r = newTreeNode;    /// assign the new node to r

                newTreeNode->employeeID = id;   /// set employeeId to id

                newTreeNode->employeeName = name;   /// set employeeName to name

                newTreeNode->right = newTreeNode->left = NULL;  /// set it's children to null
            }

            /// Case 2. Else, compare new node against left or right child, depending
            ///         on whether data value of new node is < or > root node
            if( id < r->employeeID )
                insert( r->left, id, name );

            else if( id > r->employeeID )
                insert( r->right, id, name );

            /// Continue comparing and choosing right or left until NULL pointer is found

        }

        bool search(TreeNode *r, int id) const
        {
            /// Step 1. Start at root node
            if( r == NULL )
                return false;

            /// Step 2. Examine node data

            /// Step 2a. Is it desired value? Done
            if ( id == r->employeeID )
                return true;

            /// Step 2b. Else, is desired value < node data?  Repeat step 2 with left subtree
            if ( id < r->employeeID )
                search( r->left , id );

            /// Step 2c. Else, is desired value > node data? Repeat step 2 with right subtree
            else if ( id > r->employeeID )
                search( r->right, id );

            /// Continue until desired value found or NULL pointer reached
        }

        int count(TreeNode *r)
        {
            /// If node is empty, return 0
            if( r == NULL )
                return 0;

            /// Else, count the number of nodes in the tree
            else
                return ( 1+ count(r->left) + count(r->right) );
        }

        void killTree(TreeNode *r)
        {
            /// If tree is empty, do nothing
            if( r == NULL )
                return;

            /// Else if tree is not empty, then...
            else
            {
                killTree(r->left);  /// recursively call killTree, giving it's r's left child
                killTree(r->right); /// recursively call killTree, giving it's r's right child
                delete r;   /// delete r
            }
        }

        void seek(TreeNode *&r, int id)
        {
            /// If the tree is empty, do nothing
            if( r == NULL )
                return;

            /// If r's employeeID equals id, then destroy r
            if ( id == r->employeeID )
                destroy(r);

            /// If id is < the r's employeeID, then search r's left child
            else if( id < r->employeeID )
                seek( r->left, id );

            /// If id is > the r's employeeID, then search r's right child
            else if( id > r->employeeID )
                seek( r->right, id );
        }

        void destroy(TreeNode *&r)
        {
            /// Create a pointer to help destroy
            TreeNode *h = NULL;

            /// Case 1: If node to be deleted is a leaf node, replace parent node's
            /// pointer to it with a NULL pointer, then delete the node
            if( r->left == NULL && r->right == NULL)
            {
                delete r;   /// delete r

                r = NULL;   /// set r point to NULL
            }

            /// Case 2: If node to be deleted has one child node, adjust pointers so that parent of
            /// node to be deleted points to child of node to be deleted, then delete the node
            else if( r->right != NULL && r->left == NULL )
            {
                h = r;  /// set h point to r

                r = r->right;   /// set r to point to r's right child

                delete h;   /// delete h
            }

            else if( r->left != NULL && r->right == NULL )
            {
                h = r;  /// set h point to r

                r = r->left;    /// set r to point to r's left child

                delete h;   /// delete h
            }

            /// Case 3: If node to be deleted has left and right children:
            ///         a. Promote one child to take the place of the deleted node.
            ///         b. Locate the correct position for other child in subtree of promoted child.
            ///         c. Promote the right child, position left subtree underneath
            else
            {
                h = r->right;   /// set h to point to r's right child

                /// while h's left child isn't null, set h to h's left child
                while( h->left != NULL)
                    h = h->left;

                h->left = r->right;    /// set h's left child to r's right child
                h = r;  /// set h to r
                delete r;   /// delete r
                r = h;  /// set r to h
            }
        }

    public:
        Employees()
        { root = NULL; }

        ~Employees()
        { killTree(root); }

        void print() const
        { print(root); }

        bool search(int targetID) const
        { return search(root, targetID); }

        int count()
        { return count(root); }

        void insert(int eID, string eName)
        { insert(root, eID, eName); }

        void remove(int eID)
        { seek(root, eID); }
};

#endif // Employees_H
