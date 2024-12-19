#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

struct node {
	int data;
	node* left;
	node* right;
};

struct node1 {
	int data;
	vector<node1*> children;
};

bool leaf(node* root) {
	return (root) && (root->left == nullptr) && (root->right == nullptr);
}

bool leaf1(node1* root) {
	bool leaf = true;
	for (node1* i : root->children) {
		if (i != nullptr) leaf = false;
	}
	return leaf;
}

int height(node* root) {
	if (leaf(root)) return 1;
	return 1 + std::max(height(root->left), height(root->right));
}

int height1(node1* root) {
	if (!root) return 0;
	int height = 0;
	for (node1* i : root->children) {
		int temp = height1(i);
		if (temp >= height) {
			height = temp;
		}
	}
	return 1 + height;
}

void print(node* root) {
	std::cout << root->data;
}

void print1(node1* root) {
	std::cout << root->data;
}

void in_order(node * root) {
	if (!root) return;
	in_order(root->left);
	print(root);
	in_order(root->right);
}

void pre_order(node* root) {
	if (!root) return;
	print(root);
	in_order(root->left);
	in_order(root->right);
}

void post_order(node* root) {
	if (!root) return;
	in_order(root->left);
	in_order(root->right);
	print(root);
}

void trim(node* root) {
	if (root) {
		if (leaf(root->left)) {
			//if the thing has dynamic memory it would be harder
			//delete root->leaf;
			root->left = nullptr;
		}
		if (leaf(root->right)) {
			//if the thing has dynamic memory it would be harder
			//delete root->right;
			root->right = nullptr;
		}
		trim(root->left);
		trim(root->right);
	}
}

void bloom(node* root) {
	if (leaf(root)) {
		int data = root->data;
		node* left = new node{ data, nullptr, nullptr };
		node* right = new node{ data, nullptr, nullptr };
		root->left = left;
		root->right = right;
	}
	else {
		if(root->left) bloom(root->left);
		if(root->right) bloom(root->right);
	}
}

int branch_factor(node1* root) {
	if (!root) return -1;
	int max = root->children.size();
	for (node1* i : root->children) {
		int temp = branch_factor(i);
		if (temp >= max) {
			max = temp;
		}
	}

}

void branch_level(node1* root, int level) {
	if (!root) return;
	if (level == 0) {
		print1(root);
		return;
	}
	for (node1* i : root->children) {
		branch_level(i, level - 1);
	}

}

int branch_leaf(node1* root) {
	if (!root) return 0;
	if (leaf1(root)) return 1;
	int sum=0;
	for (node1* i : root->children) {
		sum+=branch_leaf(i);
	}
	return sum;
}

void de_bloom(node* root) {
	//specifically in this scenerio
	if (root) {
		if (leaf(root->left)) {
			//if the thing has dynamic memory it would be harder
			delete root->left;
			root->left = nullptr;
		}
		if (leaf(root->right)) {
			//if the thing has dynamic memory it would be harder
			delete root->right;
			root->right = nullptr;
		}
		de_bloom(root->left);
		de_bloom(root->right);
	}
}

int main() {
	node left2 = { 5, nullptr, nullptr };
	node left1 = { 3, &left2, nullptr };
	node right2 = { 9, nullptr, nullptr };
	node right3 = { 8, nullptr, nullptr };
	node right1 = { 0, &right2, &right3 };
	node root = { 1, &left1, &right1 };

	in_order(&root);
	std::cout << std::endl;
	//pre_order(&root);
	//std::cout << std::endl;
	//post_order(&root);
	//std::cout << std::endl;

	bloom(&root);
	in_order(&root);
	de_bloom(&root);

	return 0;
}