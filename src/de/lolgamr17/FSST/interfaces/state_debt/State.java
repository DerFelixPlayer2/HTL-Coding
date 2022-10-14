package de.lolgamr17.FSST.interfaces.state_debt;

public record State(String name, double debt) {
    public String getName() {
        return name;
    }

    public double getDebt() {
        return debt;
    }
}