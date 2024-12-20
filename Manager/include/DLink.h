#ifndef DLINK_H
#define DLINK_H

class DLink
{
public:

	DLink();


	virtual void Wash() = 0;

	// Becomes optional with a virtual with default implementation
	virtual char *GetName()
	{
		return nullptr;
	}

	virtual bool Compare(DLink *pTargetNode) = 0;

	void Clear();
	virtual void Dump();


	// Data: -----------------------------
	DLink *pNext;
	DLink *pPrev;

};


#endif
