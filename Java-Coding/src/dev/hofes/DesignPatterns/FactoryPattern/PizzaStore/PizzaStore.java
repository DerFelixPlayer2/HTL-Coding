package dev.hofes.DesignPatterns.FactoryPattern.PizzaStore;

import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Pizza;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Spaghetti;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.factories.AbstractFactory;
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