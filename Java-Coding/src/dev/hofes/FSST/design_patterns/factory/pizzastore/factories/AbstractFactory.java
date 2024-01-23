package dev.hofes.FSST.design_patterns.factory.pizzastore.factories;

import dev.hofes.FSST.design_patterns.factory.pizzastore.dishes.Pizza;
import dev.hofes.FSST.design_patterns.factory.pizzastore.dishes.Spaghetti;

public abstract class AbstractFactory {
    public abstract Pizza orderPizza();
    public abstract Spaghetti orderSpaghetti();
}