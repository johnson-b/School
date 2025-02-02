package edu.uakron.DoublyLinkedList;

/**
 * Data structure to represent a Node in a DoublyLinkedList
 * @param <T> Type of value of Node
 */
public class Node<T> {
    private T value;
    private Node<T> previous;
    private Node<T> next;

    public Node(T value) {
        this.value = value;
    }

    public T getValue() {
        return value;
    }

    public void setValue(T value) {
        this.value = value;
    }

    public Node<T> getPrevious() {
        return previous;
    }

    public void setPrevious(Node<T> previous) {
        this.previous = previous;
    }

    public Node<T> getNext() {
        return next;
    }

    public void setNext(Node<T> next) {
        this.next = next;
    }
}
