#ifndef LIST_H
#define LIST_H

#include <string>
#include <sstream>
#include <stdexcept> // Para usar excepciones como out_of_range

using namespace std;

// Estructura del Nodo (Link)
// Es la unidad fundamental de la lista ligada
template <class T>
struct Link {
	T value;
	Link<T> *next;

	// Constructor para crear un nodo
	Link(T val) : value(val), next(nullptr) {}
};

// Clase List: Contiene la lógica para manipular los nodos
template <class T>
class List {
private:
	Link<T> *head; // Puntero al inicio de la lista
	int size;      // Contador de elementos

public:
	// Constructor: Inicializa la lista vacía
	List() : head(nullptr), size(0) {}

	// Destructor: Libera toda la memoria usada por los nodos (evita fugas de memoria y es muy util)
	~List() {
		Link<T> *p, *q;
		p = head;
		while (p != nullptr) {
			q = p->next;
			delete p;
			p = q;
		}
		head = nullptr;
		size = 0;
	}

    /**
     * insertion: Inserta un nuevo elemento al final de la lista.
     * La política de acceso para esta lista es añadir al final (tail insertion)
     */
	void insertion(T val) {
		Link<T> *new_link = new Link<T>(val);
		
		// Caso 1: Lista vacía
		if (head == nullptr) {
			head = new_link;
		} else {
			// Caso 2: Buscar el final de la lista
			Link<T> *p = head;
			while (p->next != nullptr) {
				p = p->next;
			}
			p->next = new_link;
		}
		size++;
	}

    // search: Busca un elemento por valor y retorna su índice (posición)
	int search(T val) const {
		Link<T> *p = head;
		int index = 0;

		while (p != nullptr) {
			if (p->value == val) {
				return index;
			}
			p = p->next;
			index++;
		}
		return -1; // No se encontró
	}

    // update: Actualiza el valor de un elemento en una posición específica
	void update(int index, T val) {
		// Validamos el índice para evitar acceder fuera de la lista
		if (index < 0 || index >= size) {
			throw out_of_range("Error: Indice fuera de rango para update.");
		}

		Link<T> *p = head;
		// Recorremos hasta la posición deseada
		for (int i = 0; i < index; i++) {
			p = p->next;
		}
		// Actualizamos el valor
		p->value = val;
	}

    // deleteAt: Elimina un elemento en una posición específica y retorna su valor
	T deleteAt(int index) {
		if (index < 0 || index >= size) {
			throw out_of_range("Error: Indice fuera de rango para deleteAt.");
		}

		Link<T> *p, *q;
		T deleted_value;

		// Caso 1: Eliminar la CABEZA (índice 0)
		if (index == 0) {
			p = head;
			head = p->next;
			deleted_value = p->value;
			delete p;
		} else {
			// Caso 2: Eliminar en cualquier otra posición
			p = head;
			// Recorremos hasta el nodo ANTERIOR al que queremos borrar (index - 1)
			for (int i = 0; i < index - 1; i++) {
				p = p->next;
			}
			
			q = p->next; // "q" es el nodo a borrar
			p->next = q->next; // El nodo anterior apunta al sucesor de "q"
			deleted_value = q->value;
			delete q; // Liberamos la memoria del nodo borrado
		}

		size--;
		return deleted_value;
	}

	// Método de formato (toString) = Método para convertir la lista a una cadena de texto
	std::string toString() const {
		std::stringstream aux;
		Link<T> *p;

		p = head;
		aux << "[";
		while (p != nullptr) {
			aux << p->value;
			if (p->next != nullptr) {
				aux << ", ";
			}
			p = p->next;
		}
		aux << "]";
		return aux.str();
	}
};

#endif /* LIST_H */