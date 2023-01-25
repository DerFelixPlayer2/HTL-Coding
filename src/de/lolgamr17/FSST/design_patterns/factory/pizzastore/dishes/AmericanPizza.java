package de.lolgamr17.FSST.design_patterns.factory.pizzastore.dishes;

public class AmericanPizza extends Pizza {

    @Override
    public void prepare() {
        System.out.println("preparing " + this);
        System.out.println("  (very special handling for an american pizza)");
    }

    @Override
    public String toString() {
        return "american pizza";
    }
}