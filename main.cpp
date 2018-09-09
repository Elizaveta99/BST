#pragma warning (disable:4996)

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<map>

using namespace std;

map<int, bool> used;

class node
{
public:
	node(int key) : Key(key), Left(nullptr), Right(nullptr) {}
	int Key;
	node* Left;
	node* Right;
};

class BST
{

private:
	node * Root;
	node* DestroyNode(node* node)
	{
		if (node)
		{
			DestroyNode(node->Left);
			DestroyNode(node->Right);
			delete node;
		}
		return nullptr;
	}

	node* Insert(int x, node* t)
	{
		if (t == nullptr)
		{
			t = new node(x);
			t->Left = t->Right = nullptr;
		}
		else if (x < t->Key)
			t->Left = Insert(x, t->Left);
		else if (x > t->Key)
			t->Right = Insert(x, t->Right);
		return t;
	}

	void DOrder(node* t)
	{
		if (t == nullptr)
		{
			return;
		}
		cout << t->Key << "\n";
		DOrder(t->Left);
		DOrder(t->Right);
	}

	node* FindLeft(node* t)
	{
		if (t == nullptr)
			return t;
		if (t->Left == nullptr)
			return t;
		return FindLeft(t->Left);
	}

	node* RightRemove(int x, node* t)
	{
		if (t == nullptr)
		{
			return t;
		}
		node* temp;
		if (x < t->Key)
			t->Left = RightRemove(x, t->Left);
		else
			if (x > t->Key)
				t->Right = RightRemove(x, t->Right);
			else
				if (t->Left && t->Right)
				{
					temp = FindLeft(t->Right);
					t->Key = temp->Key;
					t->Right = RightRemove(t->Key, t->Right);
				}
				else
				{
					temp = t;
					if (t->Left == nullptr)
						t = t->Right;
					else
						if (t->Right == nullptr)
							t = t->Left;
					delete temp;
				}
		return t;
	}

public:
	BST() : Root(nullptr) {}
	~BST()
	{
		Root = DestroyNode(Root);
	}
	void Insert(int x)
	{
		Root = Insert(x, Root);
	}
	void Display()
	{
		DOrder(Root);
	}
	void RightRemove(int x)
	{
		Root = RightRemove(x, Root);
	}
};


int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int a, key;
	cin >> key;
	BST t;
	while (cin >> a)
	{
		if (!used[a])
			used[a] = true, t.Insert(a);
	}
	if (used[a])
		t.RightRemove(key);
	t.Display();
	// system("pause");
	return 0;
}