import java.util.ArrayList;
import java.util.Comparator;
import java.util.DoubleSummaryStatistics;
import java.util.IntSummaryStatistics;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.TreeMap;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Lesson {

	public static void main(String[] args) {

		Employee[] arrayOfEmps = {
			    new Employee(1, "Jeff Bezos", 10000000.0, 50), 
			    new Employee(2, "Bill Gates", 20000000.0, 45), 
			    new Employee(3, "Mark Zuckerberg", 30000000.0, 45),
			    new Employee(4, "Will Smith", 30000000.0, 49),
			    new Employee(5, "Tom Hanks", 41000000.0, 68),
			    new Employee(6, "Jack Nicholson", 34000400.0, 78),
			    new Employee(7, "Leonardo Di Caprio", 32100000.0, 48),
			    new Employee(8, "Harrison Ford", 12500000.0, 61),
			    new Employee(9, "Tom Cruise", 20000000.0, 57),
			    new Employee(10, "Jonny Dep", 40003000.0, 45),
			    new Employee(11, "Denzel Washington", 10004000.0, 60),
			    new Employee(12, "Robert Downery Jr.", 30040000.0, 55),
			    new Employee(13, "Robert De Niro", 20000000.0, 75),
			    new Employee(14, "Al Pacino", 10045000.0, 71),
			    new Employee(15, "Anthony Hopkins", 30500000.0, 70)
			};
		
		
		
		//Incrementare del 10% il salario di tutti gli impiegati più vecchi di 60 anni
		Stream.of(arrayOfEmps)
			.forEach(e -> {
				if (e.getAge() > 60) {
					e.setSalary(e.getSalary()*1.1);
				}
			});
		
		Stream.of(arrayOfEmps).forEach(System.out::println);
		
		//stesso di prima ma in un altro modo
		Stream.of(arrayOfEmps).
			filter(p -> p.getAge()>60)
			.forEach(e -> {e.setSalary(e.getSalary()*1.1);} );
		
		Stream.of(arrayOfEmps).forEach(System.out::println);
		
		//stesso di prima ma in un altro modo
		Stream.of(arrayOfEmps).
			peek(e -> {																			//a differenza del primo qua non uso forEach
				if (e.getAge()> 60) {															//perché dopo un forEach non posso mettere altro
					e.setSalary(e.getSalary()*1.1);												//quindi peek == forEach, però con peek
				}																				//poi posso mettere forEach èperché peek non è finale
			}).
			forEach (System.out::println);
		
		
		//Creare una stringa con l'elenco dei nomi degli impiegati in ordine alfabetico decrescente uno per riga con una virgola finale
		String listofnames = Stream.of(arrayOfEmps).
				//map(e -> e.getFullname())
				map(Employee::getFullname)
				.sorted((a,b) -> -a.compareTo(b))
				//.reduce("", (a,b) -> {
				//	if (a.equals("")) {
				//		return b;
				//	} else {
				//		return a + ", \n" + b;
				//	}
				//});
				.reduce("", (a,b) -> a+b+",\n");
		
	    System.out.println(listofnames);
	    System.out.println("BRORBRBORBOBOR");
	    
	    String listofnames1 = Stream.of(arrayOfEmps).											//così risolvo il problema delle virgole
			map(Employee::getFullname)
			.sorted((a,b) -> -a.compareTo(b))
			.collect(Collectors.joining(",\n"));

		System.out.println(listofnames1);
		System.out.println("BRORBRBORBOBOR");
	    
		//Calcolare lo stipendio totale di tutti gli impiegati
	    double salary = Stream.of(arrayOfEmps).parallel()
	    		.map(e -> e.getSalary())
	    		.reduce(0.0, (a,b) -> a+b);
	    
	    System.out.println("Stipendio totale: "+salary);
	    
		
		//Calcolare l'età media, minima e massima di tutti gli impiegati
	    double avgage = Stream.of(arrayOfEmps)
	    		.map(Employee::getAge)
	    		.collect(Collectors.averagingDouble(a -> a));
	    
	    Optional<Integer> minage = Stream.of(arrayOfEmps)
		    .map(Employee::getAge)
		    .collect(Collectors.minBy((a,b) -> a-b));
	    
	    Optional<Integer> maxage = Stream.of(arrayOfEmps)
		    .map(Employee::getAge)
		    .collect(Collectors.maxBy((a,b) -> a-b));

	    System.out.println("EtÃ  media:"+avgage + 
	    		" EtÃ  minima: " + minage.get() +
	    		" EtÃ  massima: " + maxage.get());
	    
		
		//Per le statistiche
	    IntSummaryStatistics stats= Stream.of(arrayOfEmps).
		    map(Employee::getAge).
		    collect(Collectors.summarizingInt(a -> a));
	    
	    System.out.println(stats);
	    
	    
	    //Ottenere una lista che contenga gli id degli impiegati
	    List<Integer> ids = Stream.of(arrayOfEmps)
	    		.map(a -> a.getId())
	    		.collect(Collectors.toList());
	    ids.stream().forEach(System.out::println);
	    
	    
		//Ottenere un set di nomi
		Set<String> setNames = Stream.of(arrayOfEmps) 
				.map(a -> a.getFullname())
				.collect(Collectors.toSet());
	
		setNames.stream().forEach(System.out::println);
		
		
		//Ottenere un arraylist di nomi
		ArrayList<String> setNames1 = Stream.of(arrayOfEmps)
				.map(Employee::getFullname)
				.collect(
						Collectors.toCollection(ArrayList::new)
						);
		
		
		//Partizionare in base all'età  distinguendo quelli più vecchi di 60 anni dagli altri
		Map<Boolean, List<Employee>> isold = Stream.of(arrayOfEmps)
				.collect(
						Collectors.partitioningBy(e -> e.getAge() > 60)
				);
	    
		for (Boolean b: isold.keySet()) {
			System.out.println("Key: " + b);
			isold.get(b).stream().forEach(System.out::println);
		}
		
		
	    //Ottenere una mappa di impiegati raggruppati per il primo carattere del nome
		Map<Character,List<Employee>> groupByFirstChar =
				Stream.of(arrayOfEmps)
				.collect(
						Collectors.groupingBy(
								e -> e.getFullname().charAt(0))
						);
		for (Character key: groupByFirstChar.keySet()) {
			System.out.println("Key: " + key);
			groupByFirstChar.get(key).stream().forEach(System.out::println);
		}
		
		
		//Ordinare la mappa per primo carattere inverso
		Map<Character,List<Employee>> groutByFirstCharInvOrd =
				Stream.of(arrayOfEmps)
				.collect(
						Collectors.groupingBy(										//prendo elementi e li raggruppo
								e -> e.getFullname().charAt(0),						//decido la chiave per formare i gruppi
								() -> new TreeMap<>(Comparator.reverseOrder()),		//il risultato della groupBy è una mappa e dove voglio metterlo? decido come deve essere salvata
								Collectors.toList()									//cosa metto nella mappa? come collezionare gli impiegati nella lista di impiegati (credo che detto meglio: cosa devo mettere dentro value?)
						)
						
				);	
		
		for (Character key: groutByFirstCharInvOrd.keySet()) {
			System.out.println("Key: " + key);
			groutByFirstCharInvOrd.get(key).stream().forEach(System.out::println);
		}
		
		
	    //Collezionare gli id ragruppati per prima lettera del nome
		Map<Character,List<Integer>> idByFirstChar =
				Stream.of(arrayOfEmps)
				.collect(
						Collectors.groupingBy(
								e -> e.getFullname().charAt(0),
								Collectors.mapping(
										Employee::getId, 
										Collectors.toList())
								)
				);
				
		
		//Cosa metto in question?
	    String question = Stream.of(arrayOfEmps).collect(
		           Collectors.collectingAndThen(																//fai un operazione aggiuntiva a quel che ottengo
		               Collectors.maxBy(Comparator.comparing(Employee::getSalary)),								//trova 1 employ
		                (Optional<Employee> emp)-> emp.isPresent() ? emp.get().getFullname() : "none") );		//dopo averlo trovato fai questo
	}
	

	
}
