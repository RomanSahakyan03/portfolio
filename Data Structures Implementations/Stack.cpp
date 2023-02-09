#include <iostream>
#include <vector>

template <class T>
class Stack {
  std::vector<T> stack_vec;
public:
  class Iterator;
  // Создает пустой стэк
  Stack() = default;

  // Создает новый стэк, являющийся глубокой копией списка other [O(n)]
  Stack(const Stack& other) = default;

  template <class Iter>
  Stack(Iter a, Iter b){
    for(auto x = a; x != b; ++x){
      push_back(*x);
    }
  }

  // Перезаписывает текущий стэк стэком other
  Stack& operator=(const Stack& other){
    Stack<T> tmp{other};
    stack_vec.swap(tmp.stack_vec);
    return *this;
  }

  // Очищает память стэка
  ~Stack() = default;

  // Возвращает размер стэка (сколько памяти уже занято)
  std::size_t size(){
    return stack_vec.size();
  }

  // Проверяет является ли контейнер пустым
  bool empty(){
    return stack_vec.empty();
  }

  // Добавляет элемент в конец стэка.
  void push_back(const T& x) {
    stack_vec.push_back(x);
  }

  // Получает элемент на верху стэка
  T& top(){
    return stack_vec.back();
  }

  // Удаляет последний элемент стэка. Возвращает удаленный элемент.
  T pop(){
    T tmp = top();
    stack_vec.pop_back();
    return tmp;
  }

  // Меняет содержимое с другим стэком. s1.swap(s2);
  void swap(Stack& other){
    stack_vec.swap(other.stack_vec);
  }

  class Iterator{
    typename std::vector<T>::iterator ptr;
    public:

    Iterator(typename std::vector<T>::iterator cur_place): ptr{cur_place}{}

    Iterator& operator++() {
      ++ptr;
      return *this;
    }

    T operator*() {
      return *ptr;
    }

    Iterator& operator--(){
      --ptr;
      return *this;
    }

    bool operator!=(const Iterator& other){
      return ptr!=other.ptr;
    }

    bool operator==(const Iterator& other){
      return ptr == other.ptr;
    }
      
  };

  Iterator begin(){
    
    return Iterator(stack_vec.begin());
  }
  Iterator end(){
    Iterator it{stack_vec.end()};
    return it;
  }

  Iterator begin() const{
    
    return Iterator(stack_vec.begin());
  }
  Iterator end() const{
    Iterator it{stack_vec.end()};
    return it;
  }


};