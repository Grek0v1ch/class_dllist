#ifndef DLLIST_HPP
#define DLLIST_HPP

#include <iostream>
#include <fstream>

template <typename Type> class list;

template <typename Type> class node {
private:
	Type _value;
	node* _next;
	node* _previous;
public:
	node(Type value) : _value(value), _next(0), _previous(0) {}
	node<Type>* get_next() const { return _next; }
	node<Type>* get_pervious() const { return _previous; }
	void set_value(Type value) { _value = value; }
	template <typename Type1> friend class list;
};


template <typename Type> using pnode = node<Type>*;


template <typename Type> class list {
private:
	pnode<Type> _first;
	pnode<Type> _last;
public:
	list() : _first(0), _last(0) { std::cerr << "debag:first_constructor\n"; }
	~list();

	// Проверка списка на пустоту.
	bool is_empty() { return _first == 0; }
	// Возвращает значение первого элемента в списке.
	pnode<Type> front() { return _first; }
	// Возвращает значение последнего элемента в списке.
	pnode<Type> back() { return _last; }

	// Добавляет элемент в конец списка.
	void push_back(Type);
	// Добавляет элемент в начало списка.
	void push_front(Type);

	// Функция удаляет первый элемент из ненулевого списка.
	void remove_first();
	// Функция удаляет последний элемент из ненулевого списка.
	void remove_last();

	// Печать списка в консоль.
	void print();
	// Печать списка в файл.
	void fprint(std::ofstream&);
};

template <typename Type> list<Type>::~list() {
	pnode<Type> curr = _first;
	while(curr != 0) {
		pnode<Type> temp = curr->_next;
		delete curr;
		curr = temp;
	}
	std::cerr << "debag:destructor\n";
}

// Добавляет элемент в конец списка.
template <typename Type> void list<Type>::push_back(Type value) {
	pnode<Type> new_el = new node<Type>{value};
	if (is_empty()) {
		_first = new_el;
		_last = new_el;
		std::cerr << "debag:push_back{" << value << "}:is_empty\n";
		return;
	}
	_last->_next = new_el;
	new_el->_previous = _last;
	_last = new_el;
	std::cerr << "debag:push_back{" << value << "}\n";
}

// Добавляет элемент в начало списка.
template <typename Type> void list<Type>::push_front(Type value) {
	if (is_empty()) {
		push_back(value);
		std::cerr << "debag:push_front{" << value << "}:is_empty\n";
		return;
	}
	pnode<Type> new_el = new node<Type>{value};
	new_el->_next = _first;
	_first->_previous = new_el;
	_first = new_el;
	std::cerr << "debag:push_front{" << value << "}\n";
}

// Функция удаляет первый элемент из ненулевого списка.
template <typename Type> void list<Type>::remove_first() {
	// В случае нулевого списка функция никак не изменяет список.
	if (is_empty()) {
		std::cerr << "debag:remove_first:is_empty\n";
		return;
	}
	pnode<Type> curr = _first;
	_first = curr->_next;
	_first->_previous = 0;
	delete curr;
	std::cerr << "debag:remove_first\n";
}

// Функция удаляет последний элемент из ненулевого списка.
template <typename Type> void list<Type>::remove_last() {
	// В случае нулевого списка функция никак не изменяет список.
	if (is_empty()) {
		std::cerr << "debag:remove_last:is_empty\n";
		return;
	}
	pnode<Type> curr = _last;
	_last = _last->_previous;
	_last->_next = 0;
	delete curr;
	std::cerr << "debag:remove_last\n";
}

// Печать списка в консоль.
template <typename Type> void list<Type>::print() {
	pnode<Type> curr = _first;
	while (curr) {
		std::cout << curr->_value << ' ';
		curr = curr->_next;
	}
	std::cout << '\n';
}

// Печать списка в файл.
template <typename Type> void list<Type>::fprint(std::ofstream& fout) {
	pnode<Type> curr = _first;
	while (curr) {
		fout << curr->_value << ' ';
		curr = curr->_next;
	}
	fout << '\n';
}

#endif // DLLIST_HPP