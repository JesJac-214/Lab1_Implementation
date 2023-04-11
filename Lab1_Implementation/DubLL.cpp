#include <iostream>
#include "DubLL.h"
using namespace std;

Node::Node() {
	data = 0;
}
Node::Node(int inData) {
	data = inData;
}
int Node::getData() {
	return data;
}
void Node::setData(int inData) {
	data = inData;
}
Node* Node::getNext() {
	return next;
}
void Node::setNext(Node* newNext) {
	next = newNext;
}
Node* Node::getPrev() {
	return prev;
}
void Node::setPrev(Node* newPrev) {
	prev = newPrev;
}

bool DoublyLinkedList::add(Node* data, int pos) {
	if (data == nullptr || pos > listSize) {
		return false;
	}
	else {
		Node* prev = nullptr;
		Node* next = nullptr;

		if (listSize != 0 && pos == listSize) {
			prev = tail;
		}
		else if (listSize != 0) {
			next = nodeAt(pos);
			prev = next->getPrev();
		}

		data->setPrev(prev);
		data->setNext(next);

		if (prev == nullptr) {
			head = data;
		}
		else {
			prev->setNext(data);
		}
		if (next == nullptr) {
			tail = data;
		}
		else {
			next->setPrev(data);
		}

		listSize++;
		return true;
	}
}
bool DoublyLinkedList::remove(int pos) {
	Node* node = nodeAt(pos);
	if (node == nullptr) {
		return false;
	}
	else {
		Node* prev = node->getPrev();
		Node* next = node->getNext();

		if (prev == nullptr) {
			head = next;
		}
		else {
			prev->setNext(next);
		}
		if (next == nullptr) {
			tail = prev;
		}
		else {
			next->setPrev(prev);
		}
		delete node;
		listSize--;
		return true;
	}
}
bool DoublyLinkedList::replace(Node* old, Node* nieuw) {
	int pos = search(old);

	if (pos == -1 || old == nullptr || nieuw == nullptr) {
		return false;
	}
	else {
		remove(pos);
		add(nieuw, pos);
		return true;
	}
}
int DoublyLinkedList::search(Node* data) {
	int i = 0;
	Node* node;
	for (node = head; node != data && node != nullptr; node = node->getNext()) {
		i++;
	}
	if (node == nullptr) {
		return -1;
	}
	else {
		return i;
	}
}
Node* DoublyLinkedList::nodeAt(int pos) {
	if (pos >= listSize) {
		return nullptr;
	}
	else {
		Node* node = head;
		for (int i = 0; i < pos; i++) {
			node = node->getNext();
		}
		return node;
	}
}
void DoublyLinkedList::display_forward() {
	Node* current = head;
	while (current != nullptr) {
		cout << current->getData() << " ";
		current = current->getNext();
	}
	cout << endl;
}
void DoublyLinkedList::display_backward() {
	Node* current = tail;
	while (current != nullptr) {
		cout << current->getData() << " ";
		current = current->getPrev();
	}
	cout << endl;
}
int DoublyLinkedList::size() {
	return listSize;
}

int main() {
	srand(time(0));
	Node* n0 = new Node(rand()%256);
	Node* n1 = new Node(rand()%256);
	Node* n2 = new Node(rand()%256);
	Node* n3 = new Node(rand()%256);
	Node* n4 = new Node(rand()%256);

	DoublyLinkedList list;

	list.add(n0, 0); 
	list.add(n1, 1);
	list.add(n2, 2);
	list.add(n3, 1);
	list.add(n4, 3);
	list.display_forward();
	return 0;
}