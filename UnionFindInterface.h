#pragma once

class UnionFindInterface
{
public:
	virtual int GetSize() = 0;
	virtual bool IsConnected(int p, int q) = 0;
	virtual void UnionElements(int p, int q) = 0;
};
