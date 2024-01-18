package de.lolgamr17.FSST.design_patterns.proxy.internet;

class TestInternet {
    public static void main(String[] args) {
        Internet net = new RealInternet();
        externalCode(new SaferInternetProxy(net));
    }

    private static void externalCode(Internet net) {
        net.connectTo("www.test.com");
    }
}
