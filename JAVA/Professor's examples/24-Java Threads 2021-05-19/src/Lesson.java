import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.stream.IntStream;

public class Lesson {
	
	
	static Runnable counting (String s, int num) {
		return () -> IntStream.range(0, num)
				.mapToObj(i->s+": "+i+" ")
				.forEach(System.out::println);
	}	

	public static void main(String[] args) {
		Counter t1 = new Counter ("Bob",100);
		Counter t2 = new Counter ("Alice",100);
		
		
		t1.start();
		t2.start();
		for (int i=0; i<100; i++) {
			System.out.println("Main "+i);
		}
		
		ExecutorService es = 
				Executors.newFixedThreadPool(3);
		
		es.submit(counting("Bob",100));
		es.submit(counting("Alice",10));
		es.submit(counting("Bob1",50));
		
		ExecutorService deepThought = 
				Executors.newWorkStealingPool();
		
		Callable<Long> lifeUniversEverything =
				() -> {
					Thread.sleep(300);
					return (long) 42;
				};
		
		Future<Long> answer = 
				deepThought.submit(lifeUniversEverything);
		
		Long theAnswer;
		try {
			theAnswer = answer.get();
			System.out.println(theAnswer);
		} catch (InterruptedException | ExecutionException e) {
			e.printStackTrace();
		}
	}

}
