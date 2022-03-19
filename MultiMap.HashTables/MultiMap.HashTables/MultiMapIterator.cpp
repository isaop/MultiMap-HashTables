#include "MultiMapIterator.h"
#include "MultiMap.h"
#include<iostream>

MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	/*this->currentPosition = 0;
	while (this->currentPosition < this->col.m && (this->col.T[currentPosition] == NULL_TELEM || this->col.T[currentPosition] == DELETED))
		this->currentPosition ++;*/
	first();
	
}//best:theta(1)
//worst: theta(m)
//complexity:O(m)

TElem MultiMapIterator::getCurrent() const{
	if (!(valid()))
	{
		throw std::exception();
	}
		
	return this->col.T[this->currentPosition];
}
//theta(1)
bool MultiMapIterator::valid() const {
	return (this->currentPosition < this->col.m);
}//theta(1)

void MultiMapIterator::next() {
	if (!(valid()))
		throw std::exception();
	this->currentPosition++;
	while (this->currentPosition < this->col.m && (this->col.T[currentPosition] == NULL_TELEM || this->col.T[currentPosition] == DELETED))
		this->currentPosition++;
}//best:theta(1)
//worst: theta(m)
//complexity:O(m)

void MultiMapIterator::first() {
	this->currentPosition = 0;
	while (this->currentPosition < this->col.m && (this->col.T[currentPosition] == NULL_TELEM || this->col.T[currentPosition] == DELETED))
		this->currentPosition++;

}//best:theta(1)
//worst: theta(m)
//complexity:O(m)

