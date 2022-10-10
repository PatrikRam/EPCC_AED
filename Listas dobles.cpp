#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class Node
{
public:
	template<typename U> friend class List;
	Node(T data) {
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
	~Node(){}
private:
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template <typename T>
class List
{
public:
	List() {
		this->head = nullptr;
		this->size = 0;
	}
	~List() {
		while (head != nullptr){
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}
	void insert_star(T data) {
		Node<T>* new_node = new Node<T>(data);
		if (head == nullptr) {
			head = new_node;
		}
		else {
			new_node->next = head;
			head->prev = new_node;
			head = new_node;
		}
		size++;
	}
	void insert_end(T data) {
		Node<T>* new_node = new Node<T>(data);
		if (head == nullptr) {
			head = new_node;
		}
		else {
			Node<T>* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = new_node;
			new_node->prev = temp;
		}
		size++;
	}
	void insert_free(T data, int pos) {
		Node<T>* new_node = new Node<T>(data);

		if (pos > size || pos < 0)
			throw std::out_of_range("Posicion fuera de rango del tamanio de la lista!");

		else if (head == nullptr && pos == 0) {
			head = new_node;
		}

		else if (head != nullptr && pos == 0) {
			new_node->next = head;
			head->prev = new_node;
			head = new_node;
		}

		else if (head != nullptr && head->next != nullptr && pos > 0 && pos < size) {
			Node<T>* temp1 = head->next;
			int p = 1;
			while (p != pos) {
				temp1 = temp1->next;
				p++;
			}
			new_node->prev = temp1->prev;
			temp1->prev->next = new_node;
			new_node->next = temp1;
			temp1->prev = new_node;
		}
		size++;
	}

	void delete_star() {
		if (head == nullptr)
			throw std::out_of_range("Lista Vacia!");
		else if (head != nullptr && head->next == nullptr) {
			Node<T>* temp = head;
			head = nullptr;
			delete temp;
		}
		else if (head != nullptr && head->next != nullptr) {
			Node<T>* temp = head;
			head = head->next;
			head->prev = nullptr;
			delete temp;
		}
		size--;
	}

	void delete_end() {
		if (head == nullptr)
			throw std::out_of_range("Lista Vacia!");
		else if (head != nullptr && head->next == nullptr) {
			Node<T>* temp = head;
			head = nullptr;
			delete temp;
		}
		else if (head != nullptr && head->next != nullptr) {
			Node<T>* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->prev->next = nullptr;
			delete temp;
		}
		size--;
	}

	void delete_free(int pos) {
		if (pos > size || pos < 0)
			throw std::out_of_range("Fuera de rango!");

		else if (head == nullptr)
			throw std::runtime_error("Lista Vacia!");

		else if (head != nullptr && pos == 0) {
			Node<T>* temp = head;
			head = head->next;
			if (head != nullptr) {
				head->prev = nullptr;
			}
			delete temp;
		}

		else if (head != nullptr && head->next != nullptr && pos < size && pos > 0) {
			Node<T>* temp = head->next;
			int p = 1;
			while (p != pos) {
				temp = temp->next;
				p++;
			}
			if (temp->next != nullptr) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			else {
				temp->prev->next = temp->next;
			}			
		}
		size--;
	}

	const void print() {
		if (head != nullptr) {
			Node<T>* temp = head;
			while (temp != nullptr) {
				cout << temp->data;
				if (temp->next != nullptr)
					cout << "->";
				temp = temp->next;
			}
			cout << endl;
		}
	}

	const void inverse_print() {
		if (head != nullptr) {
			Node<T>* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			while (temp != nullptr) {
				cout << temp->data;
				if (temp->prev != nullptr) {
					cout << "->";
				}
				temp = temp->prev;
			}
			cout << endl;
		}
	}

	bool empty() {
		if (head == nullptr)
			return true;
		return false;
	}

private:
	Node<T>* head;
	int size;
};


int main()
{
	List<int> lista;

	lista.insert_end(10);
	lista.insert_end(210);
	lista.insert_end(110);
	lista.insert_end(510);

	lista.print();
	lista.inverse_print();

	lista.delete_free(3);

	lista.print();
	lista.inverse_print();

	if (lista.empty())
		cout << "Lista Vacia" << endl;
	
    return 0;
}
