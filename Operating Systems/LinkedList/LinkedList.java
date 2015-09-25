package edu.uakron;

/**
 * Copyright bryanjohnson
 * <p>
 * 9/25/15 3:41 PM
 */
public interface LinkedList<T> {

    /**
     * Inserts new node at the end of the list.
     * @param val Value of new node to be inserted
     * @return true if node was inserted successfully, false otherwise
     */
    boolean insert(T val);

    /**
     * Inserts new node into list at given index
     * @param index Zero based index where node will be inserted
     * @param val Value of new node to be inserted
     * @return true if node was inserted successfully, false otherwise
     */
    boolean insert(int index, T val);

    /**
     * Removes node in list at index
     * @param index Zero based index of node to be removed
     * @return true if node is removed successfully, false otherwise
     */
    boolean removeAtIndex(int index);

    /**
     * Removes node based on found value in list
     * @param val Value of node to be removed
     * @return true if node is removed successfully, false otherwise
     */
    boolean removeValue(T val);

    /**
     * Finds the index of the first node in the list with the value 'val'
     * @param val Value of node to be searched
     * @return Zero based index of node in list, -1 if not found
     */
    int indexOf(T val);

    /**
     * Gets the value of the node with index
     * @param index Index of node being searched for
     * @return T value of node with index
     */
    T get(int index);

    /**
     * Prints out each value of the list on a new line
     */
    void print();

    /**
     * Returns an array of T values
     * @return Array of T values
     */
    Object[] toArray();

    /**
     * Removes all nodes of the list
     */
    void clear();

    /**
     * Determines if list is empty
     * @return true if size is equal to zero, false otherwise
     */
    boolean isEmpty();
}
