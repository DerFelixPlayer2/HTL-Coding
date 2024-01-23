package dev.hofes.FSST.design_patterns.factory.pizzastore.factories;

import dev.hofes.FSST.design_patterns.factory.pizzastore.dishes.AmericanPizza;
import dev.hofes.FSST.design_patterns.factory.pizzastore.dishes.Pizza;
import dev.hofes.FSST.design_patterns.factory.pizzastore.dishes.Spaghetti;

public class AmericanFactory extends AbstractFactory {

    @Override
    public Pizza orderPizza() {
        return new AmericanPizza();
    }

    @Override
    public Spaghetti orderSpaghetti() {
        return new Spaghetti("american");
    }
}