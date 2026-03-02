package com.medalyze;

public class Doctor {

    private String doctorID;
    private String specialty;

    public Doctor(String doctorID, String specialty) {
        this.doctorID = doctorID;
        this.specialty = specialty;
    }

    public String getDoctorID() {
        return doctorID;
    }

    public String getSpecialty() {
        return specialty;
    }
}