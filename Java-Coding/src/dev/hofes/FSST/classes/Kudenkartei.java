package dev.hofes.FSST.classes;

import java.util.ArrayList;
import java.util.List;

public class Kudenkartei {
    private static class Customer {
        String name;
        long nr;
        Address privat;
        Address geschaeftlich;
        List<Order> Orders;

        Customer(String name, long nr, Address privat, Address geschaeftlich) {
            this.name = name;
            this.nr = nr;
            this.privat = privat;
            this.geschaeftlich = geschaeftlich;
            this.Orders = new ArrayList<>();
        }
    }

    private static class Address {
        String strasse;
        String hausnr;
        String plz;
        String ort;

        Address(String street, String hausnr, String plz, String ort) {
            this.strasse = street;
            this.hausnr = hausnr;
            this.plz = plz;
            this.ort = ort;
        }
    }

    private static class Order {
        int amt;
        int artikel;
        int preis;

        Order(int amt, int artikel, int preis) {
            this.amt = amt;
            this.artikel = artikel;
            this.preis = preis;
        }
    }

    public static void main(String[] args) {
        Customer k1 = new Customer("Max Mustermann", 12345, new Address("Musterstraße", "1", "12345", "Musterstadt"),
                new Address("Musterstraße", "1", "12345", "Musterstadt"));
        k1.Orders.add(new Order(1, 1, 100));
        k1.Orders.add(new Order(2, 2, 200));
        k1.Orders.add(new Order(3, 3, 300));
        k1.Orders.add(new Order(4, 4, 400));
        k1.Orders.add(new Order(5, 5, 500));
        k1.Orders.add(new Order(6, 6, 600));
        k1.Orders.add(new Order(7, 7, 700));
        k1.Orders.add(new Order(8, 8, 800));
        k1.Orders.add(new Order(9, 9, 900));
    }
}