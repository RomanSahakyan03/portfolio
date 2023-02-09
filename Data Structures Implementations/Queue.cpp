#include <iostream>
#include <list>

template <class T>
class Queue {
std::list<T> a;

public:
  // Создает пустую очередь
  Queue() = default;

  // Создает новую очередь, являющююся глубокой копией очереди other [O(n)]
  Queue(const Queue& other) = default;

  // Перезаписывает текущую очередь очередью other
  Queue& operator=(const Queue& other) = default;

  // Создает новую очередь перемещая существующую
  Queue(Queue&& other) = default;

  // Перезаписывает текущую очередь очередью other
  Queue& operator=(Queue&& other){
    a = std::move(other.a);
  }


  // Очищает память очереди
  ~Queue() = default;

  // Возвращает размер очереди (сколько памяти уже занято)
  std::size_t size() const{
   return a.size(); 
  }

  // Проверяет является ли контейнер пустым
  bool empty() const{
    return a.empty();
  }

  // Получает ссылку на первый элемент очереди
  T& front(){
    return a.front();
  }

  // Получает ссылку на последний элемент очереди
  T& back(){
    return a.back();
  }

  T front() const{
    return a.front();
  }

  T back() const{
    return a.back();
  }

  // Добавляет элемент в конец очереди.
  void push(T&& x){
    a.push_back(std::move(x));
  }

  void push(const T& x){
    a.push_back(x);
  }

  // Удаляет элемент из начала очереди. Возвращает удаленный элемент.
  T pop(){
    T tmp = front();
    a.pop_front();
    return tmp;
  }

  // Меняет содержимое с другой очередью. q1.swap(q2);
  void swap(Queue& other){
    a.swap(other.a);
  }
};


struct Point {
  int x, y;
  Point(int x, int y) : x{x}, y{y} {}
  Point(const Point &other) : x{other.x}, y{other.y} {
    std::cout << "Copy" << std::endl;
  }
  Point(Point &&other) : x{std::move(other.x)}, y{std::move(other.y)} {
    std::cout << "Move" << std::endl;
  }
};


int main() {
  Queue<Point> q0;
  Point p{0, 42};

  q0.push(p); // l-value push with copy
  q0.push(Point{2, 2}); // r-value push with move
  q0.push(std::move(p)); // r-value push with move

  Queue<int> a;
  a.push(1);
  a.push(2);
  a.push(5);
  std::cout <<  a.back();
  
  return 0;
}
