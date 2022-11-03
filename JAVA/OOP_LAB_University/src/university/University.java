package university;

/**
 * This class represents a university education system.
 * 
 * It manages students and courses.
 *
 */
public class University {

	/*
	 * Constructor
	 * @param name name of the university
	 */
	private String name;
	
	public University(String name){
		//TODO: to be implemented
		this.name=name;
	}
	
	/*
	 * Getter for the name of the university
	 * 
	 * @return name of university
	 */
	public String getName(){
		//TODO: to be implemented
		return name;
	}
	
	/**
	 * Defines the rector for the university
	 * 
	 * @param first
	 * @param last
	 */
	private String first, last;
	
	public void setRector(String first, String last){
		//TODO: to be implemented
		this.first = first;
		this.last = last;
	}
	
	/**
	 * Retrieves the rector of the university
	 * 
	 * @return name of the rector
	 */
	public String getRector(){
		//TODO: to be implemented
		return (first + " " + last);
	}
	
	/**
	 * Enrol a student in the university
	 * 
	 * @param first first name of the student
	 * @param last last name of the student
	 * 
	 * @return unique ID of the newly enrolled student
	 */
	public static final int MAX_ST = 1000;
	public static final int INIZIO_ST = 10000;
	
	protected int matricola = INIZIO_ST;
	protected Studente[] st = new Studente[MAX_ST];
	
	public int enroll(String first, String last){
		//TODO: to be implemented
		st[matricola-INIZIO_ST] = new Studente(first, last, matricola);
		
		return matricola++;
	}

	/**
	 * Retrieves the information for a given student
	 * 
	 * @param id the ID of the student
	 * 
	 * @return information about the student
	 */
	public String student(int id){
		//TODO: to be implemented
		
		return (st[id-INIZIO_ST].getDati());
	}
	
	/**
	 * Activates a new course with the given teacher
	 * 
	 * @param title title of the course
	 * @param teacher name of the teacher
	 * 
	 * @return the unique code assigned to the course
	 */
	public static final int MAX_INS = 50;
	public static final int INIZIO_INS = 10;
	
	private int codice = INIZIO_INS;
	protected Insegnamento[] ins = new Insegnamento[MAX_INS];
	
	public int activate(String title, String teacher){
		//TODO: to be implemented
		ins[codice-INIZIO_INS] = new Insegnamento(title, teacher, codice);
		
		return codice++;
	}
	
	/**
	 * Retrieve the information for a given course.
	 * 
	 * The course information is formatted as a string containing 
	 * code, title, and teacher separated by commas, 
	 * e.g., {@code "10,Object Oriented Programming,James Gosling"}.
	 * 
	 * @param code unique code of the course
	 * 
	 * @return information about the course
	 */
	public String course(int code){
		//TODO: to be implemented
		
		return (ins[code-INIZIO_INS].getDati());
	}
	
	/**
	 * Register a student to attend a course
	 * @param studentID id of the student
	 * @param courseCode id of the course
	 */
	public static final int MAX_ST_ISCRITTI = 100;
	public static final int MAX_INS_FREQUENTATI = 25;
	
	public void register(int studentID, int courseCode){
		//TODO: to be implemented
		st[studentID-INIZIO_ST].setIns(ins[courseCode-INIZIO_INS]);
		ins[courseCode-INIZIO_INS].setSt(st[studentID-INIZIO_ST]);
	}
	
	/**
	 * Retrieve a list of attendees
	 * 
	 * @param courseCode unique id of the course
	 * @return list of attendees separated by "\n"
	 */
	public String listAttendees(int courseCode){
		//TODO: to be implemented
		return ins[courseCode-INIZIO_INS].stampaStudentiDelCorso();
	}

	/**
	 * Retrieves the study plan for a student.
	 * 
	 * The study plan is reported as a string having
	 * one course per line (i.e. separated by '\n').
	 * The courses are formatted as describe in method {@link #course}
	 * 
	 * @param studentID id of the student
	 * 
	 * @return the list of courses the student is registered for
	 */
	public String studyPlan(int studentID){
		//TODO: to be implemented
		return st[studentID-INIZIO_ST].stampaCorsiPerStudente();
	}
}
