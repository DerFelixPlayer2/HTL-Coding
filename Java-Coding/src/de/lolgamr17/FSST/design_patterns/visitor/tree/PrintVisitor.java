package de.lolgamr17.FSST.design_patterns.visitor.tree;

import de.lolgamr17.SEN.BinaryTrees.Node;

public class PrintVisitor<T extends Comparable<T>> implements TreeVisitor<T> {

    private final int order;
    private final StringBuilder printedTree;

    /**
     * @param order Order of the tree to print (0 = pre-order, 1 = in-order, 2 = post-order)
     */
    public PrintVisitor(int order) {
        if (order < 0 || order > 2) throw new IllegalArgumentException("Order must be 0, 1 or 2");
        this.printedTree = new StringBuilder();
        this.order = order;
    }

    @Override
    public void visit(Node<T> node) {
        switch(order) {
            case 0:
                this.printedTree.append(node.value);
                if (node.left != null) visit(node.left);
                if (node.right != null) visit(node.right);
                break;
            case 1:
                if (node.left != null) visit(node.left);
                this.printedTree.append(node.value);
                if (node.right != null) visit(node.right);
                break;
            case 2:
                if (node.left != null) visit(node.left);
                if (node.right != null) visit(node.right);
                this.printedTree.append(node.value);
                break;
            default:
                throw new IllegalArgumentException("Order must be 0, 1 or 2");
        }
    }

    public String getPrintedTree() {
        return this.printedTree.toString();
    }
}