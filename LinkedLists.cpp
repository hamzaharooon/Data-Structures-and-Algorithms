/*
Hamza Haroon
DSA Notes
*/


#include<iostream>
using namespace std;

class Node{
public:
	int Value;		
	Node* Next;	
};

void printlist(Node* n){
	while(n != NULL){
		cout<<n->Value<<endl;
		n=n->Next;
	}
}

void add_to_start(Node**head, int newVal){
	//Make a new node
	Node* newNode = new Node();
	newNode->Value = newVal;
	//Put it in front of current head
	newNode->Next = *head;
	//Move head to pointer of new list
	*head = newNode;
}

void add_to_end(Node**head, int newVal){
	//Make a new node.
	Node* newNode = new Node();
	newNode->Value = newVal;
	newNode->Next = NULL;
	
	//if linkedlist is empty, new node will be head
	if (*head == NULL){
		*head = newNode;
		return;
	}
	
	//find last node
	Node* last = *head;
	while(last->Next != NULL){
		last = last->Next;
	}
	
	//add newnode after last node
	last->Next = newNode;
}

void add_after(Node*previous, int newVal){
	//Check if previous is NULL
	if (previous == NULL){
		cout<<"Previous cannot be NULL to perform this function.";
		return;
		}
		
	//Prepare a newNode
	Node* newNode = new Node();
	newNode->Value = newVal;
			
	//insert newNode after previous
	newNode->Next = previous->Next;
	previous->Next = newNode;
}

int main(){

	Node* head = new Node();
	Node* second = new Node();
	Node* third = new Node();
	
	head->Value=1;
	second->Value=2;
	third->Value=3;
	
	head->Next = second;
	second->Next = third;
	third->Next = NULL;
	
	add_to_start(&head,0);
	add_to_end(&head,4);
	add_after(second, -1);
	
	printlist(head);
}

