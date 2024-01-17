package de.lolgamr17.FSST.design_patterns.factory.pizzastore.factories;

import de.lolgamr17.FSST.design_patterns.factory.pizzastore.dishes.Pizza;
import de.lolgamr17.FSST.design_patterns.factory.pizzastore.dishes.Spaghetti;

public abstract class AbstractFactory {
    public abstract Pizza orderPizza();
    public abstract Spaghetti orderSpaghetti();
}