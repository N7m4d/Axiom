#include "PCSTreeForwardIterator.h"

namespace Axiom
{
	PCSTreeForwardIterator::PCSTreeForwardIterator(PCSNode* rootNode)
		: root{ rootNode }
		, current{ rootNode }
	{
	}

	PCSNode* PCSTreeForwardIterator::First()
	{
		return current = root;
	}

	PCSNode* PCSTreeForwardIterator::Next()
	{
		if (!IsDone())
		{
			current = current->GetForward();
		}
		
		return current;
	}

	bool PCSTreeForwardIterator::IsDone()
	{
		return !current;
	}

	PCSNode* PCSTreeForwardIterator::Current()
	{
		return current;
	}
}
