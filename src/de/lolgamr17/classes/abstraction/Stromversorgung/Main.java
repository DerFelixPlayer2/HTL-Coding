package de.lolgamr17.classes.abstraction.Stromversorgung;

public class Main {
    public static void main(String[] args) {
        Cable cable = new Cable("Cable");

        PowerStrip ps1 = new PowerStrip("ps1", 5);
        PowerStrip ps2 = new PowerStrip("ps2", 4);

        Computer c11 = new Computer("c11", 1000);
        Computer c12 = new Computer("c12", 1000);
        Computer c21 = new Computer("c21", 1000);
        Computer c22 = new Computer("c22", 1000);

        Lamp l11 = new Lamp("l11", 200);
        Lamp l12 = new Lamp("l12", 200);
        Lamp l21 = new Lamp("l21", 200);
        Lamp l22 = new Lamp("l22", 200);

        cable.plug(ps1);

        ps1.plug(c11);
        ps1.plug(l11);
        ps1.plug(c12);
        ps1.plug(l12);
        ps1.plug(ps2);

        ps2.plug(c21);
        ps2.plug(l21);
        ps2.plug(c22);
        ps2.plug(l22);

        System.out.println(cable);
        System.out.println(cable.calcConsumption() + " Watts");
    }
}