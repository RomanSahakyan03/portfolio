#include <cassert>
#include <cstddef>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>
#include <queue>
#include <list>

template <class Key, class Value> class Map {

  using key_type = Key;
  using mapped_type = Value;
  using ValueType = std::pair<Key, Value>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = ValueType &;
  using const_reference = const ValueType &;

  struct Node {
    ValueType data;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
  };

  Node *root = nullptr;
  size_type map_size{};

  void clear(Node *node) {
    if (node == nullptr) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node *find(const Key &key){
    Node *current = root;
    while (current) {
      if (key > current->data.first) {
        current = current->right;
      } else if (key < current->data.first) {
        current = current->left;
      } else {
        return current;
      }
    }
    return nullptr;
  }

  const Node *find(const Key &key) const{
    Node *current = root;
    while (current) {
      if (key > current->data.first) {
        current = current->right;
      } else if (key < current->data.first) {
        current = current->left;
      } else {
        return current;
      }
    }
    return nullptr;
  }

void full_copy(Node *other_nodes){

  // if(!other_nodes){
  //   return;
  // }
  //  // in-order
  // full_copy(other_nodes->left);
  // (*this)[other_nodes->data.first] = other_nodes->data.second;
  // full_copy(other_nodes->right);

  std::queue<Node *, std::list<Node *>> nodes;
  nodes.push(other_nodes);
  
  while(!nodes.empty()){
    if(nodes.front()){
      (*this)[nodes.front()->data.first] = nodes.front()->data.second;
      nodes.push(nodes.front()->left);
      nodes.push(nodes.front()->right);  
    }
      nodes.pop();
  }
}

public:
  class Iterator;
  class ConstIterator;
  // Создает пустой словарь
  Map() = default;

  // Создает новый словарь, являющийся глубокой копией other [O(n)]
  //  Map<std::string, int> map;
  //  map["something"] = 69;
  //  map["anything"] = 199;
  //  Map<std::string, int> copied{map};
  //  copied["something"] == map["something"] == 69
  Map(const Map &other) : map_size{other.map_size}{
    full_copy(other.root);
  }

  // Move конструктор
  Map(Map &&other) { std::swap(root, other.root); std::swap(map_size, other.map_size);}

  // Перезаписывает текущий словарь словарем other
  Map &operator=(const Map &other) {
    Map tmp{other};
    std::swap(tmp.root, root);
    std::swap(tmp.map_size, map_size);

    return *this;
  }

  // Присвоивание перемещением
  Map &operator=(Map &&other) {
    Map tmp{std::move(other)};
    std::swap(tmp.root, root);
    std::swap(tmp.map_size, map_size);
    return *this;
  }
  // Очищает память словаря
  ~Map() { clear(); }

  // Возвращает итератор на первый элемент
  Iterator begin() {
    Node *current = root;
    while (current && current->left) {
      current = current->left;
    }
    return Iterator(current);
  }

  // Возвращает const итератор на первый элемент
  ConstIterator begin() const {
    Node *current = root;
    while (current && current->left) {
      current = current->left;
    }
    return ConstIterator(current);
  }

  // Возвращает итератор обозначающий конец контейнера
  Iterator end() { return Iterator(nullptr); }

  // Возвращает const итератор обозначающий конец контейнера
  ConstIterator end() const { return ConstIterator(nullptr); }

  // Возвращает размер словаря (сколько есть узлов)
  size_type size() const {
    return map_size;
  };

  // Проверяет есть ли элемент с таким ключом в контейнере
  bool contains(const Key &key) const { return find(key) != nullptr;}

  // Возвращает элемент по ключу. Если в словаре нет элемента с таким ключом, то
  // бросает исключение std::out_of_range

  const Value &operator[](const Key &key) const {    
    if(auto current = find(key)){
      return current->data.second;
    }else{
      throw std::out_of_range("Error: you dont have that key");
    }
  }

  // Возвращает ссылку на элемент по ключу (позволяет менять элемент). Если в
  // словаре нет элемента с таким ключем, то создает его и устанавливает
  // дефолтное значение, после чего возвращает на него ссылку. map["something"]
  // = 75;

  Value &operator[](Key key) {
    Node *current = root;
    Node *parent = nullptr;
    while (current) {
      if (current->data.first == key) {
        return current->data.second;
      } else if (current->data.first > key) {
        parent = current;
        current = current->left;
      } else if (current->data.first < key) {
        parent = current;
        current = current->right;
      } else
        break;
    }
    if (!parent) {
      root = new Node{{key, mapped_type{}}};
      ++map_size;
      return root->data.second;
    } else {
      Node *new_node = new Node{{key, mapped_type{}}, parent};
      ++map_size;

      if (key > parent->data.first) {
        parent->right = new_node;
      } else {
        parent->left = new_node;
      }
      return new_node->data.second;
    }
  }

  // Удаляет элемент по ключу и возвращает значение удаленного элемента
  // Map<int, std::string> c =
  //   {
  //       {1, "one" }, {2, "two" }, {3, "three"},
  //       {4, "four"}, {5, "five"}, {6, "six"  }
  //   };
  // c.erase(4) == true
  // c =
  //   {
  //       {1, "one" }, {2, "two" }, {3, "three"},
  //             {5, "five"}, {6,"six"  }
  //   }; результат после erase

  // проверил уже
  bool erase(const Key &key){
    //it's 0 if his location in parents left and al==
    bool parent_l_or_r;
    Node *current = find(key);
    
    if(!current) return false;
    --map_size;


    if(current->left && current->right){
      auto tmp = current;
      current = current->left;
      while (!current->right)
        current = current->right;
      tmp->data = current->data;
      erase(current->data.first);
    }

    if(current == root){
      if(root->right){
        root = root->right;
        delete root->parent;
        root->parent = nullptr;
      }else if(root->left){
        root = root->right;
        delete root->parent;
        root->parent = nullptr;
      }else{
        delete root;
        root = nullptr;
      }
      return  true;
    }
    
    if(!current->left || !current->right){

    current->parent->left == current ? parent_l_or_r = 0 : parent_l_or_r = 1;
      
        if(!parent_l_or_r){
          if(current->left){
            current->parent->left = current->left; delete current;
          }else if(current->right){
            current->parent->left = current->right; delete current;
          }else{
            current->parent->left = nullptr;
            delete current;
          }
        }else{
          if(current->left){
            current->parent->right = current->left; delete current;
          }else if(current->right){
            current->parent->right = current->right; delete current;
          }else{
            current->parent->right = nullptr;
            delete current;
          }
        }
      }
    }

  // Меняет текуший контейнер с контейнером other
  void swap(Map &other) { std::swap(root, other.root); std::swap(map_size, other.map_size); }

  // Возвращает итератор на первый элемент который не меньше чем переданный
  // ключ. [O(h)]
  Iterator lower_bound(const Key &key) {
    Node* tmp = find(key);
    if(tmp){
      Iterator it(tmp);
      return it;
    }
    
    Node *current = root;
    while(true){
      
      if(current == nullptr){ return nullptr; }
      
      if(key < current->data.first && current->left == nullptr) break;
      
      if(key > current->data.first && current->right == nullptr) break;
    
      if(key < current->data.first && current->left) current = current->left;
    
      if(key > current->data.first && current->right) current = current->right;
    }
    
    if(current->data.first > key){
      Iterator it(current);
      return it;
    }else if(current->data.first < key && current->right){
      Iterator it(current);
      ++it;
      return it;
    }
  }
  

  // Очищает контейнер [O(n)]
  // Map<int, std::string> c =
  //   {
  //       {1, "one" }, {2, "two" }, {3, "three"},
  //       {4, "four"}, {5, "five"}, {6, "six"  }
  //   };
  // c.clear;
  // c.size() == 0 //true;
  void clear() { 
    clear(root);
    root = nullptr;
    map_size = 0;
    }

  class Iterator {
    Node *node;

  public:
    // Заполнить:
    using iterator_category = std::bidirectional_iterator_tag();
    using value_type = ValueType;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    Iterator(Node *it = nullptr) : node{it} {}

    // Инкремент. Движение к следующему элементу.
    Iterator &operator++() {
      if (node->right == nullptr) {
        while (node->parent && node->parent->data.first > node->data.first) {
          node = node->parent;
        }
        node = node->parent;
      } else {
        node = node->right;
        while (node->left) {
          node = node->left;
        }
      }

      return *this;
    }

    // Декремент. Движение к предыдущему элементу.
    Iterator &operator--() {
      if (node->left == nullptr) {
        while (node->parent && node->parent->data.first < node->data.first) {
          node = node->parent;
        }
        node = node->parent;
      } else {
        node = node->left;
        while (node->right) {
          node = node->right;
        }
      }

      return *this;
    }

    // Проверка на неравенство двух итераторов.
    bool operator!=(const Iterator &other) { return node != other.node; }

    std::pair<Key, Value> *operator->() { return &node->data; }

    // разыменование (как с указателями): *it = {1,"smth"};
    std::pair<Key, Value> &operator*() { return node->data; }
  };
  class ConstIterator {
    Iterator it;

  public:
    // Заполнить
    using iterator_category = std::bidirectional_iterator_tag();
    using value_type = ValueType;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    ConstIterator(Node *it) : it(it) {}

    ConstIterator &operator++() {
      ++it;
      return *this;
    }

    bool operator!=(const ConstIterator &other) { return it != other.it; }

    bool operator==(const ConstIterator &other) { return it == other.it; }

    // единственное отличие от Iterator, что возвращает константную ссылку
    const std::pair<Key, Value> &operator*() { return *it; }
  };
};

void test_operator_brackets_simple() {
  Map<std::string, std::string> map;
  map["Nikolay"] = "teacher";
  assert(map["Nikolay"] == "teacher");
}

void test_operator_brackets_empty_string() {
  Map<std::string, std::string> map;
  map[""] = "";
  assert(map[""] == "");
}

void test_operator_brackets_key_not_exist() {
  Map<std::string, std::string> map;
  assert(map["Nikolay"] == "");
}

void test_operator_brackets_key_not_exist_const() {
  const Map<std::string, std::string> map;

  // проверка, что исключение будет выброшено
  bool exception_thrown{};
  try {
    assert(map["Nikolay"] == "");
  } catch (std::out_of_range) {
    exception_thrown = true;
  }
  assert(exception_thrown);
}

void test_contains() {
  Map<std::string, std::string> map;
  map["Nikolay"] = "teacher";
  assert(map.contains("Nikolay"));
}

void test_contains_key_not_exist() {
  Map<std::string, std::string> map;
  assert(!map.contains("Nikolay"));
}

void test_copy_constructor() {
  Map<int, std::string> map;
  map[2] = "some string";
  map[1] = "other string";
  Map<int, std::string> map2{map};
  assert(map[1] == map2[1]);
}

void test_move_constructor() {
  Map<std::string, std::string> map;
  map["first"] = "some text";
  map["second"] = "some other text";
  Map<std::string, std::string> moved_map{std::move(map)};

  assert(map.size() == 0);
  assert(moved_map.size() == 2);
  assert(moved_map["second"] == "some other text");
}

void test_operator_equal_r_value() {
  Map<std::string, int> map;
  map["first"] = 1;
  map["second"] = 2;
  Map<std::string, int> moved_map;
  moved_map = std::move(map);

  assert(map.size() == 0);
  assert(moved_map.size() == 2);
  assert(moved_map["first"] == 1);
}

void test_size() {
  Map<int, std::string> dict;
  dict[1] = "one";
  dict[2] = "two";
  dict[2] = "another two";
  dict[3] = "tree";
  assert(dict.size() == 3);
}

void test_clear() {
  Map<int, std::string> map;
  map[1] = "first";
  map[2] = "second";
  map.clear();

  assert(map.size() == 0);
  assert(!map.contains(1));
  assert(!map.contains(2));
}

void test_swap_with_empty_container() {
  Map<int, int> map;
  map[1] = 25;
  map[2] = 45;
  map[10] = 4512;
  Map<int, int> map_for_swap;
  map_for_swap.swap(map);

  assert(map.size() == 0);
  assert(map_for_swap.size() == 3);
  assert(map_for_swap[10] == 4512);
}

void test_swap() {
  Map<int, int> map;
  map[1] = 25;
  map[2] = 45;
  map[10] = 4512;
  Map<int, int> map_for_swap;
  map_for_swap[3] = 4564;
  map_for_swap[4] = 6121;
  map_for_swap[58] = 8888;
  map_for_swap[95] = 545656;
  map_for_swap.swap(map);

  assert(map.size() == 4);
  assert(map_for_swap.size() == 3);
  assert(map_for_swap[10] == 4512);
  assert(map[95] == 545656);
}

void test_erase_simple() {
  Map<std::string, int> map;
  map["first"] = 1;
  map["second"] = 2;

  assert(!map.erase("last"));
  assert(map.contains("first"));
}

void test_erase_returned_value() {
  Map<std::string, int> map;
  map["first"] = 1;
  map["second"] = 2;

  assert(map.erase("first"));
  assert(!map.contains("first"));
  assert(map.size() == 1);
}

void test_lower_bound() {
  Map<std::string, std::string> map;
  map["b"] = "second key";
  map["a"] = "first key";
  map["f"] = "third key";

  std::pair<std::string, std::string> expected{"b", "second key"};
  assert(*map.lower_bound("b") == expected);
}

void test_lower_bound_equal() {
  Map<std::string, std::string> map;
  map["b"] = "second key";
  map["a"] = "first key";
  map["f"] = "third key";
  auto it = map.end();

  std::pair<std::string, std::string> expected{"f", "third key"};
  assert(*map.lower_bound("c") == expected);
}

int main() {

  test_operator_brackets_simple();
  test_operator_brackets_empty_string();
  test_operator_brackets_key_not_exist();
  test_operator_brackets_key_not_exist_const();

  test_contains();
  test_contains_key_not_exist();

  test_copy_constructor();
  test_move_constructor();
  test_operator_equal_r_value();

  test_size();

  test_clear();

  test_swap_with_empty_container();
  test_swap();

  test_erase_simple();
  test_erase_returned_value();

  test_lower_bound();
  test_lower_bound_equal();

}
