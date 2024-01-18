package de.lolgamr17.FSST.design_patterns.factory.pizzastore.factories;

import de.lolgamr17.FSST.design_patterns.factory.pizzastore.dishes.AustrianPizza;
import de.lolgamr17.FSST.design_patterns.factory.pizzastore.dishes.Pizza;
import de.lolgamr17.FSST.design_patterns.factory.pizzastore.dishes.Spaghetti;

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