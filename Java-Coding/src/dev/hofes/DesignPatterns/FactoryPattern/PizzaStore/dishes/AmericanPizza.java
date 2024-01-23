package dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes;

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