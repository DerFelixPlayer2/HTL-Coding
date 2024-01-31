package dev.hofes.ComplexDatastructures;

import org.jetbrains.annotations.NotNull;

public class ComparableTreeNode<T extends Comparable<T>> implements Comparable<ComparableTreeNode<T>> {
    public T value;
    public ComparableTreeNode<T> left;
    public ComparableTreeNode<T> right;

    public ComparableTreeNode(T value) {
        this.value = value;
    }

    @Override
    public int compareTo(@NotNull ComparableTreeNode<T> o) {
        return this.value.compareTo(o.value);
    }
}