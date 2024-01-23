package dev.hofes.FSST.design_patterns.factory.pizzastore;

import dev.hofes.FSST.design_patterns.factory.pizzastore.dishes.Pizza;
import dev.hofes.FSST.design_patterns.factory.pizzastore.dishes.Spaghetti;
import dev.hofes.FSST.design_patterns.factory.pizzastore.factories.AbstractFactory;
import org.jetbrains.annotations.NotNull;

public record PizzaStore(AbstractFactory factory) {
    public @NotNull Pizza orderPizza() {
        Pizza pizza = factory.orderPizza();

        pizza.prepare();
        pizza.bake();
        pizza.box();
        return pizza;
    }

    public @NotNull Spaghetti orderSpaghetti() {
        Spaghetti spaghetti = factory.orderSpaghetti();

        spaghetti.cook();
        return spaghetti;
    }
}