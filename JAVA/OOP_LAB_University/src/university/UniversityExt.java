package university;

import java.util.logging.Logger;

/**
 * This class is an extended version of the {@Link University} class.
 * 
 *
 */
public class UniversityExt extends University {
	
	private final static Logger logger = Logger.getLogger("University");
	
	public UniversityExt(String name) {
		super(name);
		// Example of logging
		logger.info("Creating extended university object");
	}
	
	@Override
	public int enroll(String first, String last){
		int val = super.enroll(first, last);
		logger.info("New student enrolled: " + val + ", " + first + " " + last);
		
		return val;
	}
	
	@Override
	public int activate(String title, String teacher){
		int val = super.activate(title, teacher);
		logger.info("New course activated: " + val + ", " + title + " " + teacher);
		
		return val;
	}
	
	@Override
	public void register(int studentID, int courseCode){
		super.register(studentID, courseCode);
		logger.info("Student " + studentID + " signed up for course " + courseCode);
	}

	/**
	 * records the grade (integer 0-30) for an exam can 
	 * 
	 * @param studentId the ID of the student
	 * @param courseID	course code 
	 * @param grade		grade ( 0-30)
	 */
	public void exam(int studentId, int courseID, int grade) {
		st[studentId-INIZIO_ST].setVoto(grade);
		ins[courseID-INIZIO_INS].setVoto(grade);
		logger.info("Student " + studentId + " took an exam in course " + courseID + " with grade " + grade);
	}

	/**
	 * Computes the average grade for a student and formats it as a string
	 * using the following format 
	 * 
	 * {@code "Student STUDENT_ID : AVG_GRADE"}. 
	 * 
	 * If the student has no exam recorded the method
	 * returns {@code "Student STUDENT_ID hasn't taken any exams"}.
	 * 
	 * @param studentId the ID of the student
	 * @return the average grade formatted as a string.
	 */
	public String studentAvg(int studentId) {
		float media = st[studentId-INIZIO_ST].getVotoAvg();
		
		if(media == 0) {
			return "Student " + studentId + "hasn't taken any exams";
		}
		
		return "Student " + studentId + " : " + media;
	}
	
	/**
	 * Computes the average grades of all students that took the exam for a given course.
	 * 
	 * The format is the following: 
	 * {@code "The average for the course COURSE_TITLE is: COURSE_AVG"}.
	 * 
	 * If no student took the exam for that course it returns {@code "No student has taken the exam in COURSE_TITLE"}.
	 * 
	 * @param courseId	course code 
	 * @return the course average formatted as a string
	 */
	public String courseAvg(int courseId) {
		float media = ins[courseId-INIZIO_INS].getVotoAvg();
		
		if(media == 0) {
			return "No student has taken the exam in " + ins[courseId-INIZIO_INS].getTitolo();
		}
		
		return "The average for the course " + ins[courseId-INIZIO_INS].getTitolo() + "is: " + media;
	}
	
	/**
	 * Retrieve information for the best students to award a price.
	 * 
	 * The students' score is evaluated as the average grade of the exams they've taken. 
	 * To take into account the number of exams taken and not only the grades, 
	 * a special bonus is assigned on top of the average grade: 
	 * the number of taken exams divided by the number of courses the student is enrolled to, multiplied by 10.
	 * The bonus is added to the exam average to compute the student score.
	 * 
	 * The method returns a string with the information about the three students with the highest score. 
	 * The students appear one per row (rows are terminated by a new-line character {@code '\n'}) 
	 * and each one of them is formatted as: {@code "STUDENT_FIRSTNAME STUDENT_LASTNAME : SCORE"}.
	 * 
	 * @return info of the best three students.
	 */
	public String topThreeStudents() {
		Studente[] stMigl = new Studente[3];
		Studente tmp,tmp2;
		StringBuffer sb = new StringBuffer();
		int i,z=0;
		
		for(i=0;i<matricola-INIZIO_ST;i++) {
			tmp = st[i];
			if(tmp.getNEsamiSost() <= 0) {
				continue;
			}
			for(int j=0;j<3;j++) {
				if (stMigl[j] == null) {
					stMigl[j] = tmp;
					z++;
					break;
				}
				if(tmp.getScore() > stMigl[j].getScore()) {
					for(int w=j;w<3;w++) {
						tmp2 = stMigl[w];						
						stMigl[w] = tmp;
						tmp = tmp2;
						if(tmp == null) {
							z++;
							break;
						}
					}
					
					break;
				}
			}
		}
		
		for(int j = 0; j<z; j++) {
			sb.append(stMigl[j].getFirst()).append(" ").append(stMigl[j].getLast()).append(": ").append(stMigl[j].getScore()).append("\n");
		}
		
		return sb.toString();
	}
}
