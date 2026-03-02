package com.medalyze;

public class Report {

    private String reportID;
    private String reportType;

    public Report(String reportID, String reportType) {
        this.reportID = reportID;
        this.reportType = reportType;
    }

    public String getReportID() {
        return reportID;
    }

    public String getReportType() {
        return reportType;
    }

    public void generate() {
        System.out.println("Generating " + reportType + " report...");
    }
}