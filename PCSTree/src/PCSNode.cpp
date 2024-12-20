#include "PCSTree.h"
#include "PCSNode.h"

namespace Axiom
{
	// constructor
	PCSNode::PCSNode()
		: pParent(nullptr)
		, pChild(nullptr)
		, pNextSibling(nullptr)
		, pPrevSibling(nullptr)
		, pForward(nullptr)
		, pReverse(nullptr)
	{
		memset(&pName[0], 0x0, PCSNode::NAME_SIZE);
	}

	// copy constructor
	PCSNode::PCSNode(const PCSNode& in)
		: pParent(in.pParent)
		, pChild(in.pChild)
		, pNextSibling(in.pNextSibling)
		, pPrevSibling(in.pPrevSibling)
		, pForward(in.pForward)
		, pReverse(in.pReverse)
	{
		SetName(in.pName);
	}

	// Specialize Constructor
	PCSNode::PCSNode(PCSNode* const pInParent, PCSNode* const pInChild, PCSNode* const pInNextSibling, PCSNode* const pInPrevSibling, const char* const pInName)
		: pParent(pInParent)
		, pChild(pInChild)
		, pNextSibling(pInNextSibling)
		, pPrevSibling(pInPrevSibling)
		, pForward(nullptr)
		, pReverse(nullptr)
	{
		SetName(pInName);
	}

	PCSNode::PCSNode(const char* const pInName)
		: pParent(nullptr)
		, pChild(nullptr)
		, pNextSibling(nullptr)
		, pPrevSibling(nullptr)
		, pForward(nullptr)
		, pReverse(nullptr)
	{
		SetName(pInName);
	}

	// destructor
	PCSNode::~PCSNode()
	{
		pParent = nullptr;
		pChild = nullptr;
		pNextSibling = nullptr;
		pPrevSibling = nullptr;
		pForward = nullptr;
		pReverse = nullptr;
	}

	// assignment operator
	PCSNode& PCSNode::operator = (const PCSNode& in)
	{
		pParent = in.pParent;
		pChild = in.pChild;
		pNextSibling = in.pNextSibling;
		pPrevSibling = in.pPrevSibling;
		pForward = in.pForward;
		pReverse = in.pReverse;

		SetName(in.pName);

		return *this;
	}

	void PCSNode::SetParent(PCSNode* const pIn)
	{
		pParent = pIn;
	}

	void PCSNode::SetChild(PCSNode* const pIn)
	{
		pChild = pIn;
	}

	void PCSNode::SetNextSibling(PCSNode* const pIn)
	{
		pNextSibling = pIn;
	}

	void PCSNode::SetPrevSibling(PCSNode* const pIn)
	{
		pPrevSibling = pIn;
	}

	void PCSNode::SetForward(PCSNode *const pIn)
	{
		pForward = pIn;
	}

	void PCSNode::SetReverse(PCSNode *const pIn)
	{
		pReverse = pIn;
	}

	PCSNode* PCSNode::GetParent(void) const
	{
		return pParent;
	}

	PCSNode* PCSNode::GetChild(void) const
	{
		return pChild;
	}

	PCSNode* PCSNode::GetNextSibling(void) const
	{
		return pNextSibling;
	}

	PCSNode* PCSNode::GetPrevSibling(void) const
	{
		return pPrevSibling;
	}

	PCSNode *PCSNode::GetForward(void) const
	{
		return pForward;
	}

	PCSNode *PCSNode::GetReverse(void) const
	{
		return pReverse;
	}

	PCSNode::Code PCSNode::SetName(const char* const pInName)
	{
		if (pInName == nullptr)
		{
			return Code::FAIL_NULL_PTR;
		}

		const size_t len = strlen(pInName);

		if (len == 0)
		{
			return Code::FAIL_RETURN_NOT_INITIALIZED;
		}

		if (len > PCSNode::NAME_SIZE)
		{
			memcpy_s(pName, PCSNode::NAME_SIZE, pInName, PCSNode::NAME_SIZE);
		}
		else
		{
			memcpy_s(pName, PCSNode::NAME_SIZE, pInName, len);
		}

		pName[PCSNode::NAME_SIZE - 1] = '\0';

		return Code::SUCCESS;
	}

	PCSNode::Code PCSNode::GetName(char* const pOutBuffer, unsigned int sizeOutBuffer) const
	{
		if (sizeOutBuffer == 0)
		{
			return Code::FAIL_RETURN_NOT_INITIALIZED;
		}

		if (pOutBuffer == nullptr)
		{
			return Code::FAIL_NULL_PTR;
		}

		if (sizeOutBuffer < PCSNode::NAME_SIZE)
		{
			memcpy_s(pOutBuffer, sizeOutBuffer, pName, sizeOutBuffer);
		}
		else
		{
			memcpy_s(pOutBuffer, sizeOutBuffer, pName, PCSNode::NAME_SIZE);
		}

		pOutBuffer[sizeOutBuffer - 1] = '\0';

		return Code::SUCCESS;
	}

	void PCSNode::PrintNode() const
	{
		Trace::out("%s \n", pName);
		Trace::out(" Parent: %s \n", pParent ? pParent->pName : nullptr);
		Trace::out(" Child: %s \n", pChild ? pChild->pName : nullptr);
		Trace::out(" Next sibling: %s \n", pNextSibling ? pNextSibling->pName : nullptr);
		Trace::out(" Previous sibling: %s \n", pPrevSibling ? pPrevSibling->pName : nullptr);
	}

	void PCSNode::PrintChildren() const
	{
		Trace::out("%s \n", pName);
		Trace::out(" Children: \n");

		const PCSNode* child = pChild;
		while (child != nullptr)
		{
			Trace::out("	%s \n", child->pName);
			child = child->pNextSibling;
		}
	}

	void PCSNode::PrintSiblings() const
	{
		if (pParent != nullptr)
		{
			Trace::out("%s \n", pName);
			Trace::out(" Siblings: \n");

			const PCSNode* sibling = pParent->pChild;
			while (sibling != nullptr)
			{
				Trace::out("	%s \n", sibling->pName);
				sibling = sibling->pNextSibling;
			}
		}
	}

	int PCSNode::GetNumSiblings() const
	{
		int numSiblings = 1;

		if (pParent != nullptr)
		{
			const PCSNode* sibling = pParent->pChild->pNextSibling;
			while (sibling != nullptr)
			{
				++numSiblings;
				sibling = sibling->pNextSibling;
			}
		}

		return numSiblings;
	}

	int PCSNode::GetNumChildren() const
	{
		int numChildren = 0;

		const PCSNode* child = pChild;
		while (child != nullptr)
		{
			++numChildren;
			child = child->pNextSibling;
		}

		return numChildren;
	}
}
