package edu.uakron;

/**
 * Copyright bryanjohnson
 * <p>
 * 9/19/15 7:41 PM
 */
public class DoublyLinkedList<T> {
    private Node<T> head;
    private Node<T> tail;
    private int size;

    public boolean insert(T data) {
        switch (size) {
            case 0:
                head = new Node<>(data);
                tail = head;
                size++;
                break;
            case 1:
                tail = new Node<>(data);
                tail.setPrevious(head);
                head.setNext(tail);
                size++;
            default:
                Node<T> insert = tail;
                tail = new Node<>(data);
                tail.setPrevious(insert);
                insert.setNext(tail);
                size++;
        }
        return true;
    }

    public boolean insert(int index, T data) {
        if (index < 1) {
            return false;
        } else if (index > size) {
            return false;
        } else if (index == 0) {
            Node<T> temp = head;
            head = new Node<>(data);
            temp.setPrevious(head);
            head.setNext(temp);
            size++;
        } else if (index == size) {
            this.insert(data);
        } else {
            // add to index
            
        }


        return true;
    }
    // public void remove(int index)
    // public void remove(T data)
    // public int indexOf(T data)
    // public T get(int index)

    public Node<T> getHead() {
        return head;
    }

    public Node<T> getTail() {
        return tail;
    }

    public int size() {
        return size;
    }
}