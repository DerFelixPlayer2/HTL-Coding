package de.lolgamr17.classes.abstraction.Arithmetic;

import org.jetbrains.annotations.NotNull;

public class Variable extends Expression {
    private final String name;

    Variable(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    @Override
    public int evaluate(@NotNull Bindings binding) throws RuntimeException {
        return binding.get(name);
    }

    @Override
    public Expression reduce() {
        return this;
    }

    @Override
    public String toString() {
        return name;
    }
}