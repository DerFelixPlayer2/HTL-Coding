package de.lolgamr17.classes.abstraction.Arithmetic;

public class Addition extends BinaryOperation {
    Addition(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    public int evaluate(Bindings bindings) {
        return getLeft().evaluate(bindings) + getRight().evaluate(bindings);
    }

    @Override
    public Expression reduce() {
        Expression l = getLeft().reduce();
        Expression r = getRight().reduce();

        if (l instanceof Literal && ((Literal) l).getValue() == 0) {
            return r;
        } else if (r instanceof Literal && ((Literal) r).getValue() == 0) {
            return l;
        } else if (l instanceof Literal && r instanceof Literal) {
            return new Literal(((Literal) l).getValue() + ((Literal) r).getValue());
        }

        return new Addition(l, r);
    }

    @Override
    public String getOperator() {
        return "+";
    }
}