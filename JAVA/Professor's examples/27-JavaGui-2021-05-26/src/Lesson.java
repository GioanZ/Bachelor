
public class Lesson {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Contatore m = new Contatore();
		Vista v = new Vista(m);
		Controllore c = new Controllore(m,v);

	}

}
