package de.lolgamr17.FSST.design_patterns.prototyping.pizzastore.dishes;



public class ItalianPizza extends Pizza {
	
	@Override
	public void prepare() {
		System.out.println("preparing " + this);
		System.out.println("  (very special handling for an italian pizza)");
	}

	@Override
	public String toString() {
		return "italian pizza";
	}
}