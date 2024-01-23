package dev.hofes.Interfaces;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.Iterator;

public class List<T extends Comparable<T>> implements Iterable<T> {
    private Node<T> head = null;

    public void add(T obj) {
        Node<T> n = new Node<>(obj);
        if (head == null) {
            head = n;
        } else {
            Node<T> current = head, d = null;
            while (current.hasNext()) {
                if (current.compareTo(n.val) >= 0) {
                    if (d == null) {
                        n.next = current;
                        head = n;
                        return;
                    }

                    n.next = current;
                    d.next = n;
                    return;
                }
                d = current;
                current = current.next;
            }
            current.next = n;
        }
    }

    public void print() {
        for (Object c : this)
            System.out.println(c);
    }

    public @NotNull ListIterator iterator() {
        return new ListIterator();
    }

    public class ListIterator implements Iterator<T> {
        private Node<T> next;

        @Contract(pure = true)
        public ListIterator() {
            this.next = head;
        }

        public boolean hasNext() {
            return this.next != null;
        }

        public T next() {
            Node<T> n = this.next;
            this.next = this.next.next;
            return n.val;
        }

        public void remove() {
            this.next.remove();
        }
    }

    private static final class Node<T extends Comparable<T>> implements Comparable<T> {
        private final T val;
        private Node<T> next;

        public Node(T val, Node<T> next) {
            this.val = val;
            this.next = next;
        }

        public Node(T val) {
            this(val, null);
        }

        public void remove() {
            this.next = this.next.next;
        }

        public boolean hasNext() {
            return this.next != null;
        }

        @Contract(pure = true)
        @Override
        public @NotNull String toString() {
            return String.valueOf(val);
        }

        @Override
        public int compareTo(@NotNull T o) {
            return this.val.compareTo(o);
        }
    }
}