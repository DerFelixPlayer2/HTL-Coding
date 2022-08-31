package de.lolgamr17.interfaces.dictionary;

import de.lolgamr17.interfaces.state_debt.State;
import de.lolgamr17.interfaces.state_debt.StateList;
import org.jetbrains.annotations.NotNull;

import java.util.Iterator;

public class Dictionary implements Iterable<Entry> {
    private Node head;

    public void insert(@NotNull String english, @NotNull String german) {
        insert(new Entry(english, german));
    }

    public void insert(@NotNull Entry entry) {
        if (head == null || head.entry.getEnglish().compareTo(entry.getEnglish()) > 0) {
            head = new Node(entry, head);
            return;
        }

        Node curr = head;
        while (curr.next != null && curr.next.compareTo(entry) < 0) {
            curr = curr.next;
        }

        if (curr.next == null) {
            curr.next = new Node(entry, null);
        } else {
            curr.next = new Node(entry, curr.next);
        }
    }

    @NotNull
    public String lookupGermanWord(@NotNull String english) {
        Node curr = head;
        while (curr != null) {
            if (curr.entry.getEnglish().equals(english)) {
                return curr.entry.getGerman();
            }
            curr = curr.next;
        }
        return english;
    }

    @NotNull
    @Override
    public Iterator<Entry> iterator() {
        return new Iterator<>() {
            private Node next = head;

            public boolean hasNext() {
                return next != null;
            }

            @Override
            public Entry next() {
                Node n = this.next;
                this.next = this.next.next;
                return n.entry;
            }

            public void remove() {
                this.next.remove();
            }
        };
    }

    @Override
    public String toString() {
        return head.toString();
    }

    private static final class Node implements Comparable<Entry> {
        public final Entry entry;
        public Node next;

        public Node(Entry entry, Node next) {
            this.entry = entry;
            this.next = next;
        }

        public void remove() {
            this.next = this.next.next;
        }

        public boolean hasNext() {
            return this.next != null;
        }

        @Override
        public int compareTo(@NotNull Entry e) {
            return this.entry.getEnglish().compareTo(e.getEnglish());
        }

        @Override
        public String toString() {
            return "{ " + entry.getGerman() + " -> " + entry.getEnglish() + " } -> " + next;
        }
    }
}