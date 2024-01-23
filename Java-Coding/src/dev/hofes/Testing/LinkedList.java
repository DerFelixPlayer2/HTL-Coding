package dev.hofes.Testing;

public class LinkedList {
    Node head;

    public LinkedList() {
        this.head = null;
    }

    // Methode, um ein Element am Ende der Liste hinzuzufügen
    public void append(int data) {
        Node newNode = new Node(data);

        if (head == null) {
            head = newNode;
            return;
        }

        Node last = head;
        while (last.next != null) {
            last = last.next;
        }

        last.next = newNode;
    }

    // Methode, um die Liste zu durchlaufen und ihre Elemente auszugeben
    public void printList() {
        Node current = head;

        System.out.print("Linked List: ");
        while (current != null) {
            System.out.print(current.data + " ");
            current = current.next;
        }
        System.out.println();
    }

    private static class Node {
        int data;
        Node next;

        public Node(int data) {
            this.data = data;
            this.next = null;
        }
    }
}