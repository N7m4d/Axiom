#ifndef PCSTREE_H
#define PCSTREE_H

namespace Axiom
{
	// forward declare
	class PCSNode;

	// PCSTree class 
	class PCSTree
	{
	public:
		// Simple data structure
		struct Info
		{
			int currNumNodes;
			int maxNumNodes;
			int currNumLevels;
			int maxNumLevels;
		};

		// constructor
		PCSTree();

		// copy constructor 
		PCSTree(const PCSTree &in) = delete;

		// assignment operator
		PCSTree &operator = (const PCSTree &in) = delete;

		// destructor
		~PCSTree();

		// get Root
		PCSNode *GetRoot() const;

		// insert
		void Insert(PCSNode *const pInNode, PCSNode *const pParent);

		// remove
		void Remove(PCSNode *const pInNode);
		void RemoveNodeAux(PCSNode* const pInNode);

		// get info
		void GetInfo(Info &info) const;
		void Print() const;
		void PrintAux(PCSNode* pNode) const;

		int CalculateNumLevels(const PCSNode* const pNode, int currLevel, int maxLevel) const;

	private:

		// Data
		Info	mInfo;
		PCSNode *pRoot;

	};

}

#endif
