package de.lolgamr17.classes.abstraction.Arithmetic;

public class Multiplication extends BinaryOperation {
    public Multiplication(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    public int evaluate(Bindings binding) {
        return getLeft().evaluate(binding) * getRight().evaluate(binding);
    }

    @Override
    public Expression reduce() {
        Expression l = getLeft().reduce();
        Expression r = getRight().reduce();

        if (l instanceof Literal && ((Literal) l).getValue() == 0 ||
                r instanceof Literal && ((Literal) r).getValue() == 0) {
            return new Literal(0);
        } else if (l instanceof Literal && ((Literal) l).getValue() == 1) {
            return r;
        } else if (r instanceof Literal && ((Literal) r).getValue() == 1) {
            return l;
        } else if (l instanceof Literal && r instanceof Literal) {
            return new Literal(((Literal) l).getValue() * ((Literal) r).getValue());
        }

        return new Multiplication(l, r);
    }

    @Override
    public String getOperator() {
        return "*";
    }
}