package edu.uakron.SinglyLinkedList;

import edu.uakron.LinkedList.LinkedList;

/**
 * Data structure representing a singly linked list.
 *
 * @param <T> Determines the type of the singly linked list.
 */
public class SinglyLinkedList<T> implements LinkedList<T> {
    private Node<T> head;
    private int size;

    /**
     * Default constructor.
     */
    public SinglyLinkedList() {
    }

    /**
     * Constructor.
     *
     * @param arr Array of type T
     */
    public SinglyLinkedList(T[] arr) {
        SinglyLinkedList<T> list = new SinglyLinkedList<>();
        for (T val : arr) {
            list.insert(val);
        }
        this.head = list.getHead();
        this.size = list.size();
    }

    /**
     * Head accessor
     *
     * @return First Node of the list
     */
    public Node<T> getHead() {
        return head;
    }

    /**
     * Gets the number of the Nodes in the list
     *
     * @return The number of Nodes in the list
     */
    public int size() {
        return size;
    }

    @Override
    public boolean insert(T val) {
        Node<T> newNode = new Node<>(val);
        Node<T> currentNode = head;
        if(size == 0) {
            head = newNode;
        } else {
            while (currentNode.getNext() != null) {
                currentNode = currentNode.getNext();
            }
            currentNode.setNext(newNode);
        }
        size++;
        return true;
    }

    @Override
    public boolean insert(int index, T val) {
        Node<T> newNode = new Node<>(val);
        Node<T> currentNode = head;
        for (int i = 1; i < index && currentNode.getNext() != null; i++) {
            currentNode = currentNode.getNext();
        }
        newNode.setNext(currentNode.getNext());
        currentNode.setNext(newNode);
        size++;
        return true;
    }

    @Override
    public boolean removeAtIndex(int index) {
        if(index > size) {
            return false;
        }
        if(index == 0) {
            head = head.getNext();
        } else {
            Node<T> previous = getNode(index - 1);
            previous.setNext(getNode(index).getNext());
        }
        size--;
        return true;
    }

    @Override
    public int indexOf(T val) {
        for(int i = 0; i < size; i++) {
            if(getNode(i).getValue() == val) {
                return i;
            }
        }
        return -1;
    }

    @Override
    public T get(int index) {
        return getNode(index).getValue();
    }

    public Node<T> getNode(int index) {
        if(index > size) {
            throw new IndexOutOfBoundsException();
        } else if(index == 0) {
            return head;
        }
        Node<T> current = head.getNext();
        for(int i = 1; i < index; i++) {
            if(current.getNext() == null) {
                throw new IndexOutOfBoundsException();
            }
            current = current.getNext();
        }
        return current;
    }

    @Override
    public void print() {
        Node<T> current = head;
        for(int i = 0; i < size; i++) {
            System.out.println(current.getValue());
            current = current.getNext();
        }
    }

    @Override
    public Object[] toArray() {
        Object[] arr = new Object[size];
        Node<T> node = head;
        for (int i = 0; i < size; i++) {
            arr[i] = node.getValue();
            node = node.getNext();
        }
        return arr;
    }

    @Override
    public void clear() {
        head = null;
        size = 0;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }
}
