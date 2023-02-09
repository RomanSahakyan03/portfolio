#include <iostream>
#include <string>

template <class T> class Vector {
private:
    std::size_t cap;
    std::size_t array_size;
    T* arr;
    
public:

  //class Iterator{};
  // Создает вектор размера arr_size заполненный дефолтными значениями типа T
  Vector(std::size_t arr_size = 0): 
  arr{new T[2*arr_size+1]{}},
  cap{2*arr_size+1},
  array_size{arr_size}
{}
    // arr = new T[arr_size]{};
    // cap = arr_size;
    // array_size = 0;
  

  //Vector(const T* array): arr{new T[1000]{}} {}
  Vector(Vector&& other): 
  arr{other.arr},cap{other.cap},           
  array_size{other.array_size}{
    
  other.arr = nullptr;  
  other.array_size = other.cap = 0;
  }
  // Создает новый вектор, являющийся глубокой копией вектора other
  Vector(const Vector &other): cap{other.cap},
  array_size{other.array_size},arr{new T[other.cap]{}} {
    for(std::size_t i = 0; i < other.array_size; i++){
      arr[i] = other[i];
    }
  }

  // Перезаписывает текущий вектор вектором other
  // Vector v1{5}, v2{10};
  // v1 = v2;
  // std::cout << v1.size() == 10 << std::endl // True
  Vector &operator=(Vector &&other){
    // resize(other.cap);
    // for (int i = 0; i < other.array_size; i++) {
    //     arr[i] = other[i];
    // }
    // array_size = other.array_size;

    delete [] arr;
    arr = other.arr;
    array_size = other.array_size;
    cap = other.cap;
    other.arr = nullptr;
    other.arr = other.array_size = 0;
    other.cap = 0;
  
    
    return *this;
  }

Vector &operator=(const Vector &other){
    resize(other.cap);
    for (int i = 0; i < cap; i++) {
        arr[i] = other[i];
    }
    array_size = other.array_size;
    return *this;
  }


  // Очищает память вектора
  ~Vector(){
    delete [] arr;
  }

  // Возвращает размер вектора (сколько памяти уже занято)
  std::size_t size() const{
      return array_size;
  }

  const T* data() const{
    return arr;
  }
  // Проверяет является ли контейнер пустым
  bool empty() const{
      return !(bool)size();
  }

  // Возвращает размер выделенной памяти
  std::size_t capacity() const{
    return cap;   
  }

  // Возвращает копию элемента по индексу
  T operator[](std::size_t index) const{

    if(index >= array_size){
          std::string num = std::to_string(index);
          throw std::out_of_range("operator[] error in index:" + num);
      }
       return arr[index];


  }

  // Возвращает ссылку на элемент по индексу (позволяет менять элемент, типа
  // v[5] = 42;)
  T &operator[](std::size_t index){
      if(index >= array_size){
          std::string num = std::to_string(index);
          throw std::out_of_range (std::string("operator[] error in index:") + num);
      }
       return arr[index];
  }

  // Перевыделяет память:
  // * выделяет новый кусок памяти размером равным new_capacity,
  // * копирует столько старых элементов, сколько влезает,
  // * удаляет старый кусок памяти.
  void resize(std::size_t new_capacity){
    T* arr_resized = new T[new_capacity]{};
    
    if(array_size >= new_capacity){
      array_size = new_capacity;
    }
      for (std::size_t i = 0; i < array_size; i++) {
        arr_resized[i] = arr[i];
    }

     cap = new_capacity;
    delete [] arr;  
    arr = arr_resized;
      
  }
    
    // if(arra >= new_capacity){
    //     for (std::size_t i = 0; i < array_size; i++) {
    //         arr_resized[i] = arr[i];
    //     }
    // }else{
    // array_size = new_capacity;
    // for (std::size_t i = 0; i < array_size; i++) {
    //         arr_resized[i] = arr[i];
    //     }
    // }    


  // Добавляет элемент в конец вектора. Если нужно перевыделяет память
  void push_back(const T &x){
    if(array_size == cap){
    
        resize(2*cap);
    } 
    arr[array_size++] = x;
    
  }

  // Удаляет последний элемент вектора.
  T pop_back(){
    if(array_size == 0){
        throw std::out_of_range("pop_back error");    
    }
    return arr[--array_size];
  }

  // Очищает вектор (выделенная память остает выделенной)
  void clear(){
    // T* arr_clear = new T[cap]{};
    // delete[] arr;
    // arr = arr_clear;
    for (std::size_t i = 0; i < array_size; i++) {
        pop_back();
    }
    
  }

  // Вставляет новый элемент value на место pos.
  // [1, 2, 3].insert(1, 42) -> [1, 42, 2, 3]
  void insert(size_t pos, T value){
    push_back(value);
    for (std::size_t i = array_size - 1; i > pos ; i--) {
        std::swap(arr[i], arr[i-1]);
    }
  }

  // Удаляет элемент с идексом pos. Возвращает удаленный элемент.
  // [1, 2, 3].erase(1) -> [1, 3] (return 2)
  T erase(size_t pos){
    
    for (std::size_t i = pos; i < array_size - 1; i++) {
        std::swap(arr[i], arr[i+1]);
    }
    
    return pop_back();
  }
};
template <class T> 
std::ostream& operator << (std::ostream& out, const  Vector<T> & vec)
{  
   for (std::size_t i = 0; i < vec.size(); i++) {
        out << vec[i] << " ";
    } 
    return out; 
}

int main() { 
   Vector <int> s1(7), s2(8);
    
    s1.push_back(2);
    s1.push_back(3);
    s1.push_back(4);
    s1.resize(19);
    s1.erase(1);

    
     Vector <int> s3(s1);

    // create vector from 5 elements and move it to new vector s4
    Vector <int> s4(Vector<int>{5});
    
    std:: cout << s4;
    
}
