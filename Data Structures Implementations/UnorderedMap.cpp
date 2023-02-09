#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <functional>
#include <iostream>

template <class Key>
class MyHasher{
public:
  std::size_t operator()(const Key& Value) const{
    std::cout << "h-ing ";
    return 0;
  }
};

template <class Key, class Value, class Hash = std::hash<Key>> class UnorderedMap {

  friend class Iterator;
  using ValueType = std::pair<Key, Value>;
  std::vector< std::list<ValueType> > data; 
  std::size_t size_of_umap{};

  Hash hasher{};

void realloc_for_umap(){
  int old_size = data.size();
  data.resize(old_size*2);

  for(auto it = begin(); it != end(); ++it){
    int h = hasher(it->first);
    if(h%data.size() >= old_size){
      data[h].push_back(*it);
      erase(it->first);
    }
  }
}






public:
  class Iterator;
  class ConstIterator;
  // Создает пустой словарь
  UnorderedMap(): data(10) {}

  // Создает новый UnorderedMap, являющийся глубокой копией other [O(n)]
  // UnorderedMap<std::string, int>  map;
  // map["something"] = 69;
  // map["anything"] = 199;
  // UnorderedMap<std::string, int> copied{map};
  // copied["something"] == map["something"] == 69
  UnorderedMap(const UnorderedMap &other) = default;

  // Конструктор перемещения
  UnorderedMap(UnorderedMap &&other){
    std::swap(size_of_umap, other.size_of_umap);
    std::swap(data, other.data);
  }

  // Перезаписывает текущий словарь словарем other
  UnorderedMap &operator=(const UnorderedMap &other) = default;

  // Присваивание перемещением
  UnorderedMap &operator=(UnorderedMap &&other){
    data.clear();
    size_of_umap = 0;
    std::swap(size_of_umap, other.size_of_umap);
    std::swap(data, other.data);
    return *this;
  }

  ~UnorderedMap() = default;

  // Возвращает итератор на первый элемент
  Iterator begin(){
    std::size_t i{}; //=0;
    while(data[i].empty() && i < data.size() - 1){
      ++i;
    }
    
    return Iterator{i, data[i].begin(), data};
  }

  // Возвращает константный итератор на первый элемент
  ConstIterator begin() const{
    std::size_t i{}; //=0;
    while(data[i].empty() && i < data.size() - 1){
      ++i;
    }
    return ConstIterator{i, data[i].begin(), data};
  };

  // Возвращает итератор обозначающий конец контейнера (за последним элементом)
  Iterator end(){
    return Iterator(data.size() - 1, data[data.size() - 1].end(), data);
  }

  // Возвращает константный итератор, обозначающий конец контейнера
  ConstIterator end() const{
    return ConstIterator(const_cast<UnorderedMap*>(this)->end());
  }

  // Возвращает размер UnorderedMap (сколько элементов добавлено)
  std::size_t size() const{
    return size_of_umap;
  }

  // Проверяет является ли UnorderedMap пустым
  bool empty() const{
    return !(bool)size_of_umap;
  }

  // Возвращает элемент по ключу. Если отсутсвует, выбрасывает исключение
  const Value &operator[](Key key) const{
    int h = hasher(key) % data.size();  
    auto iter = find(key);
    if(iter != end()){
      return (*iter).second;
    }
      throw std::out_of_range ("Error");
  }

  // Возвращает ссылку на элемент по Key (позволяет менять элемент). Если
  // элемент с таким ключом отсутствует, создает его и инициализирует дефолтным
  // значением map["something"] = 75;
  Value &operator[](Key key){
    int h = hasher(key) % data.size();  
    auto iter = find(key);
    if(iter != end()){
      return iter->second;
    }
    data[h].push_back({key, Value{}});
    ++size_of_umap;

    if(size_of_umap >= 3*data.size()){
      realloc_for_umap();
      return find(key)->second;
    }
    return data[h].back().second;
  }


  // Проверяет есть ли в контейнере элемент с таким Key
  bool contains(const Key &key) const{
    return find(key) != end();
  }

  // Возвращяет Итератор на элемент который ищем, если нет такого элемента
  // возвращает итератор на последный элемент
  Iterator find(const Key &key){
    int h = hasher(key) % data.size();  
    for(auto it = data[h].begin(); it != data[h].end(); ++it){
      if(it->first == key){
          return Iterator(h,it,data);
        }
    }
      return end();
  }

  ConstIterator find(const Key &key) const{
    return ConstIterator{const_cast<UnorderedMap*>(this)->find(key)};
  }

  // Добавляет новый элемент с ключем и значением, если нет уже существуюшего
  // элемента с таким же ключом Map<int, std::string> c =
  //   {
  //       {1, "one" }, {2, "two" }, {3, "three"},
  //       {4, "four"}, {5, "five"}, {6, "six"  }
  //   };
  // c.(5,"something");
  // возвращает false, потому что элмемент с key = 5 уже существует․
  bool insert(const Key &k, const Value &v){
    auto it = find(k);
    if(it != end())
      return false;
    
    int h = hasher(k) % data.size();
    data[h].push_back({k,v});
    ++size_of_umap;
    
    if(size_of_umap >= 3*data.size()){
      realloc_for_umap();
    }
    return true;
  }

  // Удаляет элемент по ключу и возвращает результат операции
  // UnorderedMap<int, std::string> c =
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
  bool erase(const Key &key){
    int h = hasher(key) % data.size();
    for(auto it = data[h].begin(); it != data[h].end(); ++it){
      if(it->first == key){
        data[h].erase(it);
        --size_of_umap;
        return  true;
      }
    }
    return false;
  }

  class Iterator{

    std::size_t index;
    typename std::list<ValueType>::iterator l_it;
    typename std::vector<std::list<ValueType> > &data;

  void set(const std::size_t ind,const typename std::list<ValueType>::iterator l_iter,const typename std::vector<std::list<ValueType> > &dataa){
    index = ind;
    l_it = l_iter;
    data = dataa;
  }

  public:
    // Заполнить
    using iterator_category = std::forward_iterator_tag;
    using value_type = ValueType;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    friend class UnorderedMap;

    Iterator(std::size_t index, typename std::list<ValueType>::iterator l_it, typename std::vector<std::list<ValueType> > &data) : 
    index{index}, l_it{l_it}, data{data}
    {}

    Iterator &operator++(){
      ++l_it;
      while(l_it == data[index].end()){
        if(index == data.size() - 1){
          return *this;
        }
        
        l_it = data[++index].begin();
      }
      
      return *this;
      
    }

    bool operator!=(const Iterator &other) { return (index != other.index && l_it != other.l_it); }
    bool operator==(const Iterator &other) { return (index == other.index && l_it == other.l_it); }

    // Разыменовывает указатель: std::cout << it->second;
    std::pair<Key, Value> *operator->(){
      return &(*l_it);
    }

    // Возвращает значение итератора: *it = {"travel", 42};
    std::pair<Key, Value> &operator*(){
      return *l_it; 
    }
  };
  class ConstIterator {
    Iterator it;

  public:
    using iterator_category = typename Iterator::iterator_category;
    using value_type = typename Iterator::value_type;
    using difference_type = typename Iterator::difference_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;

    ConstIterator(Iterator it): it{it}{}
    ConstIterator(const std::size_t index, const typename std::list<ValueType>::iterator l_it, const typename std::vector<std::list<ValueType> > &data) {
      it.set(index, l_it, data);
    }

    ConstIterator &operator++(){
      ++it;
      return *this;
    }
    // ConstIterator &operator--();

    bool operator!=(const ConstIterator &other){ return it != other.it; }
    bool operator==(const ConstIterator &other){ return it == other.it; }

    // единственное отличие от Iterator, что возвращает константную ссылку
    const std::pair<Key, Value> &operator*(){ return (const std::pair<Key, Value> &) *it; }
  };




  void chacker_for_additional_task(){
    std::cout << std::endl << "at index 0:" << std::endl;
    for(const auto &it : data[0]){
      std::cout << it.first << " ";  
    }
    std::cout << std::endl;
    std::cout << "at index 1:" << std::endl;
    for(const auto &it : data[1]){
      std::cout << it.first;  
    }
    std::cout << std::endl;

    std::cout << "size of unordered map" << std::endl;
    std::cout << size_of_umap << std::endl;

  }
};

void test_operator_brackets_simple() {
  UnorderedMap<std::string, std::string> map;
  map["Nikolay"] = "teacher";
  assert(map["Nikolay"] == "teacher");
}

void test_operator_brackets_empty_string() {
  UnorderedMap<std::string, std::string> map;
  map[""] = "";
  assert(map[""] == "");
}

void test_operator_brackets_key_not_exist() {
  UnorderedMap<std::string, std::string> map;
  assert(map["Nikolay"] == "");
}

void test_operator_brackets_key_not_exist_const() {
  const UnorderedMap<std::string, std::string> map;
  bool exception_thrown{};

  // проверка, что исключение будет выброшено
  try {
    assert(map["Nikolay"] == "");
  } catch (std::out_of_range) {
    exception_thrown = true;
  }
  assert(exception_thrown);
}

void test_contains_simple() {
  UnorderedMap<std::string, std::string> map;
  map["Nikolay"] = "teacher";
  assert(map.contains("Nikolay"));
}

void test_contains_false() {
  UnorderedMap<std::string, std::string> map;
  assert(!map.contains("Nikolay"));
}

void test_find() {
  UnorderedMap<std::string, std::string> map;
  map["Nikolay"] = "teacher";
  map["John"] = "programmer";

  assert(map.find("Nikolay") != map.end());
}

void test_find_not_found() {
  UnorderedMap<std::string, std::string> map;
  map["Nikolay"] = "teacher";
  map["John"] = "programmer";

  assert(map.find("Alex") == map.end());
}

void test_insert_false() {
  UnorderedMap<int, std::string> c;
  c[1] = "one";
  c[2] = "two";
  c[3] = "tree";
  c[4] = "four";
  c[5] = "five";
  assert(c.insert(5, "something") == false);
}

void test_insert_accessed() {
  UnorderedMap<int, std::string> c;
  c[1] = "one";
  c[2] = "two";
  c[3] = "tree";
  c[4] = "four";
  c[5] = "five";
  bool res = c.insert(7, "something");
  assert(res == true);
}

void test_erase_simple() {
  UnorderedMap<std::string, int> map;
  map["first"] = 1;
  map["second"] = 2;

  assert(map.erase("last") == false);
  assert(map.contains("first") == true);
}

void test_erase_returned_value() {
  UnorderedMap<std::string, int> map;
  map["first"] = 1;
  map["second"] = 2;

  assert(map.erase("first") == true);
  assert(map.contains("first") == false);
  assert(map.size() == 1);
}

void test_empty_simple() {
  UnorderedMap<int, std::string> dict;
  dict[1] = "one";
  assert(dict.empty() == false);
}

void test_empty() {
  UnorderedMap<int, std::string> dict;
  assert(dict.empty() == true);
}

void test_size() {
  UnorderedMap<int, std::string> dict;
  dict[1] = "one";
  dict[2] = "two";
  dict[3] = "tree";
  assert(dict.size() == 3);
}

void test_size_empty_container() {
  UnorderedMap<int, std::string> dict;
  dict[1] = "one";
  dict[2] = "two";
  dict[3] = "tree";
  for (int i = 1; i < 4; ++i) {
    dict.erase(i);
  }
  assert(dict.size() == 0);
}

void test_operator_equal_r_value() {
  UnorderedMap<std::string, int> map;
  map["first"] = 1;
  map["second"] = 2;
  UnorderedMap<std::string, int> moved_map;
  moved_map = std::move(map);

  assert(map.empty());
  assert(moved_map["first"] == 1);
}

void test_move_constructor() {
  UnorderedMap<std::string, std::string> map;
  map["first"] = "some text";
  map["second"] = "some other text";

  UnorderedMap<std::string, std::string> moved_map{std::move(map)};

  assert(map.empty());
  assert(moved_map.size() == 2);
  assert(moved_map["first"] == "some text");
}

void test_copy_constructor() {
  UnorderedMap<std::string, int> map;
  map["something"] = 69;
  map["anything"] = 199;
  UnorderedMap<std::string, int> copied{map};

  assert(copied["something"] == map["something"]);
  assert(copied["anything"] == map["anything"]);
  assert(map.size() == copied.size());
}


int main() {
  test_operator_brackets_simple();
  test_operator_brackets_empty_string();
  test_operator_brackets_key_not_exist();
  test_operator_brackets_key_not_exist_const();

  test_contains_simple();
  test_contains_false();

  test_find();
  test_find_not_found();

  test_insert_false();
  test_insert_accessed();

  test_erase_simple();
  test_erase_returned_value();

  test_empty_simple();
  test_empty();

  test_size();
  test_size_empty_container();

  test_operator_equal_r_value();
  test_move_constructor();
  test_copy_constructor();

  UnorderedMap<std::string, int, MyHasher<std::string>> my_um;
  my_um["1"] = 1;
  my_um["2"] = 2;
  my_um["3"] = 3;
  my_um["4"] = 4;
  
  my_um.chacker_for_additional_task();
  
}