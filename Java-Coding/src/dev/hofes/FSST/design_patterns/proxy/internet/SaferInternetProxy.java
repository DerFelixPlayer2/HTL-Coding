package dev.hofes.FSST.design_patterns.proxy.internet;

import java.util.ArrayList;
import java.util.List;

class SaferInternetProxy implements Internet {
    private final Internet net;
    private static final List<String> blockList = new ArrayList<>();

    static {
        blockList.add("www.gehnichthin.at");
        blockList.add("www.forbidden.com");
    }

    SaferInternetProxy(Internet net) {
        this.net = net;
    }

    @Override
    public void connectTo(String url) {
        if (blockList.contains(url)) {
            throw new IllegalStateException(url + " is blocked!");
        }
        net.connectTo(url);
    }
}