package dev.hofes.DesignPatterns.ProxyPattern.Internet;

class RealInternet implements Internet {
    @Override
    public void connectTo(String url) {
        System.out.println("Connection to: " + url);
    }
}