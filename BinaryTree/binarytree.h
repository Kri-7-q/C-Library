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
  * - remove function
  */

#include <treenode.h>
#include <QDebug>


template<class T>
class BinaryTree
{
    friend class TreeNode<T>;

public:

    enum EqualBehaviour { EqualToLesser = -1, KeepEqual = 0, EqualToGreater = 1 };
    enum CompareResult { Lesser = -1, Equal = 0, Greater = 1 };

    // Constructor
    BinaryTree() :
        m_pRoot(0),
        m_equalBehaviour(EqualToLesser)
    {

    }

    // Destructor
    ~BinaryTree()
    {
        removeDescendantsFrom(m_pRoot);
        delete m_pRoot;
    }

    // Public member functions.
    void insert(const T& data);
    void insert(TreeNode<T> * const pNewNode);
    QString toString() const;
    void setEqualBehaviour(const EqualBehaviour behaviour)      { m_equalBehaviour = behaviour; }
    EqualBehaviour equalBehaviour() const                       { return m_equalBehaviour; }
    TreeNode<T>* findNodeWith(const T& data) const;
    void removeDescendantsFrom(TreeNode<T> *pNode);

private:
    TreeNode<T>* m_pRoot;
    EqualBehaviour m_equalBehaviour;

    // Private member functions.
    void appendNodeString(TreeNode<T> *pNode, QString& treeString, const int space) const;
    CompareResult compareNodes(const TreeNode<T>* const pNode, const TreeNode<T>* const pCompareNode) const;
    CompareResult compareNodesWithData(const TreeNode<T>* const pNode, const T& data) const;
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
    insert(pNewNode);
}

/**
 * @brief BinaryTree::insert
 * @param pNewNode
 */
template<class T>
void BinaryTree<T>::insert(TreeNode<T> * const pNewNode)
{
    if (m_pRoot == 0) {
        m_pRoot = pNewNode;
        return;
    }
    TreeNode<T>* pCurrentNode = m_pRoot;
    bool notInserted = true;
    while (notInserted) {
        CompareResult result = compareNodes(pCurrentNode, pNewNode);
        if (result == Equal) {
            // Changes result to 'Equal' behaviour.
            // Could be one of:     Lesser, Equal or Greater
            result = (CompareResult)m_equalBehaviour;
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
    appendNodeString(m_pRoot, treeString, 0);

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
        CompareResult result = compareNodesWithData(pNode, data);
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

/**
 * Walk recursively through the tree and build a string representation.
 * @param pNode         The next node.
 * @param treeString    A string reference to append node strings.
 * @param space         A space value depending on the current deepth.
 */
template<class T>
void BinaryTree<T>::appendNodeString(TreeNode<T>* pNode, QString &treeString, const int space) const
{
    if (pNode->hasRigthChild()) {
        appendNodeString(pNode->rigthChild(), treeString, space + 5);
    }

    QString spaceString(space, ' ');
    treeString.append(spaceString).append(pNode->toString());

    if (pNode->hasLeftChild()) {
        appendNodeString(pNode->leftChild(), treeString, space + 5);
    }
}

/**
 * Compare two nodes with their node data.
 * @param pNode         Node pointer to a node which is to compare with another one.
 * @param pCompareNode  The other node to compare.
 * @return              Return Lesser (-1) if pCompareNode data is lesser then data of pNode.
 *                      Return Greater (1) if pCompareNode data is greater. Otherwise Equal (0).
 */
template<class T>
typename BinaryTree<T>::CompareResult BinaryTree<T>::compareNodes(const TreeNode<T> * const pNode, const TreeNode<T> * const pCompareNode) const
{
    return compareNodesWithData(pNode, pCompareNode->userData());
}

/**
 * Compare data of a node with other data. To search in the tree.
 * @param pNode         The node which data is to compare.
 * @param data          Data to compare.
 * @return              Return Lesser (-1) if data is lesser then node data.
 *                      Return Greater (1) if data is greater then node data.
 *                      Return Equal (0) if node data and data are equal.
 */
template<class T>
typename BinaryTree<T>::CompareResult BinaryTree<T>::compareNodesWithData(const TreeNode<T> * const pNode, const T &data) const
{
    const T& nodeData = pNode->userData();
    if (data < nodeData) {
        return Lesser;
    }
    if (data > nodeData) {
        return Greater;
    }

    return Equal;
}

/**
 * Delete the tree or a part of the tree from memory.
 * @param pNode     From this node all childes will be deleted.
 */
template<class T>
void BinaryTree<T>::removeDescendantsFrom(TreeNode<T>* pNode)
{
    if (pNode->hasLeftChild()) {
        TreeNode<T>* pLeftNode = pNode->leftChild();
        removeDescendantsFrom(pLeftNode);
        delete pLeftNode;
        pNode->setLeftChild(NULL);
    }
    if (pNode->hasRigthChild()) {
        TreeNode<T>* pRigthNode = pNode->rigthChild();
        removeDescendantsFrom(pRigthNode);
        delete pRigthNode;
        pNode->setRigthChild(NULL);
    }
}


#endif // BINARYTREE_H
