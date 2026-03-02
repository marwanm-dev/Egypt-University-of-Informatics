package com.medalyze;

import java.time.LocalDate;
import java.time.LocalTime;

public class Main {

    public static void main(String[] args) {

        Patient patient = new Patient("P1", "Marwan", "0100000000");
        Doctor doctor = new Doctor("D1", "Cardiology");

        Appointment appointment = new Appointment(
                "A1",
                LocalDate.now(),
                LocalTime.now(),
                "Scheduled",
                patient,
                doctor
        );

        appointment.cancel();

        Report report = new Report("R1", "Billing");
        report.generate();

        System.out.println("System running successfully.");

        // Logger Singleton Test
        Logger logger1 = Logger.getInstance();
        Logger logger2 = Logger.getInstance();

        System.out.println("Same logger instance? " + (logger1 == logger2));
    }
}