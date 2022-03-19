#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>
#include<math.h>
using namespace std;


MultiMap::MultiMap() {
	this->m = 8;
	this->length = 0;
	this->T = new TElem[m];
	for (int i = 0; i < this->m; i++)
		T[i] = NULL_TELEM;
}// theta(m)


void MultiMap::add(TKey c, TValue v) {
	TElem elem;
	elem.first = c;
	elem.second = v;
	if (this->length == m)
	{
		rehash();	
	}
	int i = 0;
	int pos = h(c, i);
	while (i < this->m && T[pos] != NULL_TELEM && T[pos] != DELETED)
	{
		i++;
		pos = h(c, i);
	}
	
	T[pos] = elem;
	
	this->length++;
}//best case: theta(1)
//worst case:theta(m*m)
//complexity: O(m*m)


bool MultiMap::remove(TKey c, TValue v) {
	TElem elem;
	elem.first = c;
	elem.second = v;
	bool returnValue = false;

	int i = 0;
	bool stop = false;
	while (i < m && stop == false)
	{
		int pos = h(c, i);
		if (T[pos] == elem) // if i found the element
		{
			T[pos] = DELETED;
			returnValue = true;
			this->length--;
			stop = true;
		}
		else
			if (T[pos] == NULL_TELEM) // if i don t find the element but the position is occupied 
			{
				stop = true;

			}
			else
				i++;
	}	
	return returnValue;
}//best case: theta(1)
//worst case:theta(m)
//complexity: O(m)


vector<TValue> MultiMap::search(TKey c) {
	vector<TValue> v;
	int i = 0;
	bool stop = false;
	while(i < m  && stop == false)
	{
		int pos = h(c, i);
		if (T[pos].first == c) // if i found the element
		{
			v.push_back(T[pos].second);
			i++;
		}
		else
			if (T[pos] == NULL_TELEM) // if i don t find the element but the position is occupied or deleted
			{
				stop = true;
			}
			else
				i++;
	}
	return v ;
}//best case: theta(1)
//worst case:theta(m)
//complexity: O(m)


int MultiMap::size() const {
	return this->length;
}// theta(1)



bool MultiMap::isEmpty() const {
	if (this->length == 0)
		return true;
	else
		return false;
}//theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}//theta(1)




int MultiMap::h(TKey e,int i) 
{
	//return ((abs(e)) % m + (i%m + (i%m)*(i%m))/2) %m ;
	
	long long int x, y;
	x  = long long int(i);
	y = long long int(i+1);
	if (x % 2 == 0)
		x = x / 2;
	else
		y = y / 2;
	long long int ml = long long int(m);
	x = (x * y) % ml;
	long long int intermediar = long long int(abs(e)%m);
	intermediar = (intermediar + x) % ml;
	int val = int (intermediar);
	return val;

}//theta(1)

void MultiMap::rehash()
{
	int aux = this->m;
	this->m = this->m * 2;
	TElem* newArray = new TElem[this->m];
	for (int i = 0; i < m; i++)
	{
		newArray[i] = NULL_TELEM;
	}

	for(int current = 0;current < aux;current++)
	{

		if (T[current] != NULL_TELEM && T[current] != DELETED)
		{
			int i = 0;
			int pos = h(T[current].first, i);
			while (i < this->m && newArray[pos] != NULL_TELEM) 
			{
				i++;
				pos = h(T[current].first, i);
			}//O(m)
			newArray[pos] = T[current];

		}

	}//O(m*m)
	
	delete[] this->T;

	this->T = newArray;
}//best:theta(m)
//worst:theta(m*m)
//O(m*m)


 
MultiMap::~MultiMap() {
	delete[] this->T;
}//theta(1)

