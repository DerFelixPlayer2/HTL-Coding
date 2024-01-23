package dev.hofes.FSST.interfaces.state_debt;

import org.jetbrains.annotations.NotNull;

import java.util.Iterator;

public class StateList implements Iterable<State> {
    private Node head;

    public StateList() {
        head = null;
    }

    public static @NotNull StateList upTo(@NotNull StateList list, double debt) {
        StateList result = new StateList();
        for (State state : list) {
            if (state.getDebt() <= debt) {
                result.insert(state);
            }
        }
        return result;
    }

    public static @NotNull StateList greaterThan(@NotNull StateList list, double debt) {
        StateList result = new StateList();
        for (State state : list) {
            if (state.getDebt() > debt) {
                result.insert(state);
            }
        }
        return result;
    }

    public static @NotNull StateList between(@NotNull StateList states, double greater, double upTo) {
        StateList result = new StateList();
        for (State state : states) {
            if (state.getDebt() > greater && state.getDebt() <= upTo) {
                result.insert(state);
            }
        }
        return result;
    }

    public void insert(@NotNull State state) {
        if (head == null || head.state.getDebt() > state.getDebt()) {
            head = new Node(state, head);
            return;
        }

        Node curr = head;
        while (curr.next != null && curr.next.compareTo(state) < 0) {
            curr = curr.next;
        }

        if (curr.next == null) {
            curr.next = new Node(state, null);
        } else {
            curr.next = new Node(state, curr.next);
        }
    }

    public void insert(@NotNull String name, double debt) {
        insert(new State(name, debt));
    }

    public int size() {
        int count = 0;
        Node h = head;
        while (h != null) {
            count++;
            h = h.next;
        }
        return count;
    }

    @NotNull
    public State get(int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= size()) {
            throw new IndexOutOfBoundsException();
        }

        Node h = head;
        while (h != null && index > 0) {
            h = h.next;
            index--;
        }
        assert h != null;
        return h.state;
    }

    /**
     * @param name Name of the state
     * @return the debt of the state with the given name or -1 if the state is not in the list
     */
    public double getDebt(String name) {
        Node h = head;
        while (h != null && !h.state.getName().equals(name)) {
            h = h.next;
        }

        if (h == null) {
            return -1;
        }
        return h.state.getDebt();
    }

    @NotNull
    @Override
    public Iterator<State> iterator() {
        return new StateListIterator();
    }

    @Override
    public String toString() {
        return head.toString();
    }

    private class StateListIterator implements Iterator<State> {
        private Node next;

        public StateListIterator() {
            this.next = head;
        }

        @Override
        public boolean hasNext() {
            return this.next != null;
        }

        @Override
        public State next() {
            Node n = this.next;
            this.next = this.next.next;
            return n.state;
        }

        public void remove() {
            this.next.remove();
        }
    }

    private static final class Node implements Comparable<State> {
        public final State state;
        public Node next;

        public Node(State state, Node next) {
            this.state = state;
            this.next = next;
        }

        public void remove() {
            this.next = this.next.next;
        }

        public boolean hasNext() {
            return this.next != null;
        }

        @Override
        public int compareTo(@NotNull State o) {
            return (int) Math.signum(this.state.getDebt() - o.getDebt());
        }

        @Override
        public String toString() {
            return "{ " + state.getName() + ", " + state.getDebt() + " } -> " + next;
        }
    }
}