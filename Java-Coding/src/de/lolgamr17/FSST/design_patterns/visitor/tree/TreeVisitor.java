package de.lolgamr17.FSST.design_patterns.visitor.tree;

import de.lolgamr17.SEN.BinaryTrees.Node;

public interface TreeVisitor<T extends Comparable<T>> {
    void visit(Node<T> node);
}