/*
 * [PROG]		: Red Black Tree
 * [AUTHOR]		: Ashfaqur Rahman <sajib.finix@gmail.com>
 * [PURPOSE]		: Red-Black tree is an algorithm for creating a balanced
 * 			  binary search tree data structure. Implementing a red-balck tree
 * 			  data structure is the purpose of this program.
 * 
 * [DESCRIPTION]	: Its almost like the normal binary search tree data structure. But
 * 			  for keeping the tree balanced an extra color field is introduced to each node.
 *			  This tree will mantain bellow properties.
 *				  1. Nodes can be either RED or BLACK.
 *				  2. ROOT is BLACK.
 *				  3. Leaves of this tree are null nodes. Here null is represented bya special node NILL.
 *				     Each NILL nodes are BLACK. So each leave is BLACK.
 * 				  4. Each RED node's parent is BLACK
 *				  5. Each simple path taken from a node to descendent leaf has same number of black height. 
 *				     That means each path contains same number of BLACK nodes.
 */

#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct node{
	long long int  key;
	long long int  color;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct node *ROOT;
struct node *NILL;

void left_rotate(struct node *x);
void right_rotate(struct node *x);
void tree_print(struct node *x);
void red_black_insert(long long int  key);
void red_black_insert_fixup(struct node *z);
struct node *tree_search(long long int  key);
struct node *tree_minimum(struct node *x);

struct node *tree_search(long long int  key){
	struct node *x;

	x = ROOT;
	while(x != NILL && x->key != key){
		if(key < x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}

	return x;
}

struct node *tree_minimum(struct node *x){
	while(x->left != NILL){
		x = x->left;
	}
	return x;
}



void red_black_insert(long long int  key){
	struct node *z, *x, *y;
	z = (struct node *) malloc(sizeof(struct node));

	z->key = key;
	z->color = RED;
	z->left = NILL;
	z->right = NILL;

	x = ROOT;
	y = NILL;


	while(x != NILL){
		y = x;
		if(z->key <= x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}

	if(y == NILL){
		ROOT = z;
	}
	else if(z->key <= y->key){
		y->left = z;
	}
	else{
		y->right = z;
	}

	z->parent = y;

	red_black_insert_fixup(z);
}



void red_black_insert_fixup(struct node *z){
	while(z->parent->color == RED){

		if(z->parent == z->parent->parent->left){

			if(z->parent->parent->right->color == RED){
				z->parent->color = BLACK;
				z->parent->parent->right->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			else{
				
				if(z == z->parent->right){
					z = z->parent;
					left_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent);
			}
		}

		else{
			
			if(z->parent->parent->left->color == RED){
				z->parent->color = BLACK;
				z->parent->parent->left->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			else{
				if(z == z->parent->left){
					z = z->parent;
					right_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
		}
	}

	ROOT->color = BLACK;
}


void left_rotate(struct node *x){
	struct node *y;
	
	y = x->right;
	x->right = y->left;
	if(y->left != NILL){
		y->left->parent = x;
	}

	y->parent = x->parent;
	if(y->parent == NILL){
		ROOT = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}
	
	y->left = x;
	x->parent = y;
}


void right_rotate(struct node *x){
	struct node *y;

	y = x->left;
	x->left = y->right;
	if(y->right != NILL){
		y->right->parent = x;
	}

	y->parent = x->parent;
	if(y->parent == NILL){
		ROOT = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;	
	}
	else{
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}
