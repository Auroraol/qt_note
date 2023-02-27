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
	traversal(cur->left);   //  左
	traversal(cur->right);  //  右
}

int getDepth(TreeNode* root)
{
	if (root == NULL)
		return 0;
	return 1 + max(getDepth(root->left), getDepth(root->right));
}

// 后序遍历
void bf(TreeNode* root)
{
	int LNum, RNum;
	if (root == NULL)
	{
		return;
	}
	bf(root->left);
	bf(root->right);
	LNum = getDepth(root->left);      //当前节点左子树的度
	RNum = getDepth(root->right);     //当前节点右子树的度
	root->bf = LNum - RNum;         //当前节点的平衡因子
}

//思想：递归的计算每个节点的左子树与右子树的深度，然后左子树深度-右子树深度即为平衡因子
int main(void)
{
	TreeNode* pRoot;
	cout << "创建树: ";
	pRoot = create();
	bf(pRoot);
	traversal(pRoot);
	while (1);
	return 0;
}