package de.lolgamr17.projects.AutoPartProject;

public class AutoPartProject {
    public static void main(String[] args) {
        AutoPartWarehouse warehouse = new AutoPartWarehouse("Autoparts.txt", "Orders.txt");
        warehouse.print();
        warehouse.processOrders();
        System.out.println("\n*** Warehouse after processing Orders ***");
        warehouse.print();
    }
}