package de.lolgamr17.FSST.interfaces.Top100;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.Iterator;
import java.util.Objects;

public class SortedList implements Iterable<Person> {
    private Node head;

    public SortedList() {
        head = null;
    }

    public void insert(@NotNull Person person) {
        if (head == null || head.person.getMoney() < person.getMoney()) {
            head = new Node(person, head);
            return;
        }

        Node curr = head;
        while (curr.next != null && curr.next.compareTo(person) > 0) {
            curr = curr.next;
        }

        if (curr.next == null) {
            curr.next = new Node(person, null);
        } else {
            curr.next = new Node(person, curr.next);
        }
    }

    public void insert(@NotNull String name, long money) {
        insert(new Person(name, money));
    }

    public int size() {
        Node current = head;
        int count = 0;
        while (current != null) {
            current = current.next;
            count++;
        }
        return count;
    }

    @NotNull
    public Person get(int index) {
        if (index < 0 || index >= size()) {
            throw new IndexOutOfBoundsException();
        }

        Node current = head;
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        return current.person;
    }

    @Contract(pure = true)
    public SortedList sublist(long min, long max) {
        SortedList sublist = new SortedList();
        for (Person person : this) {
            if (person.getMoney() >= min && person.getMoney() <= max) {
                sublist.insert(person);
            }
        }
        return sublist;
    }

    @NotNull
    @Override
    public Iterator<Person> iterator() {
        return new SortedListIterator();
    }

    @Override
    public String toString() {
        return head.toString();
    }

    private class SortedListIterator implements Iterator<Person> {
        private Node current;

        public SortedListIterator() {
            current = head;
        }

        @Override
        public boolean hasNext() {
            return current != null;
        }

        @Override
        public Person next() {
            Person result = current.person;
            current = current.next;
            return result;
        }
    }

    private static final class Node implements Comparable<Person> {
        public final Person person;
        public Node next;

        public Node(Person person, Node next) {
            this.person = person;
            this.next = next;
        }

        public void remove() {
            this.next = this.next.next;
        }

        public boolean hasNext() {
            return this.next != null;
        }

        @Override
        public int compareTo(@NotNull Person o) {
            return (int) Math.signum(this.person.getMoney() - o.getMoney());
        }

        @Override
        public @NotNull String toString() {
            return "{ " + person.getName() + ", " + person.getMoney() + " } -> " + next;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Node node = (Node) o;
            return Objects.equals(person.getMoney(), node.person.getMoney()) &&
                    Objects.equals(person.getName(), node.person.getName()) &&
                    Objects.equals(next, node.next);
        }

        @Override
        public int hashCode() {
            return Objects.hash(person, next);
        }
    }
}