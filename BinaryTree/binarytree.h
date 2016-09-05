#ifndef BINARYTREE_H
#define BINARYTREE_H

/**
  * -------------------------------------------------------------------------------------------------------------
  * Class: BinaryTree<T>
  * -------------------------------------------------------------------------------------------------------------
  * A binary tree object which consists of TreeNode<T> objects. Where T is a node data object. The data object
  * keeps the user data. It must overload some operators.
  * Operators to overload:
  * - operator <, must return true if user data object is lesser then another.
  * - operator ==, must return true if the user data are equal to other data object.
  * - operator >, must return true if this user data object is greater than another one.
  * - operator <<, is needed for behaviour Equal. The user data objects must be united.
  * And a 'toString()' method.
  *
  * EqualBehaviour
  * ---------------
  * If data of a node is equal to the new node data then a desicion is to be made.
  * The new node must be set rigth (Greater) or left (Lesser). Or nodes can be united
  * if behaviour is Equal.
  *
  * EqualBehaviour::Greater
  *     An equal node if taken as a greater one.
  * EqualBehaviour::Equal
  *     The user data of two nodes are united.
  * EqualBehaviour::Lesser
  *     The new node is equal but is taken as a lesser node.
  *
  * Tree String
  * ------------
  * It is required to implement a 'toString()' method in the user data object. It should return a QString
  * object which represents the user data.
  *
  * Required:
  * -----------
  * The template object T should keep the user data for each node. It is required to implement some
  * operator overloads (<, ==, >, <<) in the user data object T.
  * Additional it is required to implement a 'toString()' method in the user data object.
  *
  * ToDo:
  * - search function
  *
  */

#include <treenode.h>

// Node compare data type is used here as behaviour type.
typedef CompareResult EqualBehaviour;

template<class T>
class BinaryTree
{
public:
    // Constructor
    BinaryTree() :
        m_pRoot(0),
        m_equalBehaviour(Lesser)
    {

    }

    // Destructor
    ~BinaryTree()
    {
        m_pRoot->deleteChildNodes();
        delete m_pRoot;
    }

    // Public member functions.
    void insert(const T& data);
    QString toString() const;
    void setEqualBehaviour(const EqualBehaviour behaviour)      { m_equalBehaviour = behaviour; }
    EqualBehaviour equalBehaviour() const                       { return m_equalBehaviour; }
    TreeNode<T>* findNodeWith(const T& data) const;

private:
    TreeNode<T>* m_pRoot;
    EqualBehaviour m_equalBehaviour;
};



/**
 * Takes a data object of type T and creates a TreeNode<T> object in the heap.
 * This new node will be moved through the tree and added as a leave.
 * There will be made a decicion at each node. If the data object is lesser
 * the the one in the current node the new node will be moved left side. If
 * data object is greater the new node moves rigth side down the tree or is
 * added as rigth child.
 * Therefore the data T object must overload operators '<', '>', '=='.
 */
template<typename T>
void BinaryTree<T>::insert(const T& data)
{
    TreeNode<T>* pNewNode = new TreeNode<T>(data);
    if (m_pRoot == 0) {
        m_pRoot = pNewNode;
        return;
    }
    TreeNode<T>* pCurrentNode = m_pRoot;
    bool notInserted = true;
    while (notInserted) {
        CompareResult result = pCurrentNode->compareWith(pNewNode);
        if (result == Equal) {
            // Changes result to 'Equal' behaviour.
            // Could be one of:     Lesser, Equal or Greater
            result = m_equalBehaviour;
        }
        switch (result) {
        case Lesser:
            if (pCurrentNode->hasLeftChild()) {
                pCurrentNode = pCurrentNode->leftChild();
            } else {
                pCurrentNode->setLeftChild(pNewNode);
                notInserted = false;
            }
            break;
        case Equal:
            *pCurrentNode << pNewNode;
            delete pNewNode;
            notInserted = false;
            break;
        case Greater:
            if (pCurrentNode->hasRigthChild()) {
                pCurrentNode = pCurrentNode->rigthChild();
            } else {
                pCurrentNode->setRigthChild(pNewNode);
                notInserted = false;
            }
            break;
        }
    }
}

/**
 * Builds a string representation of the tree.
 * Tree will be shown from left to rigth. Root node is at the left side and the
 * tree moves to the rigth side. Leaves are at the rigth side.
 * Trees rigth side is upside in the string.
 * To get a real representation the data T object must implement the 'toString()'
 * method.
 */
template<class T>
QString BinaryTree<T>::toString() const
{
    if (m_pRoot == 0) {
        return QString("Is empty.");
    }
    QString treeString;
    m_pRoot->appendNodeString(treeString, 0);

    return treeString;
}

/**
 * Find a node in the tree which has user data equal to data.
 * @param data      A user data object with content to search for in the tree.
 * @return pNode    Returns a tree node object pointer or NULL.
 */
template<class T>
TreeNode<T> *BinaryTree<T>::findNodeWith(const T &data) const
{
    TreeNode<T>* pNode = m_pRoot;
    while (pNode) {
        CompareResult result = pNode->compareDataWith(data);
        switch (result) {
        case Greater:
            pNode = pNode->rigthChild();
            break;
        case Equal:
            return pNode;
            break;
        case Lesser:
            pNode = pNode->leftChild();
            break;
        }
    }

    return NULL;
}


#endif // BINARYTREE_H
