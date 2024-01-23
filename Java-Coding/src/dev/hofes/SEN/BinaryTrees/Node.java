package dev.hofes.SEN.BinaryTrees;

public class Node<T extends Comparable<T>> {
    public T value;
    public Node<T> left;
    public Node<T> right;

    public Node(T value) {
        this.value = value;
    }
}