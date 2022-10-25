package clinic;

public class Patient {
	
	private String name;
	private String lastname;
	private String ssn;
	private Doctor doctor;
	
	public Patient(String first, String last, String SSN) {
		name = first;
		lastname = last;
		ssn = SSN;
	}
	
	public String getSSN() {	
		
		return ssn;
	}
	
	public Doctor getD() {																	//se doctor è vuoto allora return = null
		
		return doctor;
	}
	
	@Override 
	public String toString() {
		
		return lastname + " " + name + " (" + ssn + ")";
	}
	
	public void assegnaD(Doctor doc) {
		doctor = doc;
	}
}
