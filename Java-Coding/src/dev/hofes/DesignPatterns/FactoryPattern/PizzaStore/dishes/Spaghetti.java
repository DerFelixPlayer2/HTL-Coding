package dev.hofes.DesignPatterns.FactoryPattern.PizzaStore.dishes;

public class Spaghetti implements Cloneable {
	
	private final String kind;

	public Spaghetti(String kind) {
		this.kind = kind;
	}

	public void cook() {
		System.out.println("cooking " + this);
	}

	@Override
	public String toString() {
		return "spaghetti (" + kind + " kind)";
	}

	/**
	 * override protected method defined in class Object to make it public
	 */
	@Override
	public Spaghetti clone() {
		try {
			return (Spaghetti) super.clone();
		} catch (CloneNotSupportedException ex) {
			throw new InternalError(ex.getMessage());
		}
	}
}