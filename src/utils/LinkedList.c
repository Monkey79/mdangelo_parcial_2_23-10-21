#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

#define NO_MEMORY_ERROR "-Error: No hay espacion en la memoria-\n"

static Node* getNode(LinkedList *this, int nodeIndex);
static int addNode(LinkedList *this, int nodeIndex, void *pElement);

void _swapNodes(Node* pNodeA, Node* pNodeB);
Node* _createNewEmptyNode(void);


/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *  o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void) {
	LinkedList *this;
	this = (LinkedList*) malloc(sizeof(LinkedList));
	if (this != NULL) {
		this->size = 0;
		this->pFirstNode = NULL;
	}
	return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL
 * o la cantidad de elementos de la lista
 */
int ll_len(LinkedList *this) {
	int len = -1;
	if (this != NULL) {
		len = this->size;
	}
	return len;
}

/** \brief  Obtiene un nodo de la lista
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL
 * o (si el indice es menor a 0 o mayor al len de la lista) (pElement) Si funciono correctamente
 */
static Node* getNode(LinkedList *this, int nodeIndex) {
	Node *pNode = NULL;
	int len = 0;
	int i = 0;
	if (this != NULL) {
		len = ll_len(this);
		if (nodeIndex >= 0 && nodeIndex<len) {
			pNode = this->pFirstNode;
			while (i < nodeIndex) {
				pNode = pNode->pNextNode;
				i++;
			}
		}
	}
	return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList *this, int nodeIndex) {
	return getNode(this, nodeIndex);
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList *this, int nodeIndex, void *pElement) {
	return ll_push(this, nodeIndex, pElement);
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList *this, int nodeIndex, void *pElement) {
	return addNode(this, nodeIndex, pElement);
}

/** \brief  Agrega un elemento AL FINAL de la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */
//la lista tiene que aceptar cualquier cosa
int ll_add(LinkedList *this, void *pElement) {
	int success = -1;
	int indice = 0;

	//NOTE: Para que corran todos los castos agregue como validacion que el elemento (asi como la lista) NO sea nulo
	if (this != NULL) { // && pElement != NULL
		indice = ll_len(this);
		success = ll_push(this, indice, pElement);
	}
	return success;
}


/** \brief Retorna un puntero al elemento que se encuentra en el índice especificado
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o
 * (si el indice es menor a 0 o mayor al len de la lista)
 * (pElement) Si funciono correctamente
 */
void* ll_get(LinkedList *this, int index) {
	Node *pNode = NULL;
	if (this != NULL && index>=0) pNode = getNode(this, index);
	return (pNode != NULL) ? pNode->pElement : NULL;
}

/** \brief Inserta un elemento en el LinkedList, en el índice especificado.
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 * ( 0) Si funciono correctamente
 */
int ll_set(LinkedList *this, int index, void *pElement) {
	int success = -1;

	if (this != NULL && index>=0 && index<this->size) {
		success = ll_push(this, index, pElement);
	}
	return success;
}

/** \brief Elimina un elemento de la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 * (0) Si funciono correctamente
 */
int ll_remove(LinkedList *this, int index) {
	int result = -1;
	Node* nodeDel = NULL;
	Node* prevNode = NULL;

	if(this != NULL){
		nodeDel = getNode(this, index);
		if(nodeDel!=NULL && index>=0 && index<ll_len(this)){
			if(index == 0){
				this->pFirstNode = nodeDel->pNextNode;
				free(nodeDel);
				this->size--;
				result = 0;
			}else{
				prevNode = getNode(this, index-1);
				if(prevNode!=NULL){
					prevNode->pNextNode = nodeDel->pNextNode;
					free(nodeDel);
					this->size--;
					result = 0;
				}

			}
		}
	}
	return result;
}

/** \brief Elimina todos los elementos de la lista
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 * ( 0) Si funciono correctamente
 */
int ll_clear(LinkedList *this) {
	int success = -1;
	int i;
	int len;
	if (this != NULL) {
		if(this->size == 0) {
			success = 0;
		}else{
			len = ll_len(this);
			for (i = 0; i < len; i++) {
				success = ll_remove(this, i);
			}
		}
	}
	return success;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList *this) {
	int returnAux = -1;
	if (this != NULL) {
		ll_clear(this);
		free(this);
		returnAux = 0;
	}
	return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList *this, void *pElement) {
	int returnAux = -1;
	int len;
	int i;
	int found = 0;
	void *pAnElement;
	if (this != NULL) {
		len = ll_len(this);
		for (i = 0; i < len && !found; i++) {
			pAnElement = ll_get(this, i);
			found = (pAnElement == pElement);
		}
		returnAux = (found) ? (i - 1) : returnAux;
	}
	return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si la lista NO esta vacia
 ( 1) Si la lista esta vacia
 */
int ll_isEmpty(LinkedList *this) {
	int returnAux = -1;

	if (this != NULL) {
		if (ll_len(this)) {
			returnAux = 0;
		} else {
			returnAux = 1;
		}
	}
	return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 */
int ll_push(LinkedList* this, int index, void* pElement) {
	int success = 0;

	Node *newNode = NULL;
	Node *crrntNd;
	Node *nextNd;

	int len;

	if (this != NULL) {
		len = ll_len(this);
		newNode = _createNewEmptyNode();
		if(newNode!=NULL) newNode->pElement = pElement; else exit(0);

		if(index>=0 && index<=len){
			if(index==0){ //[1] Principio de la lista
				crrntNd = getNode(this,0);
				newNode->pNextNode = crrntNd;
				this->pFirstNode = newNode;
				this->size++;
			}else if(index<len){ //[2] Medio de la lista
				crrntNd = getNode(this, index-1);
				nextNd = crrntNd->pNextNode;

				newNode = nextNd;
				crrntNd->pNextNode = newNode;
				this->size++;
			}else if(index==len){ //[3] Fin de la lista
				crrntNd = getNode(this,len-1);
				crrntNd->pNextNode = newNode;
				this->size++;
			}
		}else{
			success = -1;
		}
	}else{
		success = -1;
	}
	return success;
}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna (NULL) Error: si el puntero a
 * la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 * (pElement) Si funciono correctamente
 */
void* ll_pop(LinkedList *this, int index) {
	void *result = NULL;
	Node *actual;
	int len = ll_len(this);

	if (this != NULL && (index>=0 && index<len)) {
		actual = getNode(this, index);
		if(actual->pElement != NULL){
			free(actual->pElement);
			result = actual->pElement;
			actual->pElement = NULL;
			this->size--;
		}
	}
	return result;
}

/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 1) Si contiene el elemento
 ( 0) si No contiene el elemento
 */
int ll_contains(LinkedList *this, void *pElement) {
	int returnAux = -1;
	if (this != NULL) {
		returnAux = (ll_indexOf(this, pElement) >= 0) ? 1 : 0;
	}
	return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
 estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
 ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
 ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
 */
int ll_containsAll(LinkedList *this, LinkedList *this2) {
	int returnAux = -1;
	int equals;
	int len;
	int i;
	Node *nodo;

	if (this != NULL && this2 != NULL) {
		len = ll_len(this2);
		for (i = 0; i < len && equals; i++) {
			nodo = getNode(this2, i);
			equals = ll_contains(this, nodo->pElement);
		}
		returnAux = (equals) ? 1 : 0;
	}

	return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
 o (si el indice from es menor a 0 o mayor al len de la lista)
 o (si el indice to es menor o igual a from o mayor al len de la lista)
 (puntero a la nueva lista) Si ok
 */
LinkedList* ll_subList(LinkedList *this, int from, int to) {
	LinkedList *cloneArray = NULL;
	int e = 0;
	int len;
	Node *node;
	if (this != NULL) {
		len = ll_len(this);
		if (from >= 0 && to <= len) {
			cloneArray = ll_newLinkedList();
			for (int i = from; i < to; i++) {
				node = getNode(this, i);
				addNode(cloneArray, e, node->pElement);
				e++;
			}
		}
	}
	return cloneArray;
}

/** \brief
 * Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
 (puntero a la nueva lista) Si ok
 */
LinkedList* ll_clone(LinkedList *this) {
	LinkedList *cloneArray = NULL;
	int len;
	Node *node;
	if (this != NULL) {
		len = ll_len(this);
		cloneArray = ll_newLinkedList();
		for (int i=0; i<len; i++) {
			node = getNode(this, i);
			addNode(cloneArray, i, node->pElement);
		}
	}
	return cloneArray;
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
 ( 0) Si ok
 */
int ll_sort(LinkedList *this, int (*pFunc)(void*, void*), int order) {
	int returnAux = -1;
	int len=0;
	Node* pNodeA;
	Node* pNodeB;
	int pFuncRslt;

	if(this!=NULL && pFunc!=NULL && (order==1 || order==0)){
		len = ll_len(this);
		for(int i=0;i<len-1;i++){
			pNodeA = getNode(this, i);
			for(int e=i;e<len;e++){
				pNodeB = getNode(this, e);
				if(pNodeA!=NULL && pNodeB!=NULL){
					pFuncRslt = pFunc(pNodeA->pElement,pNodeB->pElement);
					if(order==1 && pFuncRslt==1){
						_swapNodes(pNodeA,pNodeB);
					}else if(order==0 && pFuncRslt==-1){
						_swapNodes(pNodeA,pNodeB);
					}
				}
			}
		}//end for
		returnAux=0;
	}
	return returnAux;
}

/** \brief Filtra los elementos de la lista utilizando
 * la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
 * (0) Si ok
 */
int ll_filter(LinkedList *this, int (*pFnFlt)(void*)){
	int rtn = -1;
	void* pElm; //elemento del nodo
	int criterio;

	if(this != NULL && pFnFlt!= NULL){
		for (int i=ll_len(this)-1; i>=0; i--){
			pElm = ll_get(this,i);
			if(pElm != NULL){
				criterio = pFnFlt(pElm);
				if(criterio==0){ //si el criterio da 0 (no se cumple) lo elimino
					rtn = ll_remove(this,i);
				}
			}
			rtn = 0;
		}
	}
	return rtn;
}

/** \brief Mapea (modifica) los elementos de la lista utilizando
 * la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
 * (0) Si ok
 */
int ll_map(LinkedList* this, int (*pFnMap)(void*)){
	int rtn = -1;
	int llen;
	void* pElm; //elemento del nodo

	if(this != NULL && pFnMap!= NULL){
		llen = ll_len(this);
		for (int i = 0; i < llen; i++){
			pElm = ll_get(this,i);
			if(pElm != NULL) pFnMap(pElm);
			rtn = 0;
		}
	}
	return rtn;
}



//------------Private----------------------------
void _swapNodes(Node* pNodeA, Node* pNodeB){
	void *pAux;
	pAux = pNodeA->pElement;
	pNodeA->pElement = pNodeB->pElement;
	pNodeB->pElement = pAux;
}

Node* _createNewEmptyNode(void){
	Node* newNode = NULL;
	newNode = (Node*) malloc(sizeof(Node));
	if(newNode != NULL){
		newNode->pNextNode = NULL;
	}else{
		printf(NO_MEMORY_ERROR);
	}
	return newNode;
}

