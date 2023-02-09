#include <iostream>

template <class T> struct Node {
  T value;
  Node<T>* next;
};


template <class T> class ForwardList {
	Node<T>* root = nullptr;

public:
  class Iterator {
  public:
    Node<T>* current;
    Iterator& operator++() {
      if (current == nullptr) {
        throw std::runtime_error{""};
      }
      current = current->next;
      return *this;
    }
    int operator*() {
      return current->value;
    }
    bool operator!=(const Iterator& other) {
      return current != other.current;
    }
  };

	ForwardList();

	~ForwardList() {
    while(root != nullptr){
      pop_front();
    };
  }

const int operator[](std::size_t index) const{
  Node<T>* current = root;
  for(int i=0;i<index;i++)
  {
    if(current == nullptr)
    {
      throw std::runtime_error{"You are out of list!"};
    }
    current = current->next;
  }

  if(current == nullptr)
  {
    throw std::runtime_error{"You are out of list!"};
  }
  return current->value;
}


	void push_front(int value) {
		root = new Node<T>{value, root};
	}

	int pop_front() {
    if (root == nullptr) {
      throw std::runtime_error{"e"};
    }
		Node<T>* tmp = root;
		int result = root->value;
		root = root->next;
    std::cout << tmp;
		delete tmp;
		return result;
	}
  Iterator begin() {
    return Iterator{root};
  }
  Iterator end() {
    return Iterator{nullptr};
  }
};





int main() {
	ForwardList<int> l{};
  l.push_front(10);
  l.push_front(0);
  l.push_front(15);
  for(ForwardList<int>::Iterator it = l.begin(); it != l.end(); ++it) {
    std::cout << *it << std::endl;
    
  }
}