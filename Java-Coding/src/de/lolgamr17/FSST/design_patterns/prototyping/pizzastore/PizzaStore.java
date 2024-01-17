package de.lolgamr17.FSST.design_patterns.prototyping.pizzastore;

import de.lolgamr17.FSST.design_patterns.prototyping.pizzastore.dishes.AmericanPizza;
import de.lolgamr17.FSST.design_patterns.prototyping.pizzastore.dishes.ItalianPizza;
import de.lolgamr17.FSST.design_patterns.prototyping.pizzastore.dishes.Pizza;
import de.lolgamr17.FSST.design_patterns.prototyping.pizzastore.dishes.Spaghetti;

/**
 * Implementation of a pizza store using no design pattern
 */
public class PizzaStore {

    private final Pizza pizzaPrototype;
    private final Spaghetti spaghettiPrototype;

    public PizzaStore(Pizza p, Spaghetti s) {
        this.pizzaPrototype = p;
        this.spaghettiPrototype = s;
    }

    public Pizza orderPizza() {
        Pizza pizza = this.pizzaPrototype.clone();

        pizza.prepare();
        pizza.bake();
        pizza.box();
        return pizza;
    }

    public Spaghetti orderSpaghetti() {
        Spaghetti spaghetti = spaghettiPrototype.clone();

        spaghetti.cook();
        return spaghetti;
    }
}