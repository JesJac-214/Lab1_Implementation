#pragma once

class Node {
private:
	int data;
	Node* next;
	Node* prev;
public:
	Node();
	Node(int);
	int getData();
	void setData(int data);
	Node* getNext();
	void setNext(Node* next);
	Node* getPrev();
	void setPrev(Node* prev);
};

class DoublyLinkedList {
private:
	Node* head;
	Node* tail;
	int listSize = 0;
public:
	bool add(Node* data, int pos);
	bool remove(int pos);
	bool replace(Node* old, Node* nieuw);
	int search(Node* data);
	Node* nodeAt(int pos);
	void display_forward();
	void display_backward();
	int size();
	bool isSorted();
};