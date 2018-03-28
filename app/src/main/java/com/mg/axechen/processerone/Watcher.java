package com.mg.axechen.processerone;

/**
 * Created by AxeChen on 2018/3/27.
 */

public class Watcher {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public native void createWatcher(int userId);
}
