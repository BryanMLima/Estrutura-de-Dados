//! Copyright [2018] <Bryan Martins Lima>

#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>

namespace structures {

//! Classe Array basica
template<typename T>
class ArrayList {
 public:
    //! Construtor
    ArrayList();
    //! contrutuor com parametro
    explicit ArrayList(std::size_t max_size);
    //! destrutor
    ~ArrayList();

    //! limpa lista
    void clear();
    //! empilha no final
    void push_back(const T& data);
    //! empilha no comeco
    void push_front(const T& data);
    //! insere na posicao x
    void insert(const T& data, std::size_t index);
    //! insere em ordem
    void insert_sorted(const T& data);
    //! desempilha na posicao x
    T pop(std::size_t index);
    //! desempilha de tras
    T pop_back();
    //! desempilha da frente
    T pop_front();
    //! remove dado x
    void remove(const T& data);
    //! verifica se lista esta cheia
    bool full();
    //! verifica se lista esta vazia
    bool empty();
    //! verifica se contem tal dado
    bool contains(const T& data) const;
    //! procura tal dado e devolve index
    std::size_t find(const T& data) const;
    //! devolve posicoes ocupadas
    std::size_t size() const;
    //! devolve tamanho max
    std::size_t max_size() const;
    //! devolve dado em tal posicao
    T& at(std::size_t index);
    //! devolve dado em tal posicao
    T& operator[](std::size_t index);
    //! devolve dado em tal posicao
    const T& at(std::size_t index) const;
    //! devolve dado em tal posicao
    const T& operator[](std::size_t index) const;

 protected:
    //! ponteiro do tipo T
    T* contents;
    //! variavel do tamanho atual
    std::size_t size_;
    //! variavel tamanho max
    std::size_t max_size_;
    //! index do ultimo elemento
    int last;
    //! valor default do tamanho do array
    static const auto DEFAULT_MAX = 10u;
};

template <typename T>
structures::ArrayList<T>::ArrayList() {
  contents = new T[max_size_];
  size_ = 0;
  last = -1;
}

template <typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
  max_size_ = max_size;
  contents = new T[max_size_];
  size_ = 0;
  last = -1;
}

template <typename T>
structures::ArrayList<T>::~ArrayList() {
  delete [] contents;
}

template <typename T>
void structures::ArrayList<T>::clear() {
  size_ = 0;
  last = -1;
}

template <typename T>
bool structures::ArrayList<T>::full() {
  return size_ == max_size_;
}

template <typename T>
bool structures::ArrayList<T>::empty() {
  return size_ == 0;
}

template <typename T>
void structures::ArrayList<T>:: push_back(const T& data) {
  if (full()) {
    throw std::out_of_range("Lista cheia");
  } else {
    last++;
    contents[last] = data;
    size_++;
  }
}

template <typename T>
void structures::ArrayList<T>::remove(const T& data) {
  if (empty()) {
    throw std::out_of_range("Lista vazia");
  } else {
      if (contains(data)) {
          pop(find(data));
      } else {
          throw std::out_of_range("erro posicao");
      }
  }
}

template <typename T>
void structures::ArrayList<T>::push_front(const T& data) {
  int position;
  if (full()) {
    throw std::out_of_range("lista cheia");
  } else {
    last++;
    size_++;
    position = last;
    while (position > 0) {
      contents[position] = contents[position - 1];
      position--;
    }
    contents[0] = data;
  }
}

template <typename T>
T structures::ArrayList<T>::pop_front() {
  T value;
  int position;
  if (empty()) {
    throw std::out_of_range("lista vazia");
  } else {
    last--;
    size_--;
    value = contents[0];
    position = 0;
    while (position <= last) {
      contents[position] = contents[position + 1];
      position++;
    }
    return value;
  }
}

template <typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    int atual;
    T value;
    if (index < 0 || index > last) {
        throw std::out_of_range("erro posicao");
    } else {
        if (empty()) {
            throw std::out_of_range("lista vazia");
        } else {
            last--;
            size_--;
            value = contents[index];
            atual = index;
            while (atual <= last) {
                contents[atual] = contents[atual + 1];
                atual++;
            }
            return value;
        }
    }
}

template <typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
  int atual;
  if (full()) {
    throw std::out_of_range("lista cheia");
  } else {
    if (index < 0 || index > (last + 1)) {
      throw std::out_of_range("index com valor invalido");
    } else {
      last++;
      size_++;
      atual = last;
      while (atual > index) {
        contents[atual] = contents[atual - 1];
        atual--;
      }
    contents[index] = data;
    }
  }
}

template <typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    int atual;
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        atual = 0;
        while (atual <= last && data > contents[atual]) {
            atual++;
        }
        insert(data, atual);
    }
}

template <typename T>
T structures::ArrayList<T>:: pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        T popContent = contents[last];
        last--;
        size_--;
        return popContent;
    }
}

template <typename T>
bool structures::ArrayList<T>:: contains(const T& data) const {
    for (int i = 0; i <= last; i++) {
        if (contents[i] == data) {
            return 1;
        }
    }
    return 0;
}

template <typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    int atual = 0;
    while (atual <= last && contents[atual] != data) {
        atual++;
    }
    return atual;
}

template <typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template <typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template <typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index > last || index < 0) {
        throw std::out_of_range("index invalido");
    } else {
        return contents[index];
    }
}

template <typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

//-------------------------------------

//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! construtor
    ArrayListString() : ArrayList() {}
    //! construtor com parametro
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! destrutor
    ~ArrayListString();

    //! limpa lista
    void clear();
    //! empilha atras
    void push_back(const char *data);
    //! empilha na frente
    void push_front(const char *data);
    //! insere dado em index x
    void insert(const char *data, std::size_t index);
    //! insere em ordem
    void insert_sorted(const char *data);
    //! desempilha em tal index
    char *pop(std::size_t index);
    //! desempilha do final
    char *pop_back();
    //! desempilha da frente
    char *pop_front();
    //! remove dado x
    void remove(const char *data);
    //! verifica se ha dado x
    bool contains(const char *data);
    //! retorna index do dado x se houver
    std::size_t find(const char *data);
};


}  // namespace structures

structures::ArrayListString::~ArrayListString() {
    // delete [] contents;
}
void structures::ArrayListString::clear() {
    size_ = 0;
    last = -1;
}

void structures::ArrayListString::insert(const char *data, std::size_t index) {
    std::size_t stringLength = strlen(data);
    if (stringLength < 1000) {
        char* dataPointer = new char[stringLength + 1];
        snprintf(dataPointer, strlen(data) + 1, "%s", data);
        ArrayList::insert(dataPointer, index);
    } else {
        throw std::out_of_range("string maior que 10.000");
    }
}

void structures::ArrayListString::push_back(const char *data) {
    std::size_t stringLength = strlen(data);
    if (stringLength < 10000) {
        char* dataPointer = new char[stringLength + 1];
        snprintf(dataPointer, strlen(data) + 1, "%s", data);
        ArrayList::push_back(dataPointer);
    } else {
        std::out_of_range("string maior que 10.000");
    }
}

void structures::ArrayListString::push_front(const char *data) {
    std::size_t stringLength = strlen(data);
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else {
        if (stringLength < 10000) {
            char* dataPointer = new char[stringLength + 1];
            snprintf(dataPointer, strlen(data) + 1, "%s", data);
            ArrayList::push_front(dataPointer);
        } else {
            std::out_of_range("string maior que 10.000");
        }
    }
}

void structures::ArrayListString::insert_sorted(const char *data) {
    std::size_t stringLength = strlen(data);
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else {
        if (stringLength < 10000) {
            std::size_t index = 0;
            while (index < size_ && strcmp(contents[index], data) < 0) {
                index++;
            }
            char* dataPointer = new char[stringLength + 1];
            snprintf(dataPointer, strlen(data) + 1, "%s", data);
            ArrayList::insert(dataPointer, index);
        } else {
            std::out_of_range("string maior que 10.000");
        }
    }
}

char* structures::ArrayListString::pop(std::size_t index) {
    return ArrayList::pop(index);
}

char* structures::ArrayListString::pop_back() {
    return ArrayList::pop_back();
}

char* structures::ArrayListString::pop_front() {
    return ArrayList::pop_front();
}

void structures::ArrayListString::remove(const char *data) {
    if (empty()) {
        std::out_of_range("lista vazia");
    } else {
        if (contains(data)) {
            pop(find(data));
        }
    }
}

bool structures::ArrayListString::contains(const char *data) {
    if (empty()) {
        std::out_of_range("lista vazia");
    } else {
        for (int i = 0; i <= last; i++) {
            if (strcmp(this->contents[i], data) == 0) {
                return true;
            }
        }
    }
    return false;
}

std::size_t structures::ArrayListString::find(const char *data) {
    if (empty()) {
        std::out_of_range("lista vazia");
    } else {
        for (int i = 0; i <= last; i++) {
            if (strcmp(this->contents[i], data) == 0) {
                return i;
            }
        }
    }
    return size_;
}
#endif
