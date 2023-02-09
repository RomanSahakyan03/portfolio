 #include <iostream>

template <class T> class List {

  struct Node {
    Node *prev;
    T value;
    Node *next;
  };

  std::size_t l_size{};
  Node *head = nullptr;
  Node *tail = nullptr;

public:
  class Iterator;
  // Создает список размера count заполненный дефолтными значениями типа T
  List(std::size_t count = 0) {
    while (count) {
      push_back(T{});
      --count;
    }
  }

  // Создает новый список, являющийся глубокой копией списка other [O(n)]
  List(const List &other) {
    for (const auto &x : other) {
      push_back(x);
    }
  }

  List(List &&other) {
    std::swap(l_size, other.l_size);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
  }

  // Перезаписывает текущий список списком other
  // List l1{5}, l2{10};
  // l1 = l2;
  // std::cout << l1.size() == 10 << std::endl // True
  List &operator=(const List &other) {
    List tmp{other};

    std::swap(l_size, tmp.l_size);
    std::swap(head, tmp.head);
    std::swap(tail, tmp.tail);

    return *this;
  }

  List &operator=(List &&other) {
    List tmp{std::move(other)};

    std::swap(l_size, tmp.l_size);
    std::swap(head, tmp.head);
    std::swap(tail, tmp.tail);

    return *this;
  }

  // Очищает память списка [O(n)]
  ~List() {
    while (l_size) {
      pop_front();
    }
  }

  // Возвращает размер списка (сколько памяти уже занято)
  std::size_t size() { return l_size; }

  // Проверяет является ли контейнер пустым
  bool empty() { return l_size; }

  // Возвращает итератор на первый элемент
  // https://en.cppreference.com/w/cpp/container/list/begin

  Iterator begin() const { return Iterator{head}; }

  // Возвращает итератор обозначающий конец контейнера
  Iterator end() const { return Iterator{nullptr}; }

  Iterator begin() { return Iterator{head}; }

  // Возвращает итератор обозначающий конец контейнера
  Iterator end() { return Iterator{nullptr}; }

  // Возвращает копию элемента по индексу
  T operator[](std::size_t index) const {
    // for (auto& x: container) {
    //   std::cout << x;
    // }
    // // ->
    // for (auto it = container.begin(); it != container.end(); ++it) {
    //   auto& x = *it;
    //   std::cout << x;
    // }

    for (auto &x : *this) {
      if (index == 0) {
        return x;
      }
      --index;
    }
  }

  // Возвращает ссылку на элемент по индексу (позволяет менять элемент, типа
  // v[5] = 42;)
  T &operator[](std::size_t index) {
    for (auto &x : *this) {
      if (index == 0) {
        return x;
      }
      --index;
    }
  }

  // Добавляет элемент в конец списока.
  void push_back(const T &x) {

    if (l_size == 0) {
      Node *tmp = new Node{nullptr, x, nullptr};
      head = tmp;
      tail = tmp;
    } else {
      Node *tmp = new Node{tail, x, nullptr};
      tail->next = tmp;
      tail = tmp;
    }
    // std::cout << head->value << ' ';
    ++l_size;
  }

  // Добавляет элемент в начало списока.
  void push_front(const T &x) {

    if (l_size == 0) {
      Node *tmp = new Node{nullptr, x, nullptr};
      head = tmp;
      tail = tmp;
    } else {
      Node *tmp = new Node{nullptr, x, head};
      head->prev = tmp;
      head = tmp;
    }
    // std::cout << head->value << ' ';
    ++l_size;
  }

  // Удаляет последний элемент списока.
  T pop_back() {
    if (l_size == 0)
      throw std::runtime_error("you can't pop");

    T poped_value = tail->value;
    Node *point = tail;

    if (l_size == 1) {
      head = nullptr;
      tail = nullptr;
    } else {
      tail = tail->prev;
      tail->next = nullptr;
    }
    delete point;
    --l_size;
    return poped_value;
  }

  // Удаляет первый элемент списока.
  T pop_front() {
    if (l_size == 0)
      throw std::runtime_error("you can't pop");

    T poped_value = head->value;
    Node *point = head;

    if (l_size == 1) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = head->next;
      head->prev = nullptr;
    }
    delete point;
    --l_size;
    return poped_value;
  }

  // Вставляет новый элемент value перед элементом, на который указывает it.
  //     it
  //     v
  // [1, 2, 3].insert(it, 42) -> [1, 42, 2, 3]
  void insert(Iterator it, T value) {
    if (it.ptr == head) {
      push_front(value);
      return;
    } else if (it.ptr == nullptr) {
      throw std::out_of_range("cant be inserted");
    }
    Node *tmp = new Node{it.ptr->prev, value, it.ptr};
    it.ptr->prev->next = tmp;
    it.ptr->prev = tmp;
  }

  //     it
  //     v
  // [1, 2, 3].erase(1) -> [1, 3] (return 2)
  T erase(Iterator it) {

    if (it.ptr == head) {
      return pop_front();
    } else if (it.ptr == tail) {
      return pop_back();
    } else if (it.ptr == nullptr) {
      throw std::out_of_range("cant be erased");
    }

    T res = it.ptr->value;
    it.ptr->next->prev = it.ptr->prev;
    it.ptr->prev->next = it.ptr->next;

    delete it.ptr;
    --l_size;
    return res;
  }

  void splice(const List &other, int index) {
    Iterator it = begin();
    // while (index) {
    //   ++it;
    //   --index;
    // }
    std::advance(it, index);
    //std::advance(istreambuf_iterator<_CharT> &__i, _Distance __n)
    for (auto &x : other) {
      insert(it, x);
    }
  }


  void splice(List &&other, int index) {
    Iterator it = begin();
    std::advance(it, index);

    it.ptr -> prev -> next = other.head;
    other.tail -> next = it.ptr;
    it.ptr -> prev = other.tail;
    other.head -> prev = it.ptr -> prev;
    
    other.head = other.tail = nullptr;
    other.l_size = 0;
      
  }

  // Класс, который позволяет итерироваться по контейнеру.
  // Я указал минимальный набор операций
  class Iterator {
    friend List;

    Node *ptr;

  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;

    Iterator(Node *p) : ptr{p} {}

    // Инкремент. Движение к следующему элементу. ++it
    Iterator &operator++() {
      if (ptr == nullptr) {
        throw std::runtime_error{""};
      }
      ptr = ptr->next;
      return *this;
    }

    // Декремент. Движение к предыдущему элементу. --it
    Iterator &operator--() {
      if (ptr == nullptr) {
        throw std::runtime_error{""};
      }
      ptr = ptr->prev;
      return *this;
    }

    // Проверка на неравенство двух итераторов. Обычно используется it !=
    // container.end().
    bool operator!=(const Iterator &other) { return ptr != other.ptr; }

    bool operator==(const Iterator &other) { return ptr == other.ptr; }

    // разыменование (как с указателями): *it = 42; или std::cout << *it;
    T &operator*() { return ptr->value; }
  };
};

int main() {
  List<int> s1(5);
  // std::cout << "List" <<std::endl;

  for (std::size_t i = 0; i < s1.size(); ++i) {
    s1[i] = i;
  }
  
  List<int> s2;
  // // std::cout << *s2.begin();
  s2.push_back(5);
  s2.push_back(8);
  s2.push_back(10);
  s2.push_front(1);


  for (auto x : s2) {
    std::cout << x << " ";
  }
  std::cout << std::endl;


  

  
  for (auto x : s1) {
    std::cout << x << " ";
  }
  std::cout << std::endl;


  
  int insert_index = 2;
  
  s1.splice(s2, insert_index);
  
  for (auto x : s1) {
    std::cout << x << " ";
  }

  return 0;
}
