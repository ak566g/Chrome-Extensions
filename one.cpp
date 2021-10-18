#include<iostream>
#include<cstdlib>
#include<fstream>
 
 using namespace std;
 
class Node{
	public:
	int data;
	Node* left;
	Node* right;
	Node* parent;
	char color;
};
struct Node* head=NULL;

Node* Rotate_right(Node *&head,Node *&parent){
	Node* temp,*temp2;
	temp=parent->left;
	parent->left=temp->right;
	if(parent->left!=NULL){
		parent->left->parent=parent;
	}
	temp->parent=parent->parent;
	if(parent->parent==NULL){
		head=temp;
	}
	else if(parent==parent->parent->left){
		parent->parent->left=temp;
	}
	else{
		parent->parent->right=temp;
	}
	temp->right=parent;
	parent->parent=temp;
	return parent;
	
}
Node* Rotate_left(Node *&head,Node *&parent){
	Node* temp,*temp2;
	temp=parent->left;
	temp2=parent;
	swap(parent->color,parent->parent->color);
	parent->left=parent->parent;
	parent->parent->right=temp;
	parent->parent=parent->parent->parent;
	return parent;
}

void inorder(Node* new_head){
	if(new_head==NULL){
	return;
	}
	inorder(new_head->left);
	cout<<new_head->data<<" "<<new_head->color<<endl;
	inorder(new_head->right);
}
void RBTree(Node *&head,Node *&new_head ){
	while((new_head!=head) && (new_head->parent->color=='R') && (new_head->color!='B')){
		Node* head_parent=new_head->parent;
		Node* grandparent=new_head->parent->parent;
		if(head_parent==grandparent->left){
				
			if(grandparent->right!=NULL && grandparent->right->color=='R'){
				grandparent->color='R';
				grandparent->right->color='B';
				head_parent->color='B';
				new_head=grandparent;
			}
			else{
				if(new_head==head_parent->left){
					if(grandparent==head){
						// head=Rotate_right(head,head_parent);
					//	new_head=head;
							swap(head_parent->color,grandparent->color);
					 	new_head=head_parent;
						}
					 else if(grandparent->data>head_parent->data){
					    grandparent->parent->left=Rotate_right(head,head_parent);
				 		new_head=head_parent;
				 		head_parent=new_head->parent;
					 }
					 else if(grandparent==grandparent->parent->right){
					 grandparent->parent->right=Rotate_right(head,head_parent);
				 			new_head=head_parent;
				 			head_parent=new_head->parent;
					 }
				}	
		}
	}
	if(head_parent==grandparent->right){
			if(grandparent->left!=NULL && grandparent->left->color=='R'){
				grandparent->color='R';
				grandparent->left->color='B';
				head_parent->color='B';
				new_head=grandparent;
			}
			else{
				if(new_head==head_parent->right){
					if(grandparent==head){
						 head=Rotate_left(head,head_parent);
						new_head=head;
						}
					 else if(grandparent==grandparent->parent->right){
					 grandparent->parent->right=Rotate_right(head,head_parent);
				 		new_head=head_parent;
				 		head_parent=new_head->parent;
					 }
					 else if(grandparent==grandparent->parent->left){
					 grandparent->parent->left=Rotate_right(head,head_parent);
				 			new_head=head_parent;
				 			head_parent=new_head->parent;
					 }
				}	
		}
	}
}
if(new_head==head)
new_head->color='B';
}
Node* insert(Node* new_head,Node* new_node){
	if(new_head==NULL){
	new_head=new_node;
	cout<<"created";
	return new_head;
	}
	if(new_head->data>new_node->data){
	new_head->left=insert(new_head->left,new_node);
	new_head->left->parent=new_head;
	}
	if(new_head->data<new_node->data){
	new_head->right=insert(new_head->right,new_node);
	new_head->right->parent=new_head;
	}
	return new_head;
}

Node* creatFirst(Node* head,int data){
	Node* newNode=new Node;
	newNode->data=data;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->parent=NULL;
	newNode->color='B';
	head=newNode;
	return head;
}

void new_nodecreat(Node *&head,int data){
	Node* newNode=new Node;
	newNode->data=data;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->parent=NULL;
	newNode->color='R';
	head=insert(head,newNode);
	RBTree(head,newNode);
}

int main(){
		int  n,arr[1000],number,k=0;
		fstream file("input.txt");
		while(file>>number){
			arr[k++]=number;
		}
		n=arr[0]; 
		head=creatFirst(head,arr[1]);
		for(int i=2;i<=n;i++)
			new_nodecreat(head,arr[i]);		
		inorder(head);	
}
