//! Copyright [2019] <Bryan Martins Lima>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

//! Classe de implementação de lista circular
template<typename T>
class CircularList {
 public:
    //! construtor padrão de lista circular
    CircularList();
    //! destrutor de lista circular
    ~CircularList();
    //! método para limpar a lista circular
    void clear();
    //! método para inserir dados no fim
    void push_back(const T& data);
    //! método para inserir dados no início
    void push_front(const T& data);
    //! método para inserir dado em determinada posição
    void insert(const T& data, std::size_t index);
    //! método para inserir dados em ordem
    void insert_sorted(const T& data);
    //! acessar em um indice (com checagem de limites)
    T& at(std::size_t index);
    //! versão const do acesso ao indice
    const T& at(std::size_t index) const;
    //! retirar da posição
    T pop(std::size_t index);
    //! retirar do fim
    T pop_back();
    //! retirar do início
    T pop_front();
    //! remover dado específico
    void remove(const T& data);
    //! lista vazia
    bool empty() const;
    //! lista contém determinado dado?
    bool contains(const T& data) const;
    //! posição de um item na lista
    std::size_t find(const T& data) const;
    //! tamanho da lista
    std::size_t size() const;

 private:
    class Node {
     public:
        //! construtor padrão
        explicit Node(const T& data):
            data_{data}
        {}
        //! construtor com dado e next
        Node(const T& data, Node *next):
            data_{data},
            next_{next}
        {}
        //! construtor com dado, next e sentinela
        Node(const T& data, Node *next, bool sentinela):
            data_{data},
            next_{next},
            sentinela_{sentinela}
        {}
        //! getter: dado
        T& data() {
            return data_;
        }
        //! getter const: dado
        const T& data() const {
            return data_;
        }
        //! getter: next
        Node *next() {
            return next_;
        }
        //! getter const: next
        const Node* next() const {
            return next_;
        }
        //! getter: sentinela
        bool sentinela() {
            return sentinela_;
        }
        //! getter const: sentinela
        const bool sentinela() const {
            return sentinela_;
        }
        //! setter: next
        void next(Node *node) {
            next_ = node;
        }
        //! setter: sentinela
        void sentinela(bool sentinela) {
            sentinela_ = sentinela;
        }

     private:
        T data_;
        Node* next_{nullptr};
        bool sentinela_;
    };
    //! nodo-topo
    Node* head;
    //! tamanho
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::CircularList<T>::CircularList() {
    size_ = 0;
    Node *sent = new Node(0, nullptr, true);
    sent -> next(sent);
    head = sent;
}

template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
    delete(head);
}

template<typename T>
void structures::CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    Node *new_element = new Node(data, head, false);
    if (new_element == nullptr) {
        throw std::out_of_range("Circular list full");
    } else {
        if (empty() == true) {
            head -> next(new_element);
        } else {
            Node *temp = head -> next();
            for (size_t i = 0; i < size_ - 1; i++) {
                temp = temp -> next();
            }
            temp -> next(new_element);
        }
        size_++;
    }
}

template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node *new_element = new Node(data, nullptr, false);
    if (new_element == nullptr) {
        throw std::out_of_range("Circular list full");
    } else {
        if (empty() == true) {
            new_element -> next(head);
        } else {
            new_element -> next(head -> next());
        }
        head -> next(new_element);
        size_++;
    }
}
template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("Circular List full");
    }
    if (index == 0) {
        return push_front(data);
    } else {
        if (index == size_) {
            return push_back(data);
        } else {
            if (empty()) {
                return push_front(data);
            } else {
                Node* new_element = new Node(data, nullptr, false);
                if (new_element == nullptr) {
                    throw std::out_of_range("Full List");
                }
                Node* temp = head->next();
                Node* previous = nullptr;
                for (size_t i = 0; i < index; i++) {
                    if (!temp -> sentinela()) {
                        previous = temp;
                        temp = temp -> next();
                    }
                }
                new_element->next(temp);
                previous->next(new_element);
                size_++;
            }
        }
    }
}

template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    size_t index = 0;
    Node *temp = head -> next();
    while (index < size_ && temp != nullptr && data > temp -> data()) {
        index++;
        temp = temp -> next();
    }
    insert(data, index);
}

template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Circular list empty");
    }
    if (index > size_) {
        throw std::out_of_range("Out of bound");
    }
    Node* temp = head -> next();
    for (size_t i = 0; i < index; i++) {
        temp = temp -> next();
    }
    return temp -> data();
}

template<typename T>
const T& structures::CircularList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("Circular list empty");
    }
    if (index > size_) {
        throw std::out_of_range("Out of bound");
    }
    Node* temp = head -> next();
    for (size_t i = 0; i < index; i++) {
        temp = temp -> next();
    }
    return temp -> data();
}

template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Circular List empty");
    }
    if (index >= size_) {
        throw std::out_of_range("Invalid index");
    }
    if (index == 0) {
        return pop_front();
    } else {
        if (index == size_ -1) {
            return pop_back();
        } else {
            if (size_ == 1) {
                return pop_front();
            } else {
                Node *e_retirar = head -> next();
                Node *previous = nullptr;
                T return_data;
                for (size_t i = 0; i < index; i++) {
                    previous = e_retirar;
                    e_retirar = e_retirar -> next();
                }
                return_data = e_retirar -> data();
                previous -> next(e_retirar -> next());
                size_--;
                delete(e_retirar);
                return return_data;
            }
        }
    }
}

template<typename T>
T structures::CircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Circular List empty");
    }
    Node *e_retirar = head -> next();
    T return_data;
    if (size_ > 1) {
        Node* previous = nullptr;
        for (size_t i = 0; i < size_ -1; i++) {
          if (!(e_retirar -> sentinela())) {
            previous = e_retirar;
            e_retirar = e_retirar -> next();
          }
        return_data = e_retirar -> data();
        }
    previous -> next(head);
    } else {
    return_data = e_retirar -> data();
    head -> next(head);
    }
    delete(e_retirar);
    size_--;
    return return_data;
}

template<typename T>
T structures::CircularList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("Circular List empty");
  }
  Node *e_retirar = head->next();
  T return_data = e_retirar -> data();
  if (size_ > 1) {
    head -> next(e_retirar -> next());
  } else {
    head -> next(head);
  }
  delete(e_retirar);
  size_--;
  return return_data;
}

template<typename T>
void structures::CircularList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Circular List Empty");
    }
    size_t index = find(data);
    pop(index);
}

template<typename T>
bool structures::CircularList<T>::empty() const {
    return (size_ == 0);
}

template <typename T>
bool structures::CircularList<T>::contains(const T& data) const {
  if (empty()) {
    throw std::out_of_range("Circular List empty");
  }
  Node *temp = head->next();
  for (size_t i = 0; i < size_; i++) {
    if (temp->data() == data && !temp->sentinela()) {
      return true;
    }
    temp = temp->next();
  }
  return false;
}

template <typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
  Node *temp = head->next();
  for (size_t i = 0; i < size_; i++) {
    if (temp->data() == data && !temp->sentinela()) {
        return i;
    }
    temp = temp->next();
  }
  return size_;
}

template <typename T>
std::size_t structures::CircularList<T>::size() const {
  return size_;
}

#endif
