
#ifndef CREATEHUFFMANTREE_H
#define CREATEHUFFMANTREE_H

#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <memory>
#include <string>
#include "CharFreq.h"
#include "TreeNode.h"
#include "BranchNode.h"

using namespace std;

class NodeComparison
{
public:
	bool operator() (const shared_ptr< TreeNode<CharFreq> > & lhs, const shared_ptr<TreeNode<CharFreq> >& rhs) const
	{
		return lhs->getData().getFreq() < rhs->getData().getFreq();
	}
};

class CreateHuffmanTree
{
private:
	map<string, string> HFreqTree;
	multiset <shared_ptr<TreeNode<CharFreq> >, NodeComparison> nodeSet;
public:
	CreateHuffmanTree();
	multiset<shared_ptr<TreeNode<CharFreq> >, NodeComparison> returnTree(){ return nodeSet;  }
	void copyFreqQueue(priority_queue<CharFreq, vector<CharFreq>, CFComparison> cQueue);
	shared_ptr<TreeNode <CharFreq> > createHuffmanTree();
	void createEncode(priority_queue<CharFreq, vector<CharFreq>, CFComparison> cQueue);
	void createIndivEncode(shared_ptr<TreeNode <CharFreq> > nu, string code);
};

CreateHuffmanTree::CreateHuffmanTree()
{

}


void CreateHuffmanTree::copyFreqQueue(priority_queue<CharFreq, vector<CharFreq>, CFComparison>  cQueue)
{
	while (!cQueue.empty())
	{
		TreeNode<CharFreq> nu(cQueue.top());
		cQueue.pop();
		nodeSet.insert(shared_ptr<TreeNode <CharFreq> >(new TreeNode<CharFreq>(nu)));
	}
}

shared_ptr<TreeNode<CharFreq> > CreateHuffmanTree::createHuffmanTree()
{
	multiset<shared_ptr<TreeNode<CharFreq> >, NodeComparison>::iterator it = nodeSet.begin();
	while (nodeSet.size() > 1)
	{
		it = nodeSet.begin();
		shared_ptr<TreeNode<CharFreq> > left = *it;
		nodeSet.erase(it++);
		shared_ptr<TreeNode<CharFreq> > right = *it;
		nodeSet.erase(it);
		string c = left->getData().getKey() + right->getData().getKey();
		int f = left->getData().getFreq() + right->getData().getFreq();
		shared_ptr<BranchNode<CharFreq> > nu(new BranchNode<CharFreq>(CharFreq(f, c)));
		nu->left = left;
		//cout << left->getData().getKey() << endl;
		nu->right = right;
		//cout << right->getData().getKey() << endl;
		nodeSet.insert(nu);
		left->parent = nu;
		right->parent = nu;
	}
	it = nodeSet.begin();
	//cout << "Root: " << (*it)->getData().getKey() << " " << (*it)->getData().getFreq() << endl;
	return *it;
}

void CreateHuffmanTree::createEncode(priority_queue<CharFreq, vector<CharFreq>, CFComparison> cQueue)
{
	string code = "";
	copyFreqQueue(cQueue);
	createIndivEncode(createHuffmanTree(), code);
}

void CreateHuffmanTree::createIndivEncode(shared_ptr<TreeNode<CharFreq> > nu, string code)
{
	if (nu->parent == NULL)
	{
	}
	else if (nu->parent->left == nu)
	{
		code.append("0");
	}
	else if (nu->parent->right == nu)
	{
		code.append("1");
	}

	if (nu->left == NULL && nu->right == NULL)
	{
		HFreqTree.insert(std::pair<string, string>(nu->getData().getKey(), code));
		//cout << nu->getData().getKey() << " ";
		//cout << code << endl;
	}
	else
	{
		createIndivEncode(nu->left, code);
		createIndivEncode(nu->right, code);
	}

}
#endif CREATEHUFFMANTREE_H