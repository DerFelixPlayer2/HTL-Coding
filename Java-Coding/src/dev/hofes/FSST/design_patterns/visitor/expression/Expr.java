package dev.hofes.FSST.design_patterns.visitor.expression;

interface Expr {
    <T> T accept(ExpressionVisitor<T> visitor);
}