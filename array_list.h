// Copyright [2019] <Bryan Martins Lima>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions


namespace structures {

template<typename T>
//! Classe ArrayList
class ArrayList {
 public:
    //! Metodo construtor
    ArrayList();
    //! Metodo construtor com parametro
    explicit ArrayList(std::size_t max_size);
    //! Metodo destrutor
    ~ArrayList();
    //! limpa lista
    void clear();
    //! adiciona no fim
    void push_back(const T& data);
    //! adiciona no começo
    void push_front(const T& data);
    //! adiciona na posicao index
    void insert(const T& data, std::size_t index);
    //! metodo de adicionar em ordem
    void insert_sorted(const T& data);
    //! remove na posicao index
    T pop(std::size_t index);
    //! remove do fim
    T pop_back();
    //! remove do comeco
    T pop_front();
    //! remove dado especifico
    void remove(const T& data);
    //! verifica se a lista esta cheia
    bool full();
    //! verifica se a lista esta vazia
    bool empty();
    //! verifica se tal dado existe
    bool contains(const T& data) const;
    //! acha dado
    std::size_t find(const T& data) const;
    //! numero de posicoes ocupadas
    std::size_t size() const;
    //! tamanho do array
    std::size_t max_size() const;
    //! retorna dado em tal index
    T& at(std::size_t index);
    //! retorna dado em tal index
    T& operator[](std::size_t index);
    //! reotorna dado em tal index sem mudar seu valor
    const T& at(std::size_t index) const;
    //! retorna dado em tal index sem mudar seu valor
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int last;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

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
