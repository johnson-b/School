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
                break;
            default:
                Node<T> temp = tail;
                tail = new Node<>(data);
                tail.setPrevious(temp);
                temp.setNext(tail);
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
            Node<T> temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp.getNext();
            }
            Node<T> temp2 = new Node<>(data);
            temp2.setPrevious(temp.getPrevious());
            temp2.setNext(temp);
            temp.setPrevious(temp2);
            temp2.getPrevious().setNext(temp2);
            size++;
        }
        return true;
    }

    public boolean removeAtIndex(int index) {
        if (index < 0) {
            return false;
        } else if (index > size - 1) {
            return false;
        } else if(index == 0) {
            if(size == 1) {
                head = null;
                tail = null;
            } else {
                head = head.getNext();
                head.setPrevious(null);
            }
            size--;
        } else if(index == (size - 1)) {
            if(size == 1) {
                head = null;
                tail = null;
            } else {
                tail = tail.getPrevious();
                tail.setNext(null);
            }
            size--;
        } else {
            Node<T> temp = head;
            if(index == 1) {
                temp = temp.getNext();
            } else {
                for (int i = 0; i <= index; i++) {
                    temp = temp.getNext();
                }
            }
            temp.getPrevious().setNext(temp.getNext());
            temp.getNext().setPrevious(temp.getPrevious());
            size--;
        }
        return true;
    }

    public boolean removeValue(T data) {
        if(size == 0) {
            return false;
        } else if(head.getValue() == data) {
            removeAtIndex(0);
        } else {
            Node<T> temp = head;
            for(int i = 0; i < size - 1; i++) {
                temp = temp.getNext();
                if(temp.getValue() == data) {
                    removeAtIndex(i + 1);
                    break;
                }
            }
            return true;
        }
        return false;
    }

    public int indexOf(T data) {
        Node<T> temp = head;
        if(temp.getValue() == data) {
            return 0;
        }
        for(int i = 0; i < size - 1; i++) {
            temp = temp.getNext();
            if(temp.getValue() == data) {
                return i;
            }
        }
        return -1;
    }

    public T get(int index) {
        if(index == 0) {
            return head.getValue();
        } else if(index == size - 1) {
            return tail.getValue();
        } else if(index >= size) {
            throw new IndexOutOfBoundsException();
        } else if(index == 1) {
            return head.getNext().getValue();
        } else {
            Node<T> temp = head;
            for (int i = 0; i <= index; i++) {
                temp = temp.getNext();
            }
            return temp.getValue();
        }
    }

    public void print() {
        Node<T> temp = head;
        for(int i = 0; i < size; i++) {
            System.out.println(temp.getValue());
            temp = temp.getNext();
        }
    }

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