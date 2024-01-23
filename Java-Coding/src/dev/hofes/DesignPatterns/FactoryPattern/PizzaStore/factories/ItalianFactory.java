package dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.factories;

import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.ItalianPizza;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Pizza;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Spaghetti;

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