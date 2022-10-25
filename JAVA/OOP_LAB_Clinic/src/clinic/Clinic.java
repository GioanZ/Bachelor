package clinic;

import static java.util.stream.Collectors.toList;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashMap;
import java.util.IntSummaryStatistics;
import java.util.List;
import java.util.Map;
import java.util.TreeSet;
import java.util.stream.Collectors;


/**
 * Represents a clinic with patients and doctors.
 * 
 */
public class Clinic {

	private Map<String,Patient>patients = new HashMap<>();
	private Map<Integer,Doctor>doctors = new HashMap<>();
	private Map<Patient,Doctor>dottoreDelPaziente = new HashMap<>();
	private Map<Doctor,List<Patient>>pazientiDelDottore= new HashMap<>();
	
	/**
	 * Add a new clinic patient.
	 * 
	 * @param first first name of the patient
	 * @param last last name of the patient
	 * @param ssn SSN number of the patient
	 */
	public void addPatient(String first, String last, String ssn) {
		// TODO Complete method
//		patients.put(ssn, new Patient(first, last, ssn));
		Patient p = new Patient(first, last, ssn);
		
		patients.put(ssn, p);
		dottoreDelPaziente.put(p, null);
	}


	/**
	 * Retrieves a patient information
	 * 
	 * @param ssn SSN of the patient
	 * @return the object representing the patient
	 * @throws NoSuchPatient in case of no patient with matching SSN
	 */
	public String getPatient(String ssn) throws NoSuchPatient {
		// TODO Complete method
		Patient p = patients.get(ssn);
		if(p == null) {
			NoSuchPatient e = new NoSuchPatient();
			
			throw e;
		}
		
		return p.toString();
	}

	/**
	 * Add a new doctor working at the clinic
	 * 
	 * @param first first name of the doctor
	 * @param last last name of the doctor
	 * @param ssn SSN number of the doctor
	 * @param docID unique ID of the doctor
	 * @param specialization doctor's specialization
	 */
	public void addDoctor(String first, String last, String ssn, int docID, String specialization) {
		// TODO Complete method
//		doctors.put(docID, new Doctor(first, last, ssn, docID, specialization));
		Doctor d = new Doctor(first, last, ssn, docID, specialization);
		
		doctors.put(docID, d);
		pazientiDelDottore.put(d, new ArrayList<Patient>());

		
		patients.put(ssn, new Patient(first, last, ssn));										//se aggiungo un doc devo aggiurngerlo anche come paiente
	}

	/**
	 * Retrieves information about a doctor
	 * 
	 * @param docID ID of the doctor
	 * @return object with information about the doctor
	 * @throws NoSuchDoctor in case no doctor exists with a matching ID
	 */
	public String getDoctor(int docID) throws NoSuchDoctor {
		// TODO Complete method
		Doctor d = doctors.get(docID);
		if(d == null) {
			NoSuchDoctor e = new NoSuchDoctor();
			
			throw e;
		}
		
		return d.toString();
	}
	
	/**
	 * Assign a given doctor to a patient
	 * 
	 * @param ssn SSN of the patient
	 * @param docID ID of the doctor
	 * @throws NoSuchPatient in case of not patient with matching SSN
	 * @throws NoSuchDoctor in case no doctor exists with a matching ID
	 */
	public void assignPatientToDoctor(String ssn, int docID) throws NoSuchPatient, NoSuchDoctor {
		// TODO Complete method
		Patient p = patients.get(ssn);
		Doctor d = doctors.get(docID), d2;
		
		if(p == null) {
			NoSuchPatient e = new NoSuchPatient();
			
			throw e;
		}
		if(d == null) {
			throw new NoSuchDoctor();
		}
		
		if(/*(d2 = p.getD()) != null ||*/ (d2 =dottoreDelPaziente.get(p)) != null) {
			//se il paziente ha già un dottore, togli al vecchio dottore il paziente
//			d2.cancellaP(p.getSSN());
			pazientiDelDottore.get(d2).remove(p);
		}
		
		dottoreDelPaziente.put(p, d);
		pazientiDelDottore.get(d).add(p);
		
//		p.assegnaD(d);
//		d.assegnaP(p);
	}
	
	/**
	 * Retrieves the id of the doctor assigned to a given patient.
	 * 
	 * @param ssn SSN of the patient
	 * @return id of the doctor
	 * @throws NoSuchPatient in case of not patient with matching SSN
	 * @throws NoSuchDoctor in case no doctor has been assigned to the patient
	 */
	public int getAssignedDoctor(String ssn) throws NoSuchPatient, NoSuchDoctor {
		// TODO Complete method
		Patient p = patients.get(ssn);
		Doctor d;
		
		if(p == null) {
			NoSuchPatient e = new NoSuchPatient();
			
			throw e;
		}
		
//		d = p.getD();																			//se doctor è vuoto allora d = null
//		if(d == null) {
//			NoSuchDoctor e = new NoSuchDoctor();
//			
//			throw e;
//		}
		d = dottoreDelPaziente.get(p);															//se doctor è vuoto allora d = null
		if(d == null) {
			NoSuchDoctor e = new NoSuchDoctor();
			
			throw e;
		}
		
		return d.getID();
	}
	
	/**
	 * Retrieves the patients assigned to a doctor
	 * 
	 * @param id ID of the doctor
	 * @return collection of patient SSNs
	 * @throws NoSuchDoctor in case the {@code id} does not match any doctor 
	 */
	public Collection<String> getAssignedPatients(int id) throws NoSuchDoctor {
		// TODO Complete method
		Doctor d = doctors.get(id);
		
		if(d == null) {
			NoSuchDoctor e = new NoSuchDoctor();
			
			throw e;
		}
		
//		pazientiDelDottore.get(d).stream().map(a -> a.getSSN()).collect(Collectors.toList()).stream().forEach(System.out::println);
		
		return pazientiDelDottore.get(d).stream()										//creo lista di stringhe SSN
				.map(a -> a.getSSN())													//uguale a fare .map(Person::getSSN)
	    		.collect(Collectors.toList());
	}


	/**
	 * Loads data about doctors and patients from the given stream.
	 * <p>
	 * The text file is organized by rows, each row contains info about
	 * either a patient or a doctor.</p>
	 * <p>
	 * Rows containing a patient's info begin with letter {@code "P"} followed by first name,
	 * last name, and SSN. Rows containing doctor's info start with letter {@code "M"},
	 * followed by badge ID, first name, last name, SSN, and specialization.<br>
	 * The elements on a line are separated by the {@code ';'} character possibly
	 * surrounded by spaces that should be ignored.</p>
	 * <p>
	 * In case of error in the data present on a given row, the method should be able
	 * to ignore the row and skip to the next one.<br>

	 * 
	 * @param readed linked to the file to be read
	 * @throws IOException in case of IO error
	 */
	public int loadData(Reader reader) throws IOException {
		// TODO Complete method
		int righeLette = 0;
		try (BufferedReader in = new BufferedReader(reader)) {
			List<String> file = in.lines().collect(toList()); 
			for(String riga: file) {
				List<String> pezzo = Arrays.asList(riga.split(";"));
//				for(String s:pezzo) {(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
//					s = s.trim();														//per togliere spazi a fine ed inizio della cella
//					System.out.println(s);
//				}
				if(pezzo.get(0).equals("M") == true && pezzo.size() == 6) {
					addDoctor(pezzo.get(2).trim(), pezzo.get(3).trim(),pezzo.get(4).trim(), Integer.parseInt(pezzo.get(1).trim()), pezzo.get(5).trim());
					righeLette++;
				}
				else if(pezzo.get(0).equals("P") && pezzo.size() == 4 ) {
					addPatient(pezzo.get(1).trim(), pezzo.get(2).trim(), pezzo.get(3).trim());
					righeLette++;
				}
			}
		}
		catch (IOException e) {
			throw e;
		}
		
		/* filter per avere list vuota, ordinare per cognome_nome dottore, collect di interi ID */
//		pazientiDelDottore.keySet().stream().
//			filter(d -> pazientiDelDottore.get(d).isEmpty() == false).
//			sorted(Comparator.comparing(Doctor::getLast_Name)).
//			map(d -> d.getID()).
//			collect(Collectors.toList()).
//			forEach(System.out::println);
		
		/* ordinare per numero decrescente di pazienti per dottore, fare collect di string di dottori */
//		pazientiDelDottore.keySet().stream().
//			sorted(Comparator
//					.comparing(d -> -pazientiDelDottore.get(d).size())).
//			map(d -> d.getName()).
//			collect(Collectors.toList()).
//			forEach(System.out::println);	
		
//		pazientiDelDottore.keySet().stream().
//			map(d -> String.format("%3d", pazientiDelDottore.get(d).size()) + " : " + d.getID() + " " + d.getLastname() + " " + d.getName()).
//			sorted((a,b) -> -a.compareTo(b)).
//			collect(Collectors.toList()).
//			forEach(System.out::println);
		
		return righeLette;
	}



	/**
	 * Loads data about doctors and patients from the given stream.
	 * <p>
	 * The text file is organized by rows, each row contains info about
	 * either a patient or a doctor.</p>
	 * <p>
	 * Rows containing a patient's info begin with letter {@code "P"} followed by first name,
	 * last name, and SSN. Rows containing doctor's info start with letter {@code "M"},
	 * followed by badge ID, first name, last name, SSN, and speciality.<br>
	 * The elements on a line are separated by the {@code ';'} character possibly
	 * surrounded by spaces that should be ignored.</p>
	 * <p>
	 * In case of error in the data present on a given row, the method calls the
	 * {@link ErrorListener#offending} method passing the line itself,
	 * ignores the row, and skip to the next one.<br>

	 * 
	 * @param reader reader linked to the file to be read
	 * @param listener listener used for wrong line notifications
	 * @throws IOException in case of IO error
	 */
	public int loadData(Reader reader, ErrorListener listener) throws IOException {
		// TODO Complete method
		int righeLette = 0;
		List<String> file;
		BufferedReader in;
		
		if(reader == null) {
			throw new IOException();
		}
		
		in = new BufferedReader(reader);
		
		file = in.lines().collect(toList()); 
		for(String riga: file) {
			List<String> pezzo = Arrays.asList(riga.split(";"));
			for(String s:pezzo) {
				s = s.trim();
			}
			if(pezzo.get(0).equals("M") == true && pezzo.size() == 6) {
				addDoctor(pezzo.get(2), pezzo.get(3),pezzo.get(4), Integer.parseInt(pezzo.get(1)), pezzo.get(5));
				righeLette++;
			}
			else if(pezzo.get(0).equals("P") && pezzo.size() == 4 ) {
				addPatient(pezzo.get(1), pezzo.get(2), pezzo.get(3));
				righeLette++;
			}
			else {
				listener.offending(riga);
			}
		}
		
		return righeLette;	
	}

		
	/**
	 * Retrieves the collection of doctors that have no patient at all.
	 * The doctors are returned sorted in alphabetical order
	 * 
	 * @return the collection of doctors' ids
	 */
	public Collection<Integer> idleDoctors(){
		// TODO Complete method

		return pazientiDelDottore.keySet().stream().
				filter(
						d -> 
							pazientiDelDottore.get(d).
									isEmpty() != false).
				sorted(Comparator.comparing(Doctor::getLast_Name)).
				map(d -> d.getID()).
				collect(Collectors.toList());
	}

	/**
	 * Retrieves the collection of doctors having a number of patients larger than the average.
	 * 
	 * @return  the collection of doctors' ids
	 */
	public Collection<Integer> busyDoctors(){
		// TODO Complete method
		double avg = pazientiDelDottore.values().stream().
											collect(
													Collectors.averagingDouble(a -> a.size()));
		//System.out.println(avg);
		
		return pazientiDelDottore.keySet().stream().
				filter(d -> pazientiDelDottore.get(d).size() > avg).
				map(Doctor::getID).
				collect(Collectors.toList());
	}

	/**
	 * Retrieves the information about doctors and relative number of assigned patients.
	 * <p>
	 * The method returns list of strings formatted as "{@code ### : ID SURNAME NAME}" where {@code ###}
	 * represent the number of patients (printed on three characters).
	 * <p>
	 * The list is sorted by decreasing number of patients.
	 * 
	 * @return the collection of strings with information about doctors and patients count
	 */
	public Collection<String> doctorsByNumPatients(){
		// TODO Complete method
		TreeSet<String> l = new TreeSet<String>();
		String s;
		
		for(Doctor d: pazientiDelDottore.keySet()) {
			s = String.format("%3d", pazientiDelDottore.get(d).size()) + " : " + d.getID() + " " + d.getLastname() + " " + d.getName();
			l.add(s);
		}
		
		l = (TreeSet<String>) l.descendingSet();										//invertire lista ordinata
		
		/* dovrebbe essere la stessa cosa */
//		pazientiDelDottore.keySet().stream().
//		map(d -> String.format("%3d", pazientiDelDottore.get(d).size()) + " : " + d.getID() + " " + d.getLastname() + " " + d.getName()).
//		sorted((a,b) -> -a.compareTo(b)).
//		collect(Collectors.toList()).
//		forEach(System.out::println);
		
		return l;
	}
	
	/**
	 * Retrieves the number of patients per (their doctor's)  speciality
	 * <p>
	 * The information is a collections of strings structured as {@code ### - SPECIALITY}
	 * where {@code SPECIALITY} is the name of the speciality and 
	 * {@code ###} is the number of patients cured by doctors with such speciality (printed on three characters).
	 * <p>
	 * The elements are sorted first by decreasing count and then by alphabetic speciality.
	 * 
	 * @return the collection of strings with speciality and patient count information.
	 */
	public Collection<String> countPatientsPerSpecialization(){
		// TODO Complete method
		TreeSet<String> l = new TreeSet<String>();
		String s;
		Map<String, IntSummaryStatistics> res = pazientiDelDottore.keySet().stream()
				.collect(
						Collectors.groupingBy(
								Doctor::getSpecial,//classifaier						//voglio raggruppare per Specialist
								Collectors
									.summarizingInt(d -> pazientiDelDottore.get(d)
											.size())
								)	
						);
		
		for(String special: res.keySet()) {
			s = String.format("%3d", res.get(special).getSum()) + " - " + special;
			l.add(s);
		}
		l = (TreeSet<String>) l.descendingSet();
		
		return l;
	}
	
}
