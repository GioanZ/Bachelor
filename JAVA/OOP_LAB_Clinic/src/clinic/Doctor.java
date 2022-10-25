package clinic;

public class Doctor {

	private String name;
	private String lastname;
	private String ssn;
	private int ID;
	private String specialization;
	
	
	public Doctor(String first, String last, String SSN, int docID, String specialization) {
		name = first;
		lastname = last;
		ssn = SSN;
		ID = docID;
		this.specialization = specialization;
	}
	
	public String getName() {
		
		return name;
	}
	
	public String getLastname() {
		
		return lastname;
	}
	
	public int getID() {
		
		return ID;
	}
	
	public String getSpecial() {
		
		return specialization;
	}
	
	public String getLast_Name() {
		
		return lastname + " " + name;
	}
	
	@Override 
	public String toString() {
		
		return lastname + " " + name + " (" + ssn + ") ["  + ID + "]: " + specialization;
	}
	
	public void assegnaP(Patient p) {
		
	}
	
	public void cancellaP(String ssn) {
		
	}
}
