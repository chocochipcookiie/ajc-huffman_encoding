#ifndef TREENODE_H
#define TREENODE_H

#include <memory>

template <class T>
class TreeNode
{
	protected:
		T data;
	public:
		shared_ptr<TreeNode<T> > parent;
		shared_ptr<TreeNode<T> > left;
		shared_ptr<TreeNode<T> > right;
		TreeNode(T nu) : data(nu){}
		T getData() const { return data; }
};

#endif TREENODE_H