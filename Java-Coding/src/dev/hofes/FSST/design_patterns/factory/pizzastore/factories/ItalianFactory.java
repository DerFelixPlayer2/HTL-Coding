package dev.hofes.FSST.design_patterns.factory.pizzastore.factories;

import dev.hofes.FSST.design_patterns.factory.pizzastore.dishes.ItalianPizza;
import dev.hofes.FSST.design_patterns.factory.pizzastore.dishes.Pizza;
import dev.hofes.FSST.design_patterns.factory.pizzastore.dishes.Spaghetti;

public class ItalianFactory extends AbstractFactory {
    @Override
    public Pizza orderPizza() {
        return new ItalianPizza();
    }

    @Override
    public Spaghetti orderSpaghetti() {
        return new Spaghetti("italian");
    }
}