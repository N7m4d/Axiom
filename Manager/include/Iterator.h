#ifndef ITERATOR_H
#define ITERATOR_H

#include "DLink.h"

class Iterator
{
public:
	virtual DLink *Next() = 0;
	virtual bool IsDone() = 0;
	virtual DLink *First() = 0;
	virtual DLink *Curr() = 0;
};

#endif
