#include <iostream>
using std::cout;
using std::endl;

template<typename T>
class Node
{
public:
	template<typename U> friend class List;
	Node(T data) {
		this->data = data;
		this->next = nullptr;
	}
	~Node(){}
private:
	T data;
	Node<T>* next;
};

template<typename T>
class List
{
public:
	List() {
		this->head = nullptr;
		this->size = 0;
	}
	~List(){
		while (head != nullptr) {
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
		}
		size++;
	}

	void insert_free(T data, int pos) {

		if (pos > size || pos < 0)
			throw std::out_of_range("Posicion fuera del rango de la lista!");

		Node<T>* new_node = new Node<T>(data);

		if (pos == 0) {
			new_node->next = head;
			head = new_node;
		}
		else if (head != nullptr && pos <= size && pos > 0) {
			Node<T>* temp1 = head->next;
			Node<T>* temp2 = head;
			int p = 1;
			while (p != pos) {
				temp2 = temp1;
				temp1 = temp1->next;
				p++;
			}
			temp2->next = new_node;
			new_node->next = temp1;
		}
		size++;
	}

	void delete_star() {
		if (head == nullptr)
			throw std::runtime_error("Lista  Vacia!");
		else {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			size--;
		}
	}

	void delete_last() {
		if (head == nullptr)
			throw std::runtime_error("Lista  Vacia!");

		else if (head != nullptr && head->next == nullptr) {
			Node<T>* temp1 = head;
			head = nullptr;
			delete temp1;
		}

		else {
			Node<T>* temp1 = head->next;
			Node<T>* temp2 = head;
			while (temp1->next != nullptr) {
				temp2 = temp1;
				temp1 = temp1->next;
			}
			temp2->next = nullptr;
			delete temp1;
		}
		size--;
	}
	void delete_free(int pos) {

		if (pos < 0 || pos >= size)
			throw std::out_of_range("La posicion ingresada esta fuera del rango de la lista!");

		else if (head != nullptr && pos == 0) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}

		else if (head != nullptr && head->next != nullptr && pos > 0 && pos < size) {
			Node<T>* temp1 = head->next;
			Node<T>* temp2 = head;
			int p = 1;
			while (p != pos) {						
				temp2 = temp1;
				temp1 = temp1->next;
				p++;
			}
			temp2->next = temp1->next;
			delete temp1;
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
	int get_size() {
		return size;
	}

private:
	Node<T>* head;
	int size;
};

int main()
{
	List<int> mi_lista;

	mi_lista.insert_star(10);
	mi_lista.insert_star(50);
	mi_lista.insert_star(20);
	mi_lista.insert_star(30);

	mi_lista.print();

	mi_lista.delete_free(3);

	mi_lista.print();


	return 0;
}
