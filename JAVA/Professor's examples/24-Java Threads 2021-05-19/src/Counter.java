
public class Counter extends Thread{
	private int num;
	private String name;
	
	public Counter (String nn, int n) {
		name = nn;
		num = n;
	}

	public void run () {
		for (int i =0; i< num; i++) {
			System.out.println(name+ " "+i);
		}
	}
}
