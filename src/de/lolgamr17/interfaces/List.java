package de.lolgamr17.interfaces;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.Iterator;

public class List implements Iterable<Integer> {
    private Node head = null;

    public void add(Comparable<Integer> obj) {
        Node n = new Node((Integer) obj);
        if (head == null) {
            head = n;
        } else {
            Node current = head, d = null;
            do {
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
            } while (current.hasNext());
            current.next = n;
        }
    }

    public void print() {
        for (Object c : this)
            System.out.println(c);
    }

    /*public boolean contains(Comparable<Integer> obj) {
        Node current = head;
        while (current != null) {
            if (current.val.compareTo(obj) == 0) {
                return true;
            }
            current = current.next;
        }
        return false;
    }

    public void clear() {
        head = null;
    }*/

    public ListIterator iterator() {
        return new ListIterator(this);
    }

    private class ListIterator implements Iterator<Integer> {
        private Node next;

        @Contract(pure = true)
        public ListIterator(@NotNull List list) {
            this.next = head;
        }

        public boolean hasNext() {
            return this.next != null;
        }

        public Integer next() {
            Node n = this.next;
            this.next = this.next.next;
            return n.val;
        }

        public void remove() {
            this.next.remove();
        }
    }

    private static final class Node implements Comparable<Integer> {
        private final Integer val;
        private Node next;

        public Node(Integer val, Node next) {
            this.val = val;
            this.next = next;
        }

        public Node(Integer val) {
            this(val, null);
        }

        public void remove() {
            this.next = this.next.next;
        }

        public int getVal() {
            return this.val;
        }

        public boolean hasNext() {
            return this.next != null;
        }

        @Contract(pure = true)
        @Override
        public @NotNull String toString() {
            return val + "";
        }

        @Override
        public int compareTo(@NotNull Integer o) {
            return this.val - o;
        }
    }
}