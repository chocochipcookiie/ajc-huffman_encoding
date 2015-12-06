#ifndef BRANCHNODE_H
#define BRANCHNODE_H

#include <memory>
#include "TreeNode.h"

template <typename T>
class BranchNode : public TreeNode<T>
{
	public:
		BranchNode(T nu) : TreeNode(nu) {}
};

#endif BRANCHNODE_H