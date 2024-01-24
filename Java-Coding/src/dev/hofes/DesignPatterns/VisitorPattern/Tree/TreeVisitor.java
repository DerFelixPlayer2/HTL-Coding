package dev.hofes.DesignPatterns.VisitorPattern.Tree;

import dev.hofes.ComplexDatastructures.ComparableNode;

public interface TreeVisitor<T extends Comparable<T>> {
    void visit(ComparableNode<T> node);
}