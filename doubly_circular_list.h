//! Copyright [2019] <Bryan Martins Lima>
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

//! Classe de implementação de lista circular dupla
template<typename T>
class DoublyCircularList {
 public:
    //! construtor padrão de lista circular dupla
    DoublyCircularList();
    //! destrutor de lista circular
    ~DoublyCircularList();
    //! método para limpar a lista circular
    void clear();
    //! método para inserir dados no fim
    void push_back(const T& data);
    //! metodo insere no inicio
    void push_front(const T& data);
    //! metodo insere na posicao
    void insert(const T& data, std::size_t index);
    //! metodo insere em ordem
    void insert_sorted(const T& data);
    //! metodo retira da posicao
    T pop(std::size_t index);
    //! metodo retira do fim
    T pop_back();
    //! metood retira do inicio
    T pop_front();
    //! retira especifico
    void remove(const T& data);
    //! lista vazia
    bool empty() const;
    //! contem
    bool contains(const T& data) const;
    //! acesso a um elemento (checando limites)
    T& at(std::size_t index);
    //! getter constante a um elemento
    const T& at(std::size_t index) const;
    //! posição de um dado
    std::size_t find(const T& data) const;
    //! tamanho
    std::size_t size() const;

 private:
    class Node {
     public:
        //! construtor padrao
        explicit Node(const T& data):
            data_{data}
        {}
        //! construtor com data e next
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        //! construtor com data, previous e next
        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}
        //! getter: dado
        T& data() {
            return data_;
        }
        //! getter const: dado
        const T& data() const {
            return data_;
        }
        //! getter: previous
        Node* prev() {
            return prev_;
        }
        //! getter const: previous
        const Node* prev() const {
            return prev_;
        }
        //! setter: previous
        void prev(Node* node) {
            prev_ = node;
        }
        //! getter: next
        Node* next() {
            return next_;
        }
        //! getter const: next
        const Node* next() const {
            return next_;
        }
        //! setter: next
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };
    //! nodo-topo
    Node* head;
    //! tamanho
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    size_ = 0;
    head = nullptr;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    Node *new_element = new Node(data, nullptr, nullptr);
    if (new_element == nullptr) {
        throw std::out_of_range("DoublyCircularList Full");
    }
    if (!empty()) {
        Node *temp = head->prev();
        new_element->next(head);
        new_element->prev(temp);
        temp->next(new_element);
        head->prev(new_element);
    } else {
        new_element->next(new_element);
        new_element->prev(new_element);
        head = new_element;
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node *new_element = new Node(data, nullptr, nullptr);
    if (new_element == nullptr) {
        throw std::out_of_range("DoublyCircularList Full");
    }
    if (size_ == 0) {
        new_element->next(new_element);
        new_element->prev(new_element);
        head = new_element;
    } else {
        new_element->next(head);
        if (size_ == 1) {
            new_element->prev(head);
            head->next(new_element);
        } else {
            new_element->prev(head->prev());
            head->prev()->next(new_element);
        }
        head->prev(new_element);
        head = new_element;
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data,
                                        std::size_t index) {
    if (index > size_) throw std::out_of_range("Index invalido");
    if (index == 0) {
        push_front(data);
    } else {
        if (index == size_) {
            push_back(data);
        } else {
            if (empty()) {
                push_front(data);
            } else {
               Node *new_element = new Node(data, nullptr, nullptr);
               if (new_element == nullptr) {
                throw std::out_of_range("DoublyCircularList full");
               }
               Node *temp = nullptr;
               size_t interval = size_/2;
               if (index <= interval) {
                temp = head;
                for (size_t i = 0; i < index; i++) {
                    temp = temp->next();
                }
               } else {
                    temp = head;
                    for (size_t i = 0; i < (size_ - index); i++) {
                        temp = temp->prev();
                    }
               }
               new_element->next(temp);
               new_element->prev(temp->prev());
               temp->prev()->next(new_element);
               temp->prev(new_element);
               size_++;
            }
        }
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node *temp = head;
        size_t index = 0;
        while (index < size_ && temp != nullptr && data > temp->data()) {
            index++;
            temp = temp->next();
        }
        insert(data, index);
    }
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Empty Doubly Linked List");
    }
    if (index >= size_) {
        throw std::out_of_range("Invalid Index");
    }
    Node *temp = nullptr;
    size_t interval = (size_)/ 2;
    if (index <= interval) {
        temp = head;
        for (size_t i = 0; i < index; i++) {
            temp = temp->next();
        }
    } else {
        temp = head->prev();
        for (size_t i = 0; i < (size_ - index - 1); i++) {
            temp = temp->prev();
        }
    }
    return temp->data();
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("Empty Doubly Linked List");
    }
    if (index >= size_) {
        throw std::out_of_range("Invalid Index");
    }
    Node *temp = nullptr;
    size_t interval = (size_)/ 2;
    if (index <= interval) {
        temp = head;
        for (size_t i = 0; i < index; i++) {
            temp = temp->next();
        }
    } else {
        temp = head->prev();
        for (size_t i = 0; i < (size_ - index - 1); i++) {
            temp = temp->prev();
        }
    }
    return temp->data();
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("DoublyCircularList is empty");
    }
    if (index >= size_) {
        throw std::out_of_range("Index invalido");
    }
    if (index == 0) {
        return pop_front();
    } else {
        if (index == size_ -1) {
            return pop_back();
        } else {
            Node *retira_elemento = nullptr;
            T return_data;
            size_t interval = size_/2;
            if (index <= interval) {
                retira_elemento = head;
                for (size_t i = 0; i < index; i++) {
                    retira_elemento = retira_elemento->next();
                }
            } else {
                retira_elemento = head->prev();
                for (size_t i = 0; i < (size_ - index - 1); i++) {
                    retira_elemento = retira_elemento->prev();
                }
            }
            return_data = retira_elemento->data();
            retira_elemento->prev()->next(retira_elemento->next());
            retira_elemento->next()->prev(retira_elemento->prev());
            size_--;
            delete(retira_elemento);
            return return_data;
        }
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("DoublyCircularList is empty");
    }
    Node *retira_elemento = nullptr;
    T return_data;
    if (size_ > 1) {
        retira_elemento = head->prev();
        return_data = retira_elemento->data();
        retira_elemento->prev()->next(head);
        head->prev(retira_elemento->prev());
    } else {
        retira_elemento = head;
        return_data = retira_elemento->data();
        head = nullptr;
    }
    size_--;
    delete(retira_elemento);
    return return_data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("DoublyCircularList is empty");
    }
    Node *retira_elemento = head;
    T return_data = retira_elemento->data();
    if (size_ > 1) {
        retira_elemento->prev()->next(retira_elemento->next());
        retira_elemento->next()->prev(retira_elemento->prev());
        head = retira_elemento->next();
    } else {
        head = nullptr;
    }
    size_--;
    delete(retira_elemento);
    return return_data;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Circular List Empty");
    }
    size_t index = find(data);
    pop(index);
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return (size_ == 0);
}

template <typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    if (empty()) {
        throw std::out_of_range("Empty DoublyCircularList");
    }
    Node *temp = head;
    for (size_t i = 0; i < size_; i++) {
        if (temp->data() == data) {
            return true;
        } else {
            temp = temp->next();
        }
    }
    return false;
}

template <typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    Node* temp = head;
    for (size_t i = 0; i < size_; i++) {
        if (temp->data() == data) {
            return i;
        }
        temp = temp->next();
    }
    return size_;
}

template <typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
  return size_;
}

#endif
