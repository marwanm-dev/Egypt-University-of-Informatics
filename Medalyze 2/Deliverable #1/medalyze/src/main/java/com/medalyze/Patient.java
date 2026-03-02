package com.medalyze;

public class Patient {

    private String patientID;
    private String name;
    private String contactInfo;

    public Patient(String patientID, String name, String contactInfo) {
        this.patientID = patientID;
        this.name = name;
        this.contactInfo = contactInfo;
    }

    public String getPatientID() {
        return patientID;
    }

    public String getName() {
        return name;
    }

    public String getContactInfo() {
        return contactInfo;
    }

    public void updateContactInfo(String newContactInfo) {
        this.contactInfo = newContactInfo;
    }
}