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
	if (listSize == 1) {
		return true;
	}
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
/*int DoublyLinkedList::binarySearch(int data) { //sorta but yeah not really
	Node* shit = head;
	int start = 0;
	int end = listSize - 1;
	int i = start;
	int dest = listSize / 2;
	if (listSize == 2) {
		dest = 0;
	}
	while (i != end) {
		while (i != dest) {
			shit = shit->getNext();
			i++;
		}
		if (dest == 0||listSize == 1||start == dest||i == end) {
			if (shit->getData() < data) {
				i++;
				return i;
			}
			else if (shit->getData() >= data) {
				return i;
			}
		}
		else {
			if (shit->getData() > data) {
				i = 0;
				shit = head;
				end -= dest / 2;
				if (start > 0) {
					start -= dest / 2;
				}
				dest /= 2;
			}
			else {
				if ((dest - start) == 1) {
					start++;
				}
				else {
					start += dest;
				}
				if (dest == 1 || (end - dest) == 1) {
					dest++;
				}
				else {
					dest += dest / 2;
				}
			}
		}
	}
}*/

//BinarySearch copied from geeksforgeeks.com
// function to find out middle element
struct Node* middle(Node* start, Node* last)
{
	if (start == NULL)
		return NULL;

	struct Node* slow = start;
	struct Node* fast = start->getNext();

	while (fast != last)
	{
		fast = fast->getNext();
		if (fast != last)
		{
			slow = slow->getNext();
			fast = fast->getNext();
		}
	}

	return slow;
}

// Function for implementing the Binary
// Search on linked list
int DoublyLinkedList::binarySearch(Node* head, int value)
{
	struct Node* start = head;
	struct Node* last = NULL;
	Node* mid = middle(start, last);

	do
	{
		// Find middle
		mid = middle(start, last);

		// If middle is last
		if (mid == last)
			return listSize;

		// If value is present at middle
		if (mid->getData() == value)
			return search(mid);

		// If value is more than mid
		else if (mid->getData() < value)
			start = mid->getNext();

		// If the value is less than mid.
		else
			last = mid;

	} while (last == NULL ||
		last != start);

	// value not present
	if (start == last) {
		return search(start);
	}
	else if (mid->getData() < value) {
		return search(mid);
	}
	else {
		mid->getNext();
		return search(mid);
	}
}
//end of copying


DoublyLinkedList unsortedList;
DoublyLinkedList bSort(DoublyLinkedList inputList, int n) {
	if (inputList.isSorted()) {
		cout << "sorted base list:" << endl; //errors for a stack overflow of i here despite i not being initiated yet???
		inputList.display_forward();
		int i = 0;
		while (i != unsortedList.size()) {
			int insertVal = unsortedList.nodeAt(0)->getData();
			inputList.add(new Node(insertVal), inputList.binarySearch(inputList.nodeAt(0), insertVal));
			unsortedList.remove(0);
		}	
		return inputList;
	}
	else {
		unsortedList.add(new Node((inputList.nodeAt(n - 1))->getData()), 0); //put value of last node into list of unsorted values
		inputList.remove(n - 1); //remove the last node
		bSort(inputList, inputList.size()); //recursive call with shortened list
	}
}

int main() {
	cout << "Generating list..." << endl;
	srand(time(0)); //random seed generated from time at start of program, thus changing each time it is launched	
	DoublyLinkedList list;
	int i = 0;
	while (i < 2980) { //too big and various errors pop up
		list.add(new Node(rand()% 10000), 0);
		i++;
	}
	//manual list for precise testing, comment out the while using loop and vice versa
	/*list.add(new Node(616), 0);
	list.add(new Node(138), 0);
	list.add(new Node(829), 0);
	list.add(new Node(233), 0);
	list.add(new Node(496), 0);
	list.add(new Node(561), 0);
	list.add(new Node(861), 0);
	list.add(new Node(717), 0);
	list.add(new Node(165), 0);
	list.add(new Node(712), 0);
	list.add(new Node(994), 0);
	list.add(new Node(181), 0);
	list.add(new Node(503), 0);
	list.add(new Node(344), 0);
	list.add(new Node(641), 0);*/
	list.display_forward();
	cout << "Unsorted list shown above, proceeding with sort..." << endl;
	list = bSort(list, list.size());
	cout << "Final list:" << endl;
	list.display_forward();
	return 0;
}