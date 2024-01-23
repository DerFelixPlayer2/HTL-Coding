package dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.factories;

import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Pizza;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Spaghetti;

public abstract class AbstractFactory {
    public abstract Pizza orderPizza();
    public abstract Spaghetti orderSpaghetti();
}