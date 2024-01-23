package dev.hofes.FSST.design_patterns.visitor.tree;

import dev.hofes.SEN.BinaryTrees.Node;

public interface TreeVisitor<T extends Comparable<T>> {
    void visit(Node<T> node);
}