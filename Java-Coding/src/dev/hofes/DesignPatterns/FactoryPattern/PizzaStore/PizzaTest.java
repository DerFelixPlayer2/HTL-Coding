package dev.hofes.DesignPatterns.FactoryPattern.PizzaStore;

import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Pizza;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes.Spaghetti;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.factories.AmericanFactory;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.factories.AustrianFactory;
import dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.factories.ItalianFactory;

import java.util.Scanner;

public class PizzaTest {
    public static void main(String[] args) {
        System.out.println("Welcome to the SSW pizza store (implementation using no design pattern)");
        System.out.println("Please select your preferred style:");
        System.out.println("1) Italian style");
        System.out.println("2) American style");
        System.out.println("3) Austrian style");

        try (Scanner s = new Scanner(System.in)) {
            PizzaStore pizzaStore = new PizzaStore(switch (s.next()) {
                case "1" -> new ItalianFactory();
                case "2" -> new AmericanFactory();
                case "3" -> new AustrianFactory();
                default -> throw new IllegalStateException("Unexpected value: " + s.next());
            });

            Pizza pizza = pizzaStore.orderPizza();
            System.out.println("ready to eat " + pizza);
            System.out.println();

            Spaghetti spaghetti = pizzaStore.orderSpaghetti();
            System.out.println("ready to eat " + spaghetti);
            System.out.println();
        }
    }
}