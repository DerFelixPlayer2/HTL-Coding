package de.lolgamr17.FSST.design_patterns.proxy.internet;

class RealInternet implements Internet {
    @Override
    public void connectTo(String url) {
        System.out.println("Connection to: " + url);
    }
}