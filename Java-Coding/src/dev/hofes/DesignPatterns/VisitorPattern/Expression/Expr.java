package dev.hofes.DesignPatterns.VisitorPattern.Expression;

interface Expr {
    <T> T accept(ExpressionVisitor<T> visitor);
}