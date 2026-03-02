package com.medalyze;

public class Prescription {

    private String prescriptionID;
    private String status;
    private Patient patient;

    public Prescription(String prescriptionID, String status, Patient patient) {
        this.prescriptionID = prescriptionID;
        this.status = status;
        this.patient = patient;
    }

    public String getPrescriptionID() {
        return prescriptionID;
    }

    public String getStatus() {
        return status;
    }

    public void updateStatus(String newStatus) {
        this.status = newStatus;
    }
}