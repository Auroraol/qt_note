#include <iostream>
using namespace std;

struct TreeNode
{
	char val;
	TreeNode* left;
	TreeNode* right;
	int bf;
	TreeNode(char val) : val(val) { left = right = NULL; }
};

TreeNode* create()
{
	char val;
	TreeNode* myTree;
	cin >> val;
	if (val == '#')
	{
		myTree = NULL;
	}
	else
	{
		myTree = new TreeNode(val);
		if (myTree != NULL)
		{
			myTree->left = create();
			myTree->right = create();
		}
	}
	return myTree;
}

void traversal(TreeNode* cur)
{
	if (!cur)
		return;
	cout << cur->bf << " ";
	traversal(cur->left);   //  ��
	traversal(cur->right);  //  ��
}

int getDepth(TreeNode* root)
{
	if (root == NULL)
		return 0;
	return 1 + max(getDepth(root->left), getDepth(root->right));
}

// �������
void bf(TreeNode* root)
{
	int LNum, RNum;
	if (root == NULL)
	{
		return;
	}
	bf(root->left);
	bf(root->right);
	LNum = getDepth(root->left);      //��ǰ�ڵ��������Ķ�
	RNum = getDepth(root->right);     //��ǰ�ڵ��������Ķ�
	root->bf = LNum - RNum;         //��ǰ�ڵ��ƽ������
}

//˼�룺�ݹ�ļ���ÿ���ڵ��������������������ȣ�Ȼ�����������-��������ȼ�Ϊƽ������
int main(void)
{
	TreeNode* pRoot;
	cout << "������: ";
	pRoot = create();
	bf(pRoot);
	traversal(pRoot);
	while (1);
	return 0;
}