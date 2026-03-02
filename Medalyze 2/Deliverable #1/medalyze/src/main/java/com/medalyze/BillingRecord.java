package com.medalyze;

public class BillingRecord {

    private String billingID;
    private double amount;
    private String insuranceStatus;

    public BillingRecord(String billingID, double amount, String insuranceStatus) {
        this.billingID = billingID;
        this.amount = amount;
        this.insuranceStatus = insuranceStatus;
    }

    public String getBillingID() {
        return billingID;
    }

    public double getAmount() {
        return amount;
    }

    public String getInsuranceStatus() {
        return insuranceStatus;
    }

    public void updateInsuranceStatus(String status) {
        this.insuranceStatus = status;
    }
}