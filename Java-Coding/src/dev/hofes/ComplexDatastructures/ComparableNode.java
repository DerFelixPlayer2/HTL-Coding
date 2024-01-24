package dev.hofes.ComplexDatastructures;

public class ComparableNode<T extends Comparable<T>> {
    public T value;
    public ComparableNode<T> left;
    public ComparableNode<T> right;

    public ComparableNode(T value) {
        this.value = value;
    }
}