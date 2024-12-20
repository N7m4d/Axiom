#ifndef	DLINK_ITERATOR_H
#define	DLINK_ITERATOR_H

#include "Iterator.h"

class DLinkIterator : public Iterator
{
public:
	DLinkIterator();

	virtual DLink *Next() override;
	virtual bool IsDone() override;
	virtual DLink *First() override;
	virtual DLink *Curr() override;

	void Reset(DLink *pHead);

private:
	void privClear();

public:
	DLink *pHead;
	DLink *pCurr;
	bool bDone;
};

#endif

