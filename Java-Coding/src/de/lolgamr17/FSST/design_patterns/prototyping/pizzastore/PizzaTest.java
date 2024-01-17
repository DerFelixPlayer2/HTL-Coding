package de.lolgamr17.FSST.design_patterns.prototyping.pizzastore;

import de.lolgamr17.FSST.design_patterns.prototyping.pizzastore.dishes.*;

import java.util.Scanner;

public class PizzaTest {
	public static void main(String[] args) {
		System.out.println("Welcome to the SSW pizza store (implementation using no design pattern)");
		System.out.println("Please select your preferred style:");
		System.out.println("1) Italian style");
		System.out.println("2) American style");
		System.out.println("3) Austrian style");

		try (Scanner s = new Scanner(System.in)) {
			PizzaStore pizzaStore = switch (s.next()) {
				case "1" -> new PizzaStore(new ItalianPizza(), new Spaghetti("italian"));
				case "2" -> new PizzaStore(new AmericanPizza(), new Spaghetti("american"));
				case "3" -> new PizzaStore(new AustrianPizza(), new Spaghetti("austrian"));
				default -> throw new IllegalStateException("Unexpected value: " + s.next());
			};

			Pizza pizza = pizzaStore.orderPizza();
			System.out.println("ready to eat " + pizza);
			System.out.println();

			Spaghetti spaghetti = pizzaStore.orderSpaghetti();
			System.out.println("ready to eat " + spaghetti);
			System.out.println();
		}
	}
}