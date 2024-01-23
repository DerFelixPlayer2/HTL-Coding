package dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.factories;

import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.AmericanPizza;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Pizza;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Spaghetti;

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