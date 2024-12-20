#include "PCSTreeReverseIterator.h"

namespace Axiom
{
	PCSTreeReverseIterator::PCSTreeReverseIterator(PCSNode* rootNode)
		: root{ rootNode }
		, current {root->GetReverse()}
		, prevNode{nullptr}
	{
	}

	PCSNode* PCSTreeReverseIterator::First()
	{
		prevNode = nullptr;
		return current = root->GetReverse();
	}

	PCSNode* PCSTreeReverseIterator::Next()
	{
		prevNode = current;

		if (!IsDone())
		{
			current = current->GetReverse();
		}
		else
		{
			current = nullptr;
		}

		return current;
	}

	bool PCSTreeReverseIterator::IsDone()
	{
		return prevNode == root;
	}

	PCSNode* PCSTreeReverseIterator::Current()
	{
		return current;
	}
}
