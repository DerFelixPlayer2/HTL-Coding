package dev.hofes.FSST.design_patterns.visitor.expression;

abstract class BinaryOperation implements Expr {
    private final Expr left;
    private final Expr right;

    BinaryOperation(Expr left, Expr right) {
        this.left = left;
        this.right = right;
    }

    public Expr getLeft() {
        return left;
    }

    public Expr getRight() {
        return right;
    }
}