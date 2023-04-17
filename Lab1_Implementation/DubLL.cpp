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
void DoublyLinkedList::display_forward() { // from start to end
	Node* current = head;
	while (current != nullptr) {
		cout << current->getData() << " ";
		current = current->getNext();
	}
	cout << endl;
}
void DoublyLinkedList::display_backward() { // from end to start
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
bool DoublyLinkedList::isSorted() {
	int i = 0;
	while (i < listSize - 1){
		if (nodeAt(i)->getData() <= nodeAt(i + 1)->getData()) {
			i++;
		}
		else if(nodeAt(i)->getData() > nodeAt(i + 1)->getData()) {
			return false;
		}
		else {
			return true;
		}
	}
}
int DoublyLinkedList::binarySearch(int data) { //sorta but yeah not really
	Node* shit = head;
	int start = 0;
	int i = start;
	int dest = listSize / 2;
	while (i != listSize) {
		if (listSize == 1) {
			if (shit->getData() < data) {
				return i;
			}
			else if (shit->getData() >= data) {
				return i++;
			}
		}
		while (i != dest) {
			shit = shit->getNext();
			i++;
		}
		if (shit->getData()||listSize==0) {
			return i;
		}
		else {
			if (shit->getData() > data) {
				i = start;
				dest /= 2;
			}
			else {
				dest += dest / 2;
			}
		}
	}
}
DoublyLinkedList bSort(DoublyLinkedList inputList, int n, int last) {
	if (inputList.isSorted()) {
		cout << "sorted base list:" << endl;
		inputList.display_forward();
		inputList.add(new Node(last), inputList.binarySearch(last));
		return inputList;
	}
	else {
		last = (inputList.nodeAt(n - 1))->getData(); //save data of last node
		inputList.remove(n - 1); //remove the last node
		bSort(inputList, inputList.size(), last); //recursive call with shortened list
	}
}

int main() {
	cout << "Generating list..." << endl;
	srand(time(0)); //random seed generated from time at start of program, thus changing each time it is launched	
	DoublyLinkedList list;
	int i = 0;
	while (i < 8) {
		list.add(new Node(rand()% 1000), 0);
		i++;
	}
	//manual list for precise testing, comment out the while loop and vice versa
	/*list.add(new Node(9), 0);
	list.add(new Node(2), 0);
	list.add(new Node(666), 0);
	list.add(new Node(33), 0);
	list.add(new Node(15), 0);*/
	list.display_forward();
	cout << "Unsorted list shown above, proceeding with sort..." << endl;
	list = bSort(list, list.size(), 0);
	cout << "Final list:" << endl;
	list.display_forward();
	return 0;
}