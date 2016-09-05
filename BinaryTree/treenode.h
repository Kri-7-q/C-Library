#ifndef TREENODE_H
#define TREENODE_H

/**
  * -------------------------------------------------------------------------------------------------------------
  * Class: TreeNode<T>
  * -------------------------------------------------------------------------------------------------------------
  * Represents one node in a binary tree. Keeps a pointer to a left and a rigth child node.
  * A pointer to a TreeNode<T> object can point to a single node object or to whole tree.
  * This class should not be used. It is handled by the BinaryTree class.
  *
  * Node data
  * ---------
  * The node data type must overload some operators and implement some functions.
  * It needs compare operators <, >, == to compare tree nodes.
  * If equal data should not take place in the tree as a own tree node then it needs to implement
  * an overload of operator <<. This operator overload should unit two tree nodes into one.
  * A 'toString()' method is required to get a string representation of the tree.
  */


#include <QString>


// This data type is returned when two nodes were compared.
enum CompareResult { Lesser = -1, Equal = 0, Greater = 1 };


template<class T>
class TreeNode
{
public:
    TreeNode(const T& data) :
        m_data(data),
        m_pLeftChild(0),
        m_pRigthChild(0)
    {

    }

    CompareResult compareWith(const TreeNode* const pNode) const;
    CompareResult compareDataWith(const T& data) const;
    QString appendNodeString(QString& treeString, const int space) const;
    void deleteChildNodes();
    T userData() const                              { return m_data; }
    void setUserData(const T& data)                 { m_data = data; }
    T* ptrUserData()                                { return &m_data; }

    // Public inline methods
    bool hasLeftChild() const                       { return m_pLeftChild != 0; }
    bool hasRigthChild() const                      { return m_pRigthChild != 0; }
    void setLeftChild(TreeNode* pNode)              { m_pLeftChild = pNode; }
    void setRigthChild(TreeNode* pNode)             { m_pRigthChild = pNode; }
    TreeNode* leftChild() const                     { return m_pLeftChild; }
    TreeNode* rigthChild() const                    { return m_pRigthChild; }

    // Operator overload.
    void operator << (const TreeNode* const rhs)    { m_data << rhs->m_data; }

private:
    T m_data;
    TreeNode* m_pLeftChild;
    TreeNode* m_pRigthChild;
};



/**
 * Compares this node with another node. It will compare the user data objects.
 * @param pNode     A node to compare with this node.
 * @return          Lesser if user data of pNode is lesser the user data of this node.
 *                  Greater if user data of pNode is greater. Or Equal if user data
 *                  of both nodes are Equal.
 */
template<class T>
CompareResult TreeNode<T>::compareWith(const TreeNode* const pNode) const
{
    return compareDataWith(pNode->m_data);
}

/**
 * Compares the user data of this node with another user data object.
 * @param data      A reference to a user data object which is compared with the one of this node.
 * @return          Lesser if user data of pNode is lesser the user data of this node.
 *                  Greater if user data of pNode is greater. Or Equal if user data
 *                  of both nodes are Equal.
 */
template<class T>
CompareResult TreeNode<T>::compareDataWith(const T &data) const
{
    if (data > m_data) {
        return Greater;
    }
    if (data == m_data) {
        return Equal;
    }

    return Lesser;
}

/**
 * Recursive
 * This method should not be called. It is used to get a string representation of
 * the tree. It is call from BinaryTree objects 'toString()' method.
 * @param treeString        A string reference where node string is added.
 * @param space             How much space are required at this point in the tree.
 * @return treeString       The string representation of the tree after recursive walkthrough.
 */
template<class T>
QString TreeNode<T>::appendNodeString(QString& treeString, const int space) const
{
    if (hasRigthChild()) {
        m_pRigthChild->appendNodeString(treeString, space + 5);
    }

    QString nodeData = QString(space, ' ').append(m_data.toString());
    treeString.append(nodeData);

    if (hasLeftChild()) {
        m_pLeftChild->appendNodeString(treeString, space + 5);
    }

    return treeString;
}

/**
 * Recursive
 * Delete all child nodes down the tree starting at this node.
 */
template<class T>
void TreeNode<T>::deleteChildNodes()
{
    if (hasLeftChild()) {
        m_pLeftChild->deleteChildNodes();
        delete m_pLeftChild;
        m_pLeftChild = NULL;
    }
    if (hasRigthChild()) {
        m_pRigthChild->deleteChildNodes();
        delete m_pRigthChild;
        m_pRigthChild = NULL;
    }
}

#endif // TREENODE_H
