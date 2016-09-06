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

    T userData()                                    { return m_data; }
    const T& userData() const                       { return m_data; }
    void setUserData(const T& data)                 { m_data = data; }
    T* ptrUserData()                                { return &m_data; }
    QString toString() const                        { return m_data.toString(); }

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

#endif // TREENODE_H
