package dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.factories;

import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.AustrianPizza;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Pizza;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Spaghetti;

public class AustrianFactory extends AbstractFactory {

    @Override
    public Pizza orderPizza() {
        return new AustrianPizza();
    }

    @Override
    public Spaghetti orderSpaghetti() {
        return new Spaghetti("austrian");
    }
}