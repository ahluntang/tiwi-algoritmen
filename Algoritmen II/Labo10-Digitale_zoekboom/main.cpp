#include <vector>
#include <iostream>
#include <string>
#include <fstream>
template<typename T>
class Tree;
 
template<typename T>
class Node {
	friend class Tree<T>;
	public:
		Node(T value):key(value){};
	private:
		Tree<T> left;
		Tree<T> right;
		T key;
};
 
template<typename T>
class Tree {
	public:
		Tree():k(0){};
		void add(T value);
		Tree<T> * search(T value);
		void inorder();
		Node<T> * k;
};
 
template<typename T>
void Tree<T>::add(T value){
	Tree<T> * current = search(value);
	current->k = new Node<T>(value);
}
 
template<typename T>
Tree<T> * Tree<T>::search(T value){
	Tree<T> * current = this;
	int depth = 0;
	while(current->k != 0){
		if(value[depth] <= current->k->key[depth])
			current = &current->k->left;
		else 
			current = &current->k->right;
		depth++;
	}
	return current;
}
 
template<typename T>
void Tree<T>::inorder(){
	if(k!=0){
		k->left.inorder();
		std::cout << k->key << ", ";
		k->right.inorder();
	}
}
 
int main(){
	Tree<std::string> start;
	start.add("0000");
	start.add("0001");
	start.add("0101");
	start.add("1000");
	start.add("10001");
	start.inorder();
	return 0;
}