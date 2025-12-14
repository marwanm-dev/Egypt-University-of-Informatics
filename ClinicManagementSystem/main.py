import tkinter as tk
from tkinter import ttk, messagebox
import pyodbc


# ==============================
# DATABASE CONNECTION
# ==============================
def get_connection():
    try:
        conn = pyodbc.connect(
            "DRIVER={ODBC Driver 18 for SQL Server};"
            "SERVER=192.168.1.9,1433;"
            "DATABASE=ClinicManagementSystem;"
            "UID=marwan;"
            "PWD=Marwan123;"
            "Encrypt=no;"
            "TrustServerCertificate=yes;"
            "Connection Timeout=5;"
        )
        return conn
    except Exception as e:
        messagebox.showerror("Connection Error", str(e))
        return None


# ==============================
# MAIN APPLICATION
# ==============================
class ClinicApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Clinic Management System")
        self.geometry("1000x600")

        # Notebook (Tabs)
        self.notebook = ttk.Notebook(self)
        self.notebook.pack(expand=1, fill="both")

        # Tabs
        self.create_patient_tab()
        self.create_doctor_tab()
        self.create_appointment_tab()
        self.create_visit_tab()
        self.create_prescription_tab()
        self.create_report_tab()

    # ==============================
    # PATIENT TAB
    # ==============================
    def create_patient_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Patient")

        # Labels
        labels = [
            "PatientID (for update/delete)",
            "Name",
            "DOB (YYYY-MM-DD)",
            "Gender",
            "Phone",
            "Address",
            "NationalID",
        ]
        for i, text in enumerate(labels):
            tk.Label(tab, text=text).grid(row=i, column=0, padx=5, pady=2)

        # Entries
        self.patient_id_entry = tk.Entry(tab)
        self.name_entry = tk.Entry(tab)
        self.dob_entry = tk.Entry(tab)
        self.gender_entry = tk.Entry(tab)
        self.phone_entry = tk.Entry(tab)
        self.address_entry = tk.Entry(tab)
        self.nationalid_entry = tk.Entry(tab)

        entries = [
            self.patient_id_entry,
            self.name_entry,
            self.dob_entry,
            self.gender_entry,
            self.phone_entry,
            self.address_entry,
            self.nationalid_entry,
        ]

        for i, entry in enumerate(entries):
            entry.grid(row=i, column=1)

        # Buttons
        tk.Button(tab, text="Add Patient", command=self.insert_patient).grid(
            row=7, column=0, pady=5
        )
        tk.Button(tab, text="Update Phone", command=self.update_patient_phone).grid(
            row=7, column=1, pady=5
        )
        tk.Button(tab, text="Delete Patient (Soft)", command=self.delete_patient).grid(
            row=7, column=2, pady=5
        )
        tk.Button(tab, text="Show Patients", command=self.show_patients).grid(
            row=8, column=0, columnspan=3, pady=5
        )

        self.patient_text = tk.Text(tab, height=10)
        self.patient_text.grid(row=9, column=0, columnspan=3, sticky="nsew")

    def insert_patient(self):
        name = self.name_entry.get()
        dob = self.dob_entry.get()
        gender = self.gender_entry.get()
        phone = self.phone_entry.get()
        address = self.address_entry.get()
        nationalid = self.nationalid_entry.get()

        if not all([name, dob, gender, phone, address, nationalid]):
            messagebox.showwarning("Input Error", "All fields are required")
            return

        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    """
                    INSERT INTO Patient (Name,DOB,Gender,Phone,Address,NationalID) 
                    VALUES (?,?,?,?,?,?)""",
                    (name, dob, gender, phone, address, nationalid),
                )
                conn.commit()
                messagebox.showinfo("Success", "Patient added successfully")
                cursor.close()
                self.clear_patient_entries()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def update_patient_phone(self):
        pid = self.patient_id_entry.get()
        phone = self.phone_entry.get()
        if not pid or not phone:
            messagebox.showwarning("Input Error", "PatientID and Phone required")
            return
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    "UPDATE Patient SET Phone=? WHERE PatientID=?", (phone, pid)
                )
                conn.commit()
                messagebox.showinfo("Success", f"Patient {pid} phone updated")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def delete_patient(self):
        pid = self.patient_id_entry.get()
        if not pid:
            messagebox.showwarning("Input Error", "PatientID required")
            return
        if not messagebox.askyesno("Confirm Delete", f"Soft delete patient {pid}?"):
            return
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    "UPDATE Patient SET IsDeleted=1 WHERE PatientID=?", (pid,)
                )
                conn.commit()
                messagebox.showinfo("Deleted", f"Patient {pid} marked as deleted")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def show_patients(self):
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    "SELECT PatientID, Name, DOB, Gender, Phone, Address, NationalID FROM Patient WHERE IsDeleted=0"
                )
                rows = cursor.fetchall()
                self.patient_text.delete("1.0", tk.END)
                for r in rows:
                    self.patient_text.insert(tk.END, f"{r}\n")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def clear_patient_entries(self):
        self.patient_id_entry.delete(0, tk.END)
        self.name_entry.delete(0, tk.END)
        self.dob_entry.delete(0, tk.END)
        self.gender_entry.delete(0, tk.END)
        self.phone_entry.delete(0, tk.END)
        self.address_entry.delete(0, tk.END)
        self.nationalid_entry.delete(0, tk.END)

    # ==============================
    # DOCTOR TAB
    # ==============================
    def create_doctor_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Doctor")

        labels = ["DoctorID", "Name", "Specialization", "Phone", "DailyCapacity"]
        for i, text in enumerate(labels):
            tk.Label(tab, text=text).grid(row=i, column=0)

        self.doctor_id_entry = tk.Entry(tab)
        self.doctor_name_entry = tk.Entry(tab)
        self.doctor_spec_entry = tk.Entry(tab)
        self.doctor_phone_entry = tk.Entry(tab)
        self.doctor_capacity_entry = tk.Entry(tab)

        entries = [
            self.doctor_id_entry,
            self.doctor_name_entry,
            self.doctor_spec_entry,
            self.doctor_phone_entry,
            self.doctor_capacity_entry,
        ]
        for i, entry in enumerate(entries):
            entry.grid(row=i, column=1)

        tk.Button(tab, text="Add Doctor", command=self.insert_doctor).grid(
            row=5, column=0
        )
        tk.Button(
            tab, text="Update Doctor Phone", command=self.update_doctor_phone
        ).grid(row=5, column=1)
        tk.Button(tab, text="Delete Doctor", command=self.delete_doctor).grid(
            row=5, column=2
        )
        tk.Button(tab, text="Show Doctors", command=self.show_doctors).grid(
            row=6, column=0, columnspan=3
        )

        self.doctor_text = tk.Text(tab, height=10)
        self.doctor_text.grid(row=7, column=0, columnspan=3, sticky="nsew")

    def insert_doctor(self):
        name = self.doctor_name_entry.get()
        spec = self.doctor_spec_entry.get()
        phone = self.doctor_phone_entry.get()
        cap = self.doctor_capacity_entry.get()
        if not all([name, spec, phone, cap]):
            messagebox.showwarning("Input Error", "All fields required")
            return
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    "INSERT INTO Doctor (Name,Specialization,Phone,DailyCapacity) VALUES (?,?,?,?)",
                    (name, spec, phone, cap),
                )
                conn.commit()
                messagebox.showinfo("Success", "Doctor added")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def update_doctor_phone(self):
        did = self.doctor_id_entry.get()
        phone = self.doctor_phone_entry.get()
        if not did or not phone:
            messagebox.showwarning("Input Error", "DoctorID and Phone required")
            return
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    "UPDATE Doctor SET Phone=? WHERE DoctorID=?", (phone, did)
                )
                conn.commit()
                messagebox.showinfo("Success", "Doctor updated")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def delete_doctor(self):
        did = self.doctor_id_entry.get()
        if not did:
            messagebox.showwarning("Input Error", "DoctorID required")
            return
        if not messagebox.askyesno("Confirm Delete", f"Delete doctor {did}?"):
            return
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute("DELETE FROM Doctor WHERE DoctorID=?", (did,))
                conn.commit()
                messagebox.showinfo("Deleted", f"Doctor {did} deleted")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def show_doctors(self):
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute("SELECT * FROM Doctor")
                rows = cursor.fetchall()
                self.doctor_text.delete("1.0", tk.END)
                for r in rows:
                    self.doctor_text.insert(tk.END, f"{r}\n")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    # ==============================
    # APPOINTMENT TAB
    # ==============================
    def create_appointment_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Appointment")
        labels = [
            "AppointmentID",
            "PatientID",
            "DoctorID",
            "Date YYYY-MM-DD",
            "Time HH:MM",
            "Status",
        ]
        for i, text in enumerate(labels):
            tk.Label(tab, text=text).grid(row=i, column=0)
        self.appt_id_entry = tk.Entry(tab)
        self.appt_patient_entry = tk.Entry(tab)
        self.appt_doctor_entry = tk.Entry(tab)
        self.appt_date_entry = tk.Entry(tab)
        self.appt_time_entry = tk.Entry(tab)
        self.appt_status_entry = tk.Entry(tab)

        entries = [
            self.appt_id_entry,
            self.appt_patient_entry,
            self.appt_doctor_entry,
            self.appt_date_entry,
            self.appt_time_entry,
            self.appt_status_entry,
        ]
        for i, entry in enumerate(entries):
            entry.grid(row=i, column=1)

        tk.Button(tab, text="Add Appointment", command=self.insert_appointment).grid(
            row=6, column=0
        )
        tk.Button(
            tab, text="Update Status", command=self.update_appointment_status
        ).grid(row=6, column=1)
        tk.Button(tab, text="Delete Appointment", command=self.delete_appointment).grid(
            row=6, column=2
        )
        tk.Button(tab, text="Show Appointments", command=self.show_appointments).grid(
            row=7, column=0, columnspan=3
        )

        self.appt_text = tk.Text(tab, height=10)
        self.appt_text.grid(row=8, column=0, columnspan=3, sticky="nsew")

    def insert_appointment(self):
        pid = self.appt_patient_entry.get()
        did = self.appt_doctor_entry.get()
        date = self.appt_date_entry.get()
        time = self.appt_time_entry.get()
        status = self.appt_status_entry.get()
        if not all([pid, did, date, time, status]):
            messagebox.showwarning("Input Error", "All fields required")
            return
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    "INSERT INTO Appointment (PatientID,DoctorID,AppointmentDate,AppointmentTime,Status) VALUES (?,?,?,?,?)",
                    (pid, did, date, time, status),
                )
                conn.commit()
                messagebox.showinfo("Success", "Appointment added")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def update_appointment_status(self):
        aid = self.appt_id_entry.get()
        status = self.appt_status_entry.get()
        if not aid or not status:
            messagebox.showwarning("Input Error", "AppointmentID and Status required")
            return
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    "UPDATE Appointment SET Status=? WHERE AppointmentID=?",
                    (status, aid),
                )
                conn.commit()
                messagebox.showinfo("Success", "Appointment updated")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def delete_appointment(self):
        aid = self.appt_id_entry.get()
        if not aid:
            messagebox.showwarning("Input Error", "AppointmentID required")
            return
        if not messagebox.askyesno("Confirm Delete", f"Delete appointment {aid}?"):
            return
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute("DELETE FROM Appointment WHERE AppointmentID=?", (aid,))
                conn.commit()
                messagebox.showinfo("Deleted", f"Appointment {aid} deleted")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def show_appointments(self):
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute("""
                    SELECT A.AppointmentID,P.Name,D.Name,A.AppointmentDate,A.AppointmentTime,A.Status
                    FROM Appointment A
                    JOIN Patient P ON A.PatientID=P.PatientID
                    JOIN Doctor D ON A.DoctorID=D.DoctorID
                """)
                rows = cursor.fetchall()
                self.appt_text.delete("1.0", tk.END)
                for r in rows:
                    self.appt_text.insert(tk.END, f"{r}\n")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    # ==============================
    # VISIT TAB
    # ==============================
    def create_visit_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Visit")
        labels = [
            "VisitID",
            "AppointmentID",
            "Symptoms",
            "Diagnosis",
            "Notes",
            "FollowUpInstructions",
        ]
        for i, text in enumerate(labels):
            tk.Label(tab, text=text).grid(row=i, column=0)
        self.visit_id_entry = tk.Entry(tab)
        self.visit_appt_entry = tk.Entry(tab)
        self.visit_symptoms_entry = tk.Entry(tab)
        self.visit_diag_entry = tk.Entry(tab)
        self.visit_notes_entry = tk.Entry(tab)
        self.visit_followup_entry = tk.Entry(tab)
        entries = [
            self.visit_id_entry,
            self.visit_appt_entry,
            self.visit_symptoms_entry,
            self.visit_diag_entry,
            self.visit_notes_entry,
            self.visit_followup_entry,
        ]
        for i, entry in enumerate(entries):
            entry.grid(row=i, column=1)
        tk.Button(tab, text="Add Visit", command=self.insert_visit).grid(
            row=6, column=0
        )
        tk.Button(tab, text="Show Visits", command=self.show_visits).grid(
            row=6, column=1, columnspan=2
        )
        self.visit_text = tk.Text(tab, height=10)
        self.visit_text.grid(row=7, column=0, columnspan=3, sticky="nsew")

    def insert_visit(self):
        aid = self.visit_appt_entry.get()
        symptoms = self.visit_symptoms_entry.get()
        diag = self.visit_diag_entry.get()
        notes = self.visit_notes_entry.get()
        follow = self.visit_followup_entry.get()
        if not all([aid, symptoms, diag]):
            messagebox.showwarning(
                "Input Error", "AppointmentID, Symptoms, Diagnosis required"
            )
            return
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    "INSERT INTO Visit (AppointmentID,Symptoms,Diagnosis,Notes,FollowUpInstructions) VALUES (?,?,?,?,?)",
                    (aid, symptoms, diag, notes, follow),
                )
                conn.commit()
                messagebox.showinfo("Success", "Visit added")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def show_visits(self):
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute("""
                    SELECT V.VisitID,A.AppointmentID,P.Name,V.Symptoms,V.Diagnosis,V.Notes,V.FollowUpInstructions
                    FROM Visit V
                    JOIN Appointment A ON V.AppointmentID=A.AppointmentID
                    JOIN Patient P ON A.PatientID=P.PatientID
                """)
                rows = cursor.fetchall()
                self.visit_text.delete("1.0", tk.END)
                for r in rows:
                    self.visit_text.insert(tk.END, f"{r}\n")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    # ==============================
    # PRESCRIPTION TAB
    # ==============================
    def create_prescription_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Prescription")
        labels = ["PrescriptionID", "VisitID", "MedicationID", "Dosage", "Duration"]
        for i, text in enumerate(labels):
            tk.Label(tab, text=text).grid(row=i, column=0)
        self.pres_id_entry = tk.Entry(tab)
        self.pres_visit_entry = tk.Entry(tab)
        self.pres_med_entry = tk.Entry(tab)
        self.pres_dosage_entry = tk.Entry(tab)
        self.pres_duration_entry = tk.Entry(tab)
        entries = [
            self.pres_id_entry,
            self.pres_visit_entry,
            self.pres_med_entry,
            self.pres_dosage_entry,
            self.pres_duration_entry,
        ]
        for i, entry in enumerate(entries):
            entry.grid(row=i, column=1)
        tk.Button(
            tab, text="Add PrescriptionItem", command=self.insert_prescription_item
        ).grid(row=5, column=0)
        tk.Button(tab, text="Show Prescriptions", command=self.show_prescriptions).grid(
            row=5, column=1, columnspan=2
        )
        self.pres_text = tk.Text(tab, height=10)
        self.pres_text.grid(row=6, column=0, columnspan=3, sticky="nsew")

    def insert_prescription_item(self):
        visit = self.pres_visit_entry.get()
        med = self.pres_med_entry.get()
        dosage = self.pres_dosage_entry.get()
        duration = self.pres_duration_entry.get()
        if not all([visit, med, dosage, duration]):
            messagebox.showwarning("Input Error", "All fields required")
            return
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    "INSERT INTO PrescriptionItem (VisitID,MedicationID,Dosage,Duration) VALUES (?,?,?,?)",
                    (visit, med, dosage, duration),
                )
                conn.commit()
                messagebox.showinfo("Success", "PrescriptionItem added")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def show_prescriptions(self):
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute("""
                    SELECT PI.PrescriptionItemID,V.VisitID,P.Name,PI.MedicationID,PI.Dosage,PI.Duration
                    FROM PrescriptionItem PI
                    JOIN Visit V ON PI.VisitID=V.VisitID
                    JOIN Patient P ON V.AppointmentID = (SELECT AppointmentID FROM Appointment WHERE PatientID=P.PatientID)
                """)
                rows = cursor.fetchall()
                self.pres_text.delete("1.0", tk.END)
                for r in rows:
                    self.pres_text.insert(tk.END, f"{r}\n")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    # ==============================
    # REPORT TAB
    # ==============================
    def create_report_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Reports")
        tk.Button(
            tab,
            text="Appointments per Doctor",
            command=self.report_appointments_per_doctor,
        ).grid(row=0, column=0)
        tk.Button(tab, text="Total Revenue", command=self.report_total_revenue).grid(
            row=0, column=1
        )
        self.report_text = tk.Text(tab, height=20)
        self.report_text.grid(row=1, column=0, columnspan=2, sticky="nsew")

    def report_appointments_per_doctor(self):
        conn = get_connection()
        if conn:
            try:
                cursor = conn.cursor()
                cursor.execute("""
                    SELECT D.Name, COUNT(A.AppointmentID) AS TotalAppointments
                    FROM Doctor D
                    LEFT JOIN Appointment A ON D.DoctorID=A.DoctorID
                    GROUP BY D.Name
                """)
                rows = cursor.fetchall()
                self.report_text.delete("1.0", tk.END)
                for r in rows:
                    self.report_text.insert(tk.END, f"{r}\n")
                cursor.close()
            except Exception as e:
                messagebox.showerror("Error", str(e))
            finally:
                conn.close()

    def report_total_revenue(self):
        # Placeholder: add actual billing table later
        messagebox.showinfo("Info", "Total revenue report not yet implemented")


# ==============================
# RUN APP
# ==============================
if __name__ == "__main__":
    app = ClinicApp()
    app.mainloop()
