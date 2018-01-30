/*
 * dlist.h
 *
 *  Created on: 12 maj 2017
 *      Author: Filip Strandberg
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <iostream>

///@todo Smart pointers

struct Node{
	void* data;
	Node* next;
	Node* prev;
};

// Double Directed Linked List?
template <class T>
class Dlist{
private:
	Node* head;
	Node* tail;
	int size;
public:

	Dlist(){
		this->head = new Node;
		this->tail = new Node;
		this->head->next = this->tail;
		this->head->prev = NULL;
		this->tail->next = NULL;
		this->tail->prev = this->head;
		size = 0;
	}

	~Dlist(){
		while(!this->IsEnd(this->First())){
			this->Remove(this->Next(this->First()));
			///@todo Remove() or Delete()?
		}
		delete this->head;
		delete this->tail;
	}

	Node* First()	{ return this->head; }

	Node* Last()	{ return this->tail; }

	Node* Next(Node* n) { return n->next; }

	Node* Prev(Node* n) { return n->prev; }

	int Size()	{ return this->size; }

	bool IsEnd(Node* n)		{ return n->next == this->tail; }

	bool IsStart(Node* n)	{ return n->prev == this->head; }

	bool IsEmpty()			{ return this->head->next == this->tail; }

	T Inspect(Node* n)		{ return (T)n->data; }

	T InspectNext(Node* n)	{ return (T)n->next->data; }

	T InspectPrev(Node* n)	{ return (T)n->prev->data; }

	T InspectFirst()		{ return (T)this->InspectNext(this->First()); }

	T InspectLast()			{ return (T)this->InspectPrev(this->Last()); }

	Node* InsertFirst(T d){
		Node* newNode = new Node;
		newNode->data = (void*)d;
		newNode->prev = this->head;
		newNode->next = this->head->next;
		this->head->next->prev = newNode;
		this->head->next = newNode;
		this->size++;
		return newNode;
	}

	Node* InsertAfter(Node* n, T d){
		if(n != NULL && n != this->Last()){
			Node* newNode = new Node;
			newNode->data = (void*)d;
			newNode->prev = n;
			newNode->next = n->next;
			n->next->prev = newNode;
			n->next = newNode;
			this->size++;
			return newNode;
		}
		return NULL;
	}

	Node* InsertLast(T d){
		Node* newNode = new Node;
		newNode->data = (void*)d;
		newNode->next = this->tail;
		newNode->prev = this->tail->prev;
		this->tail->prev->next = newNode;
		this->tail->prev = newNode;
		this->size++;
		return newNode;
	}

	Node* Swap(Node* n1, Node* n2){
		if( n1 != NULL && n2 != NULL &&
			n1 != this->First() && n1 != this->Last() &&
			n2 != this->First() && n2 != this->Last() ){

			void* temp = n1->data;
			n1->data = n2->data;
			n2->data = temp;
			///@todo Swap pointers in list instead of data?
			return n1;
		}

		return NULL;
	}

	void PrintFront(){
		Node* temp = this->First();
		while(!this->IsEnd(temp)){
			std::cout << this->InspectNext(temp) << std::endl;
			temp = this->Next(temp);
		}
	}

	void PrintFrom(Node* n){
		if(n != NULL){
			Node* temp = n;
			while(!this->IsEnd(temp)){
				std::cout << this->InspectNext(temp) << std::endl;
				temp = this->Next(temp);
			}
		}
	}

	void PrintBack(){
		Node* temp = this->Last();
		while(!this->IsStart(temp)){
			std::cout << this->InspectPrev(temp) << std::endl;
			temp = this->Prev(temp);
		}
	}

	void Clear(){
		while(!this->IsEnd(this->First())){
			this->Remove(this->Next(this->First()));
		}
	}

	void Remove(Node* n){
		if(n != NULL){
			if(n == this->First()){
				n = this->Next(n);
			}
			else if(n == this->Last()){
				n = this->Prev(n);
			}
			n->prev->next = n->next;
			n->next->prev = n->prev;
			delete n;
		}
	}

	void Delete(Node* n){
		if(n != NULL){
			if(n == this->First()){
				n = this->Next(n);
			}
			else if(n == this->Last()){
				n = this->Prev(n);
			}
			n->prev->next = n->next;
			n->next->prev = n->prev;
			delete n->data;
			delete n;
		}
	}

	Node* SortMerge(){
		return NULL;
	}

	Node* SortBubble(){
		return NULL;
	}

};

#endif /* DLIST_H_ */
