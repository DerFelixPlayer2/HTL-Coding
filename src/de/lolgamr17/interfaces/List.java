package de.lolgamr17.interfaces;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.Iterator;

public class List implements Iterable<List.Node> {
    private Node head = null;

    public void add(Comparable<Node> obj) {
        Node n = (Node) obj;
        if (head == null) {
            head = n;
        } else {
            Node current = head, d = null;
            do {
                if (current.compareTo(n) >= 0) {
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
        for (Node c : this)
            System.out.println(c);
    }

    public boolean contains(Comparable<Node> obj) {
        Node current = head;
        while (current != null) {
            if (current.compareTo((Node) obj) == 0) {
                return true;
            }
            current = current.next;
        }
        return false;
    }

    public void clear() {
        head = null;
    }

    public ListIterator iterator() {
        return new ListIterator(this);
    }

    private static class ListIterator implements Iterator<Node> {
        private Node current;

        @Contract(pure = true)
        public ListIterator(@NotNull List current) {
            this.current = current.head;
        }

        public boolean hasNext() {
            return this.current != null;
        }

        public Node next() {
            Node n = this.current;
            this.current = this.current.next;
            return n;
        }

        public void remove() {
            this.current.remove();
        }
    }

    public static final class Node implements Comparable<Node> {
        private final int val;
        private Node next;

        public Node(int val, Node next) {
            this.val = val;
            this.next = next;
        }

        public Node(int val) {
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
        public int compareTo(@NotNull List.Node o) {
            return this.val - o.val;
        }
    }
}