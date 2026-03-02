package com.medalyze;

public class Medication {

    private String medicationID;
    private String name;
    private String dosage;

    public Medication(String medicationID, String name, String dosage) {
        this.medicationID = medicationID;
        this.name = name;
        this.dosage = dosage;
    }

    public String getMedicationID() {
        return medicationID;
    }

    public String getName() {
        return name;
    }

    public String getDosage() {
        return dosage;
    }
}