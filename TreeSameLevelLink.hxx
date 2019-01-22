#ifndef __TREE_SAME_LEVEL_LINK_HXX_
#define __TREE_SAME_LEVEL_LINK_HXX_

#include <iostream>
#include <vector>
#include <memory>

using std::ostream;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::move;

class Node;
using NodePtr = std::shared_ptr<Node>;

class Node
{
public:

    Node(int v):mValue(v) {};
    Node() = delete;
    ~Node() = default;

    std::vector<NodePtr> mChildren;
    NodePtr              mRight;
    int                  mValue;
};


/**
 * each node has a link to the same level node on its right
 */
class TreeSameLevelLink
{
public:


    /**
     * Constructor
     */
    TreeSameLevelLink():mRoot(nullptr) 
    { 
        // build a tree
        mRoot = make_shared<Node>(0);

        // assume this tree has 3 levels, each node in a level has 3 children
        uint value = 1;
        for (uint count = 1; count < 4; ++count)
        {
            NodePtr newNode = make_shared<Node>(value++);
            mRoot->mChildren.push_back(move(newNode));
        }

        for (auto& entry : mRoot->mChildren)
        {
            for (uint count = 1; count < 4; ++count)
            {
                NodePtr newNode = make_shared<Node>(value++);
                entry->mChildren.emplace_back(move(newNode));
            }
        }
    };


    /**
     * Destructor
     */
    ~TreeSameLevelLink() = default;



    /**
     *
     * traverse the tree breath first and link nodes to the right
     */
    void linkRightNode()
    {
        NodePtr nextNode = mRoot;

        // loop until no more node 
        while (nextNode != nullptr) 
        {
            NodePtr myRightNode = nextNode;
            NodePtr myLeftNode = nullptr;
            do 
            {
                // go through the children and link its children to its right
                for (auto& entry : myRightNode->mChildren)
                { 
                    if (myLeftNode != nullptr)
                    {
                        myLeftNode->mRight = entry;
                    }

                    myLeftNode = entry;
                }

                myRightNode = myRightNode->mRight;
            }
            while (myRightNode != nullptr);
      
            if (nextNode->mChildren.empty())
            {   // no more child node, done
                break;
            }

 			nextNode = nextNode->mChildren[0];
					
        }	// while (nextNode != nullptr) {
    };


    /**
     *
     * traverse the tree breath first and display value at each level
     */
    void showResult()
    {
        NodePtr nextNode = mRoot;

        // loop until no more node 
        while (nextNode != nullptr) 
        {
            NodePtr myRightNode = nextNode;
            do 
            {
                std::cout << myRightNode->mValue << " ";

                myRightNode = myRightNode->mRight;
            }
            while (myRightNode != nullptr);
      
            if (nextNode->mChildren.empty())
            {   // no more child node, done
                break;
            }

 			nextNode = nextNode->mChildren[0];
					
        }	// while (nextNode != nullptr) {

        std::cout << std::endl;
    };


    /**
     * append to output stream
     *
     * @param: out - a reference to output stream to append to
     * @param: tree - a reference to TreeSameLevelLink to append to
     *
     * @return a reference to ostream appended with values of nodes of this tree, i.e, out
     */
    friend ostream& operator<<(ostream& out, const TreeSameLevelLink& tree)
    {
        // traverse down the root to print out values of nodes
        return tree.traverse(out, *tree.mRoot);
    };



protected:


private:

    /**
     * append to value of the input node to output stream and traverse down (depth first) all child nodes
     *
     * @param: out - a reference to output stream to append to
     * @param: node - a reference to BinaryTreeSameLevelLinkNode to append to
     *
     * @return a reference to ostream appended with values of nodes of this tree, i.e., out
     */
    ostream& traverse(ostream& out, Node& node) const
    {
        // append value of the input node to the output stream
        out << node.mValue << " ";

        // print out children
        for (auto& entry : node.mChildren)
        {
            traverse(out, *entry);
        }

        return out;
    };


    /**
     * ptr to a Node object
     */
    NodePtr		mRoot;


};


#endif // __TREE_SAME_LEVEL_LINK_HXX_