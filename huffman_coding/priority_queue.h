/*
 * priority_queue.h
 *  Created on: May 30, 2015
 */

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

typedef struct q_node Q_node;
typedef struct queue Queue;
typedef struct q_tree Q_tree;

/**
 * Allocates queue, sets its first elem as NULL.
 * @return Pointer to the newly allocated Queue.
 */
Queue* createQueue();

/**
 * Allocates a tree of queue nodes, sets its first elem as NULL and tree size as 0.
 * @return Pointer to the newly allocated Tree.
 */
Q_tree* createQueueTree();

/**
 * Check weather the queue is empty or not
 * @return true(1) if empty, false(0) if not.
 */
int queueIsEmpty(Queue* queue);

/**
 * Takes an already allocated Node and equeues it according to its priority in ASCENDING order.
 * When comparing 2 nodes with the same priority, the new node will be set before the existing one.
 * @param priorityQueue 	The priority queue's root node
 * @param newNode 			An already allocated Node
 * @return 					The priority queue's root node
 */
Queue* insertNodeOnPriorityQueue(Queue* priorityQueue, Q_node* newNode);

/**
 * Takes an already allocated Node and inserts it at the end of the queue.
 * @param priorityQueue 	The priority queue's root node
 * @param newNode 			An already allocated Node
 * @return 					The priority queue's root node
 */
Queue* insertNodeOnQueue(Queue* queue, Q_node* newNode);

/**
 * Allocates a new queue node, setting its priority and value. Its left and right pointers defaults to NULL;
 * @param item 		Node's value
 * @param priority	Node's priority
 * @return 			The new allocated node
 */
Q_node* createQueueNode(char item, int priority);

/**
 * Allocates a new queue node setting its pointers(left & right), priority and value,
 * then inserts the new node in the queue according to its priority in ASCENDING order.
 * @param priorityQueue The priority queue's root node
 * @param item 			Node's value
 * @param priority		Node's priority
 * @return 				The priority queue's root node
 */
Queue* PQ_enqueue(Queue* priorityQueue, char item, int priority);

/**
 * Allocates a new queue node setting its value, then inserts it at the end of the queue.
 * @param priorityQueue The priority queue's root node
 * @param item 			Node's value
 * @return 				The priority queue's root node
 */
Queue* enqueue(Queue* queue, char item);

/**
 * Used while converting queue into tree. (partial removal)
 * Returns first element of the queue (with the lowest priority) then removes it by setting 'nextNode' to NULL
 * and moving the queue's HEAD forward.
 * @param queue 	The priority queue's root node
 * @return  		The priority queue's new root. When the queue is empty, defaults to NULL.
 */
Q_node* dequeue(Queue* queue);

/**
 * (complete removal)
 * Dequeues queue node by moving queue's HEAD forward, then freeing queue's first element and returning its value.
 * @param queue 	The priority queue's root node
 * @return  		The dequeued element's value. When the queue is empty, defaults to -1.
 */
char dequeueAndFree(Queue* queue);

/**
 * Prints every element of the queue in order.
 * @param queue 	The priority queue's root node
 */
void printPriorityQueue(Queue* queue);

/**
 * Prints the elements of a tree in pre-order.
 * @param node 	The tree's root node
 */
void printQueueTreePreOrder(Q_node* node);

/**
 * Free every element of the queue.
 * @param queue 	The priority queue's root node
 */
void freePriorityQueue(Queue* queue);

/**
 * Free every element of the tree.
 * @param first 	The tree's root node
 */
void freeQueueTree(Q_node* first);

/**
 * Returns the number of elements on given queue.
 * @param queue 	The priority queue's root node
 * @return 			Number of elements on queue (Queue size)
 */
int getQueueLength(Queue* queue);

/**
 * Takes the first 2 nodes of given queue, remove them and set both as left and right childs of a new allocated node
 * which value is set to '*' and priority set to the sum of its children, then enqueues this new node into the priority
 * queue. Repeat those steps until theres only one element on the queue, therefore generating a tree.
 * @param queue 	The priority queue's root node
 * @return 			New huffman tree.
 */
Q_tree* mergeQueueIntoHuffmanTree(Queue* queue);

/**
 * Writes each node value of a tree on a given file (in pre-order).
 * @param pFile The pointer to the opened file.
 * @param node 	The tree's root node
 * @param tree 	The huffman tree
 */
void writeTreeOnFile(FILE *pfile, Q_node *node, Q_tree *tree);

/*
 * Creates a new file for decompressing and gets last byte position, then using the
 * huffman tree while reading the compressed file, follows the path to the right letter
 * using the 0's and 1's logic. Upon reaching a leaf, write the correspondent letter to
 * the new decompressed file. Repeat until it reaches the last byte and use the trash size
 * to limit the reading.
 * @param pFile 		The pointer to an opened file
 * @param huffmantree 	The huffman tree
 * @param trashSize 	The size of the trash
 */
void readTraslateWrite(FILE *pFile, Q_node *huffmanTree, int trashSize);


/*======== Getters ========*/

/**
 * Gets the tree's root node.
 * @param tree 	A tree of queue nodes
 * @return 		The tree's root node
 */
Q_node* getTreeRootNode(Q_tree* tree);

/**
 * Gets the tree's size.
 * @param tree 	A tree of queue nodes
 * @return 		The tree's size
 */
Q_node* getTreeSize(Q_tree* tree);

/**
 * Gets the left node of a Queue.
 * @param node 	A priority queue's node
 * @return 		The node's left child
 */
Q_node* getQueueNodeLeft(Q_node* node);

/**
 * Gets the right node of a Queue.
 * @param node 	A priority queue's node
 * @return 		The node's right child (not the wrong one haha)
 */
Q_node* getQueueNodeRight(Q_node* node);

/**
 * Gets the queue node's value.
 * @param node 	A priority queue's node
 * @return 		The node's value
 */
char getQueueNodeValue(Q_node* node);

#endif /* PRIORITY_QUEUE_H_ */
