#ifndef LEAFNODE_H
#define LEAFNODE_H

#include "TreeNode.h"

class LeafNode : public TreeNode<T>
{
	public:
		LeafNode(T data);
};


LeafNode::LeafNode(T data) : TreeNode(data)
{
	left = NULL;
	right = NULL;
}
#endif LEAFNODE_H