package com.medalyze;

import java.time.LocalDate;
import java.time.LocalTime;

public class Appointment {

    private String appointmentID;
    private LocalDate date;
    private LocalTime time;
    private String status;
    private Patient patient;
    private Doctor doctor;

    public Appointment(String appointmentID, LocalDate date, LocalTime time,
                       String status, Patient patient, Doctor doctor) {
        this.appointmentID = appointmentID;
        this.date = date;
        this.time = time;
        this.status = status;
        this.patient = patient;
        this.doctor = doctor;
    }

    public String getAppointmentID() {
        return appointmentID;
    }

    public String getStatus() {
        return status;
    }

    public void cancel() {
        this.status = "Cancelled";
    }
}