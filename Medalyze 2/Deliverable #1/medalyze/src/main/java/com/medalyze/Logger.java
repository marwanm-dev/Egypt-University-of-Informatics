package com.medalyze;

public class Logger {

    private static Logger instance;

    // private constructor prevents instantiation
    private Logger() {
    }

    // lazy initialization
    public static Logger getInstance() {
        if (instance == null) {
            instance = new Logger();
        }
        return instance;
    }

    public void log(String message) {
        System.out.println("[LOG] " + message);
    }
}