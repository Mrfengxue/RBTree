#include <iostream>
using namespace std;
#include<cassert>
#include<queue>
#include<iomanip>

enum Color{RED,BLACK};

template<typename _T>
class RBTree
{
public:
	RBTree():root(NULL),NIL(NULL)
	{
		NIL = _BuyNode(0);
		NIL->parent = root;
		NIL->color = BLACK;
	}
	~RBTree(){}

	struct RBNode
	{
		int color;
		_T value;
		RBNode *left;
		RBNode *right;
		RBNode *parent;
	};

	void RBInsert(const _T &val)
	{
		RBNode *tmp = _BuyNode(val);
		RBNode *p = root;
		if(root == NULL)
		{
			root = tmp;
			root->color = BLACK;
			root->parent = NIL;
			return ;
		}
		while(p != NIL)
		{
			if(tmp->value < p->value)
			{
				if(p->left == NIL)
					break;
				else
					p = p->left;
			}else
			{
				if(p->right == NIL)
					break;
				else
					p = p->right;
			}
		}
		tmp->parent = p;
		if(tmp->value < p->value)
		{
			p->left = tmp;
		}else
		{
			p->right = tmp;
		}
		RBInsert_FixUp(tmp);
	}

	void RBInsert_FixUp(RBNode *z)
	{
		RBNode *y = NIL;//zµÄÊå¸¸
		RBNode *zpa = z->parent;
		while(zpa->color == RED)
		{
			if(zpa->parent->left == z->parent)
			{
				y = zpa->parent->right;
				if(y->color == RED)
				{
					zpa->color = BLACK;
					y->color = BLACK;
					zpa->parent->color = RED;
					z = zpa->parent;
					zpa = z->parent;
				} 
				else 
				{
					if(zpa->right == z)
					{
						z = zpa;
						RoateLeft(z);
						zpa = z->parent;
						zpa->color = BLACK;
						zpa->parent->color = RED;
						RoateRight(zpa->parent);
					}
					else
					{
						zpa->color = BLACK;
						zpa->parent->color = RED;
						RoateRight(zpa->parent);
					}
				}
			}
			else
			{
				y = zpa->parent->left;
				if( y->color == RED)
				{
					zpa->color = BLACK;
					y->color = BLACK;
					zpa->parent->color = RED;
					z = zpa->parent;
					zpa = z->parent;
				} 
				else 
				{
					if(zpa->left == z)
					{
						z = zpa;
						RoateRight(z);
						zpa = z->parent;
						zpa->color = BLACK;
						zpa->parent->color = RED;
						RoateLeft(zpa->parent);
					}
					else
					{
						zpa->color = BLACK;
						zpa->parent->color = RED;
						RoateLeft(zpa->parent);
					}
				}
			}
		}
		root->color = BLACK;
	}	

	RBNode * Find_RBNode(const _T&val)
	{
		RBNode *p = root;
		while(p != NULL)
		{
			if(p->value == val)
			{
				break;
			}
			else if(val < p->value)
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
		return p;
	}

	void RBDelete(const _T& val)
	{
		RBNode *z = Find_RBNode(val);
		RBNode *y = NIL;
		RBNode *x = NIL;
		if(z == NULL)
		{
			return ;
		}
		if(z->left == NIL || z->right == NIL)
			y = z;
		else
			y = Next(z);

		if(y->left != NIL)
		{
			x = y->left;
		}else
		{
			x = y->right;
		}
		x->parent = y->parent;
		if(y->parent == NIL)
		{
			root = x;
		}
		else if(y->parent->left == y)
		{
			y->parent->left = x;
		}
		else
		{
			y->parent->right = x;
		}

		if(y != z)
		{
			z->value = y->value;
		}

		if(y->color == BLACK)
		{
			RB_Delete_FixUp(x);
		}
		_FreeNode(y);
	}


	void RB_Delete_FixUp(RBNode *x)
	{
		RBNode *w = NIL;
		while(x != root && x->color == BLACK)
		{
			if(x == x->parent->left)
			{
				w = x->parent->right;
				if(w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					RoateLeft(x->parent);
					w = x->parent->right;
				}

				if(w->left->color == BLACK && w->right->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else if(w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					RoateRight(w);
					w = x->parent->right;
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					RoateLeft(x->parent);
					x = root;
				}
				else
				{
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					RoateLeft(x->parent);
					x = root;
				}
			}
			else
			{
				w = x->parent->left;
				if(w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					RoateRight(x->parent);
					w = x->parent->left;
				}

				if(w->left->color == BLACK && w->right->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else if(w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					RoateLeft(w);
					w = x->parent->left;
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					RoateRight(x->parent);
					x = root;
				}
				else
				{
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					RoateRight(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}
	void print()
	{
		queue<RBNode *> que;
		RBNode *p = root;
		if(p != NIL)
		{
			que.push(p);
		}

		while(!que.empty())
		{
			p = que.front();
			que.pop();
			cout<<setw(4)<<p->value<<setw(4)<<p->color<<endl;
			if(p->left != NIL)
			{
				que.push(p->left);
			}
			if(p->right != NIL)
			{
				que.push(p->right);
			}
		}
		cout<<endl;
	}

private:
	void RoateLeft(RBNode *p)
	{
		RBNode *newroot = p->right;
		p->right = newroot->left;
		newroot->left = p;
		if(p->right != NIL)
		{
			p->right->parent = p;
		}
		newroot->parent = p->parent;
		if(p->parent == NIL)
		{
			root = newroot;
		}
		else if(p->parent->left == p)
		{
			p->parent->left = newroot;
		}
		else
		{
			p->parent->right = newroot;
		}
		p->parent = newroot;

	}

	void RoateRight(RBNode *p)
	{
		RBNode *newroot = p->left;
		p->left = newroot->right;
		newroot->right = p;
		if(p->left != NIL)
		{
			p->right->parent = p;
		}
		newroot->parent = p->parent;
		if(p->parent == NIL)
		{
			root = newroot;
		}
		else if(p->parent->left == p)
		{
			p->parent->left = newroot;
		}
		else
		{
			p->parent->right = newroot;
		}
		p->parent = newroot;

	}

	RBNode *_BuyNode(const _T& val)
	{
		RBNode *p = (RBNode *)malloc(sizeof(RBNode));
		assert(p != NULL);
		p->value = val;
		p->color = RED;
		p->parent = NULL;
		p->left = NIL;
		p->right = NIL;
		return p;		
	}

	void _FreeNode(RBNode *p)
	{
		free(p);
	}

	RBNode *Next(RBNode *z)
	{
		z = z->left;
		while(z != NIL && z->right != NIL)
			z = z->right;
		return z;
	}
	RBNode *NIL;
	RBNode *root;
};




int main(int argc, char *argv[])
{
	RBTree<int> Rb;
	int array[]={13,15,11,8,17,1,22,25,27,6}; 
	int n = sizeof(array)/sizeof(array[0]);
	int i;
	for(i=0;i < n;++i)
	{
		Rb.RBInsert(array[i]);
	}
	cout<<"RBTree:"<<endl;
	Rb.print();
	for(i=0;i < n;++i)
	{
		cout<<"Delete "<<array[i]<<" after:"<<endl;
		Rb.RBDelete(array[i]);
		Rb.print();
	}
	return 0;
}
