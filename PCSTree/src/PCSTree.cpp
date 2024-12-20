#include "PCSTree.h"
#include "PCSNode.h"

namespace Axiom
{
	// constructor
	PCSTree::PCSTree()
		: mInfo()
		, pRoot(nullptr)
	{
	};

	// destructor
	PCSTree::~PCSTree()
	{
		//delete pRoot;
	};

	// get Root
	PCSNode* PCSTree::GetRoot() const
	{
		return pRoot;
	}

	// insert
	void PCSTree::Insert(PCSNode* const pInNode, PCSNode* const pParent)
	{
		if (pParent == nullptr)
		{
			pRoot = pInNode;

			mInfo.currNumLevels++;
			mInfo.maxNumLevels++;
		}
		else
		{
			PCSNode* child = pParent->GetChild();

			if (child != nullptr)
			{
				child->SetPrevSibling(pInNode);
				pInNode->SetNextSibling(child);
			}

			PCSNode* parentForward = pParent->GetForward();
			if (parentForward)
			{
				parentForward->SetReverse(pInNode);
			}

			pInNode->SetParent(pParent);
			pInNode->SetReverse(pParent);
			pInNode->SetForward(parentForward);
			if (!pInNode->GetForward())
			{
				pRoot->SetReverse(pInNode);
			}

			pParent->SetChild(pInNode);
			pParent->SetForward(pInNode);

			int newDepth = 1;

			PCSNode* tmp = pInNode;
			while (tmp->GetParent() != nullptr)
			{
				newDepth++;
				tmp = tmp->GetParent();
			}

			if (newDepth > mInfo.currNumLevels)
			{
				mInfo.currNumLevels = newDepth;
				mInfo.maxNumLevels = mInfo.currNumLevels;
			}
		}

		mInfo.currNumNodes++;
		mInfo.maxNumNodes++;
	}

	// Remove
	void PCSTree::Remove(PCSNode* const pInNode)
	{
		if (pInNode == nullptr)
		{
			return;
		}

		RemoveNodeAux(pInNode);

		mInfo.currNumLevels = CalculateNumLevels(pRoot, 1, 1);
		if (pInNode == pRoot)
		{
			mInfo.currNumLevels = 0;
		}
	}

	void PCSTree::RemoveNodeAux(PCSNode* const pInNode)
	{
		PCSNode* parent = pInNode->GetParent();
		PCSNode* nextSibling = pInNode->GetNextSibling();
		PCSNode* prevSibling = pInNode->GetPrevSibling();
		PCSNode* reverse = pInNode->GetReverse();
		PCSNode* forward = pInNode->GetForward();

		// Update the siblings of the node to be removed
		if (nextSibling != nullptr)
		{
			nextSibling->SetPrevSibling(prevSibling);
		}

		if (prevSibling != nullptr)
		{
			prevSibling->SetNextSibling(nextSibling);
		}
		else if (parent != nullptr)
		{
			parent->SetChild(nextSibling);
		}

		if (reverse)
		{
			reverse->SetForward(forward);
		}

		if (forward)
		{
			forward->SetReverse(reverse);
		}

		if (pInNode == pRoot->GetReverse())
		{
			pRoot->SetReverse(reverse);
		}

		// Recursively remove all child nodes
		PCSNode* child = pInNode->GetChild();
		while (child != nullptr)
		{
			nextSibling = child->GetNextSibling();
			RemoveNodeAux(child);
			child = nextSibling;
		}

		// Reset the node's properties
		pInNode->SetParent(nullptr);
		pInNode->SetChild(nullptr);
		pInNode->SetNextSibling(nullptr);
		pInNode->SetPrevSibling(nullptr);

		mInfo.currNumNodes--;
	}

	// get tree info
	void PCSTree::GetInfo(Info& info) const
	{
		info = mInfo;
	}

	void PCSTree::Print() const
	{
		PrintAux(pRoot);
	}

	void PCSTree::PrintAux(PCSNode* pNode) const
	{
		if (pNode == nullptr)
		{
			return;
		}

		while (pNode != nullptr)
		{
			pNode->PrintChildren();
			if (pNode->GetChild() != nullptr)
			{
				PrintAux(pNode->GetChild());
			}

			pNode = pNode->GetNextSibling();
		}
	}

	int PCSTree::CalculateNumLevels(const PCSNode* const pNode, int currLevel, int maxLevels) const
	{
		if (pNode == nullptr)
		{
			return maxLevels;
		}

		if (maxLevels < currLevel)
		{
			maxLevels = currLevel;
		}

		maxLevels = CalculateNumLevels(pNode->GetChild(), currLevel + 1, maxLevels);
		maxLevels = CalculateNumLevels(pNode->GetNextSibling(), currLevel, maxLevels);

		return maxLevels;
	}
}
