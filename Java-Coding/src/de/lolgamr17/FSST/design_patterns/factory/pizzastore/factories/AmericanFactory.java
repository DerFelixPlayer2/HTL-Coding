package de.lolgamr17.FSST.design_patterns.factory.pizzastore.factories;

import de.lolgamr17.FSST.design_patterns.factory.pizzastore.dishes.AmericanPizza;
import de.lolgamr17.FSST.design_patterns.factory.pizzastore.dishes.Pizza;
import de.lolgamr17.FSST.design_patterns.factory.pizzastore.dishes.Spaghetti;

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