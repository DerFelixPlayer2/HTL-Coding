package dev.hofes.FSST.design_patterns.visitor.expression;

interface ExpressionVisitor<T> {
    T visit(Add add);

    T visit(Sub sub);

    T visit(Div div);

    T visit(Mul mul);

    T visit(Literal literal);
}