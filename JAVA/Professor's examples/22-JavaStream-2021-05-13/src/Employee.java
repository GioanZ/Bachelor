
public class Employee implements Comparable<Employee>{
	private int id;
	private String fullname;
	private double salary;
	private int age;
	
	
	public Employee(int id, String fullname, double d, int age) {
		super();
		this.id = id;
		this.fullname = fullname;
		this.salary = d;
		this.age = age;
	}


	public int getId() {
		return id;
	}


	public void setId(int id) {
		this.id = id;
	}


	public String getFullname() {
		return fullname;
	}


	public void setFullname(String fullname) {
		this.fullname = fullname;
	}


	public double getSalary() {
		return salary;
	}


	public void setSalary(double salary) {
		this.salary = salary;
	}


	public int getAge() {
		return age;
	}


	public void setAge(int age) {
		this.age = age;
	}


	@Override
	public String toString() {
		return "Emplyee [id=" + id + ", fullname=" + fullname + ", salary=" + salary + ", age=" + age + "]";
	}


	@Override
	public int compareTo(Employee o) {
		// TODO Auto-generated method stub
		return this.getFullname().compareTo(o.getFullname());
	}
	
	
}
