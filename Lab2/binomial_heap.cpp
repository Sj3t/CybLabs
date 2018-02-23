/*Step into the digital dimension to find ourselves a new quality of life*/

/*Michael "Hyst3r1a" Gorshenin, 2018*/

////////////
//Binomial heap
////////////

/*Binomial heap is a number of binomial trees, in which:
 1. Every node's key in each of the trees is NOT BIGGER than its parent's key;
 2. For each positive number K there is only 1 tree with the k degree;

 There is a very wide range of possible number of children for each node, so children are represented
 as a single-linked list, and parent connects to them via left-most child.

 Binomial heap is the base of "prioritaized queue" data structure.

 Operations available for that heap are:
 1. Key insertion O(log n)
 2. Getting minimum key O(log n)
 3. Extracting minimum key Θ(log n)
 4. Merging 2 heaps Ω(log n)
 5. Key decreasing Θ(log n)
 6. Key deletion Θ(log n)

 Key deletion is done by decreasing the key value to minimum(it makes it go all the way up to the root), and then extract minimum key.
*/


#include <iostream>
#include <string>

using namespace std;

/*Binomial heap node*/
struct Node{
	int key;
	Node *parent; 
    Node *child;// pointer to leftmost child
	Node *sibling;// pointer to the node's "brother" to the right. This is used because node's children are saved as a linked list
	int degree;// the node's degree - number of children it has.
};


    Node *Merge(struct Node *h1, struct Node *h2){

		Node *head = NULL;


		 //Heap emptiness check block
	if (h1 == NULL && h2 == NULL){
		return h1;

	}
	else if (h1 == NULL && h2 != NULL){
		return h2;

	}
	else if (h1 != NULL && h2 == NULL){
		return h1;

	}
	   /*Both heaps are not empty
	   This means that we have to:
	   1. Merge both root lists.
	   2. Determine if there are trees with equal degree.
	   3. For each equal degree found - merge trees by making the lower tree root a child of
	   a higher tree root.
	   4. Re-check if newcomer trees have equal degrees with others. Repeat until there is 1 or no trees of each degree.


	   TODO: stop writing c++ code to avoid pointer brainfuck
	   */
	else{
		 Node *t1 = h1;
		 Node *t2 = h2;
		 Node *temp2;
		 Node *temp = head;
		while (t1 != NULL && t2 != NULL){


			if (t1->degree <= t2->degree){
				temp2 = t1;
				t1 = t1->sibling;
			}
			else{
				temp2 = t2;
				t2 = t2->sibling;
			}
			if (head == NULL){
				head = temp2;
				temp = temp2;
			}
			else{

				temp->sibling = temp2;
				temp = temp2;
			}
		}
		while (t1 != NULL){

			temp2 = t1;
			t1 = t1->sibling;

			temp->sibling = temp2;
			temp = temp2;
		}
		while (t2 != NULL){

			temp2 = t2;
			t2 = t2->sibling;

			temp->sibling = temp2;
			temp = temp2;
		}

		
		Node *t3 = head;

		while (t3->sibling != NULL){
			Node *t4 = t3->sibling;
			Node *t5 = t4->sibling;
			if (t3->degree != t4->degree){

				t3 = t3->sibling;
			}
			else{
				if (t5 != NULL){
					if (t4->degree != t5->degree){

						if (t3->key <= t4->key){
							t3->sibling = t5;
							t4->sibling = t3->child;
							t3->child = t4;
							t3->degree++;

						}
						else{

							Node *t6 = head;
							if (t3 == head){
								t3->sibling = t4->child;
								t4->child = t3;
								t4->degree++;
								head = t4;
								t3 = t4;

							}
							else{
								while (t6->sibling != t3){
									t6 = t6->sibling;
								}
								t6->sibling = t4;
								t3->sibling = t4->child;
								t4->child = t3;
								t3 = t4;
								t3->degree++;
							}

						}
					}
					else{
						t3 = t3->sibling;
					}
				}
				else{

					if (t3->key <= t4->key){
						t3->sibling = NULL;
						t4->sibling = t3->child;
						t3->child = t4;
						t3->degree++;

					}
					else{
						struct Node *t6 = head;
						if (t3 == head){
							t3->sibling = t4->child;
							t4->child = t3;
							t4->degree++;
							head = t4;
							t3 = t4;
						}
						else{
							while (t6->sibling != t3){
								t6 = t6->sibling;
							}
							t6->sibling = t4;
							t3->sibling = t4->child;
							t4->child = t3;
							t4->degree++;
							t3 = t4;
						}

					}
				}
			}
		}

		return head;
	}
}

    Node *InsertKey(int newKey, Node *head) {

	struct Node *temp = new Node;
	temp->key = newKey;
	temp->parent = temp->sibling = temp->child = NULL;
	temp->degree = 0;
	struct Node *headNew = Merge(temp, head);

	return headNew;

}

    Node *ExtractMin(struct Node *head ){
		//This function first finds, then prints, and then extracts the min key of the heap
		/* 
		Extraction is made up of following steps:
		1. Cycling through the list of roots to find the lowest key.
		2. Delete the found root node. This would form a new binomial heap, formed up of trees its children
		3. Merge the main and a newly formed heap.
		
		*/



	if (head == NULL){
		cout << "The heap is empty, can't continue" << endl;
		return head;
	}
	else{

		int Min = head->key;
		struct Node *temp = head;
		struct Node *MinNode = head;
		while (temp != NULL){
			if (temp->key < Min){
				Min = temp->key;
				MinNode = temp;
			}

			temp = temp->sibling;
		}

	
			cout << "Minimum Extracted : " << MinNode->key << endl;
		



		if (MinNode == head){
			struct Node *p1 = head->sibling;
			struct Node *p2 = head->child;
			if (p2 == NULL){
				return p1;
			}
			else if (p2->sibling == NULL){
				return Merge(p2, p1);
			}
			else{
				struct Node *q1 = p2;
				struct Node *q2 = p2;
				while (q1->sibling != NULL){
					q1 = q1->sibling;
				}
				while (q2->sibling != q1){
					q2 = q2->sibling;
				}
				struct Node *ExtractHead = q1;
				while (q1 != p2){
					q2 = p2;
					while (q2->sibling != q1){
						q2 = q2->sibling;
					}
					q1->sibling = q2;
					q1 = q2;

				}
				q1->sibling = NULL;
				return Merge(ExtractHead, p1);
			}
		}
		else{
			struct Node *p1 = head;
			struct Node *p3 = head;
			struct Node *p2 = MinNode->child;
			while (p3->sibling != MinNode){
				p3 = p3->sibling;
			}
			struct Node *p4 = MinNode->sibling;
			p3->sibling = p4;
			if (p2 == NULL){
				return p1;
			}
			else if (p2->sibling == NULL){
				return Merge(p2, p1);
			}
			else{
				struct Node *q1 = p2;
				struct Node *q2 = p2;
				while (q1->sibling != NULL){
					q1 = q1->sibling;
				}
				while (q2->sibling != q1){
					q2 = q2->sibling;
				}
				struct Node *ExtractHead = q1;
				while (q1 != p2){
					q2 = p2;
					while (q2->sibling != q1){
						q2 = q2->sibling;
					}
					q1->sibling = q2;
					q1 = q2;

				}
				q1->sibling = NULL;


				return Merge(ExtractHead, p1);
			}



		}

	}
}

    void showHeap(struct Node *x, int depth){

	//classic ASCII-style comand line left table representation.
	if (x->sibling != NULL)
		showHeap(x->sibling, depth);
	cout << endl;
	if ((x->child != NULL) || (x->parent == NULL)){
		for (int i = 0; i < depth; i++) cout << "    ";
		cout << x->key;
		if (x->child == NULL) cout << endl;
	}
	else{
		for (int i = 0; i < depth; i++) cout << "    ";
		cout << x->key << endl;
	}
	if (x->child != NULL){
		showHeap(x->child, depth + 1);
	}
}

    void showBinomialHeap(struct Node *head){
		//Helper function for heap emptiness check. 
		//Brought into a method for compability reasons.
	cout << "Heap: " << endl;
	if (head == NULL){ 
		cout << "Empty heap" << endl;
	}
	else showHeap(head, 0);
}

	void Control(Node *headMain) {
		

		while (true){
		string s;
		cin >> s;
		if (s[0] == 'clr'){
		headMain = NULL;
		}
		else if (s == "ins"){
		int Number;
		cin >> Number;
		headMain = InsertKey(Number, headMain);
		}
		else if (s == "show"){
		showBinomialHeap(headMain);
		}
		else if (s == "extract"){
		headMain =	ExtractMin(headMain);
		}
		else if (s[0] == 'stop'){ 
		break;
		}
		}
		

	}

    void main(){
	//Creating an empty tree
	struct Node *headMain = NULL;
	
	//Yay, random keys!:3
	for (int i = 0; i < 128; ++i)
	{
		headMain = InsertKey(rand()%100, headMain);
		
	}
	//showing the heap
	showBinomialHeap(headMain);
	Control(headMain);
}