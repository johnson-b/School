package edu.uakron.DoublyLinkedList;

import edu.uakron.LinkedList.LinkedList;

/**
 * Data structure representing a doubly linked list.
 *
 * @param <T> Determines the type of the doubly linked list.
 */
public class DoublyLinkedList<T> implements LinkedList<T> {
    private Node<T> head;
    private Node<T> tail;
    private int size;

    /**
     * Default constructor.
     */
    public DoublyLinkedList() {
    }

    /**
     * Constructor.
     *
     * @param arr Array of type T
     */
    public DoublyLinkedList(T[] arr) {
        DoublyLinkedList<T> list = new DoublyLinkedList<>();
        for (T val : arr) {
            list.insert(val);
        }
        this.head = list.getHead();
        this.tail = list.getTail();
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
     * Tail accessor
     *
     * @return Last Node of the list
     */
    public Node<T> getTail() {
        return tail;
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
        switch (size) {
            case 0:
                head = new Node<>(val);
                tail = head;
                size++;
                break;
            case 1:
                tail = new Node<>(val);
                tail.setPrevious(head);
                head.setNext(tail);
                size++;
                break;
            default:
                Node<T> temp = tail;
                tail = new Node<>(val);
                tail.setPrevious(temp);
                temp.setNext(tail);
                size++;
        }
        return true;
    }

    @Override
    public boolean insert(int index, T val) {
        if (index < 1) {
            return false;
        } else if (index > size) {
            return false;
        } else if (index == 0) {
            Node<T> temp = head;
            head = new Node<>(val);
            temp.setPrevious(head);
            head.setNext(temp);
            size++;
        } else if (index == size) {
            this.insert(val);
        } else {
            Node<T> temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp.getNext();
            }
            Node<T> temp2 = new Node<>(val);
            temp2.setPrevious(temp.getPrevious());
            temp2.setNext(temp);
            temp.setPrevious(temp2);
            temp2.getPrevious().setNext(temp2);
            size++;
        }
        return true;
    }

    @Override
    public boolean removeAtIndex(int index) {
        if (index < 0) {
            return false;
        } else if (index > size - 1) {
            return false;
        } else if (index == 0) {
            if (size == 1) {
                head = null;
                tail = null;
            } else {
                head = head.getNext();
                head.setPrevious(null);
            }
            size--;
        } else if (index == (size - 1)) {
            if (size == 1) {
                head = null;
                tail = null;
            } else {
                tail = tail.getPrevious();
                tail.setNext(null);
            }
            size--;
        } else {
            Node<T> temp = head;
            if (index == 1) {
                temp = temp.getNext();
            } else {
                for (int i = 0; i < index; i++) {
                    temp = temp.getNext();
                }
            }
            temp.getPrevious().setNext(temp.getNext());
            temp.getNext().setPrevious(temp.getPrevious());
            size--;
        }
        return true;
    }

    @Override
    public int indexOf(T val) {
        Node<T> temp = head;
        if (temp.getValue() == val) {
            return 0;
        }
        for (int i = 0; i < size - 1; i++) {
            temp = temp.getNext();
            if (temp.getValue() == val) {
                return i + 1;
            }
        }
        return -1;
    }

    @Override
    public T get(int index) {
        if (index == 0) {
            return head.getValue();
        } else if (index == size - 1) {
            return tail.getValue();
        } else if (index >= size) {
            throw new IndexOutOfBoundsException();
        } else if (index == 1) {
            return head.getNext().getValue();
        } else {
            Node<T> temp = head;
            for (int i = 0; i <= index; i++) {
                temp = temp.getNext();
            }
            return temp.getValue();
        }
    }

    @Override
    public void print() {
        Node<T> temp = head;
        for (int i = 0; i < size; i++) {
            System.out.println(temp.getValue());
            temp = temp.getNext();
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
        tail = null;
        size = 0;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }
}