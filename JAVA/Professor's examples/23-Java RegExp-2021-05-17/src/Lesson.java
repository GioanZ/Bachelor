import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Lesson {
	
	/* Controllare se una stringa contiene una sequenza di 10 caratteri numerici*/

	public static boolean hasTenDigits(String s) {
		int noDigits = 0;
		for (int i=0; i<s.length();i++) {
			char c = s.charAt(i);
			if (Character.isDigit(c)) {
				noDigits++;
				if (noDigits == 10) return true;
			} else {
				noDigits = 0;
			}
		}
		return false;
	}
	
	/* Controllare se una stringa contiene una sequenza di 10
	 * caratteri consecutivi usando le espressioni regolari
	 */
	
	public static boolean hasTenDigitsRegEx(String s) {
			//return s.matches("(.*)([0-9]{10})(.*)");											// il "." serve per dire che ci può essere qualsiasi cosa al posto del punto
			return s.matches("(.*)(\\d{10})(.*)");												// il \d serve per avere solo numeri, {10} per dire che ci devono essere almeno 10 di \d
	}
	
	
	public static boolean regexGroups (String regex, String s) {
		//Genero un oggetto pattern in cui compilo la regexp
		Pattern p = Pattern.compile(regex);														//capisce quanti gruppi ci sono
		Matcher m = p.matcher(s);
		if (m.find()) {
			for (int i = 0; i <= m.groupCount(); i++) {
				System.out.println("Group"+i+": "+m.group(i));
			}
			return true;
		} else {
			return false;
		}
		
	}

	public static void regexAllGroups (String regex, String s) {
		//Genero un oggetto pattern in cui compilo la regexp
		Pattern p = Pattern.compile(regex);
		Matcher m = p.matcher(s);
		while (m.find()) {
				System.out.println("Match:");
				for (int i = 0; i <= m.groupCount(); i++) {
					System.out.println("Group"+i+": "+m.group(i));
			}
		}
		
	}
	
	
	
	
	
	
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		if (hasTenDigits("afsd9876543210jjjj")) {
			System.out.println("La stringa contiene dieci numeri consecutivi");
		} else {
			System.out.println("La stringa non contiene dieci numeri consecutivi");
		}
		
		if (hasTenDigitsRegEx("ad/ld933876543210jjjj")) {
			System.out.println("La stringa contiene dieci numeri consecutivi");
		} else {
			System.out.println("La stringa non contiene dieci numeri consecutivi");
		}
		
		if (regexGroups("(.*)([0-9]{10})(.*)","afsd987657743210jjjj")) {							//ci sono 4 gruppi, le parentesi messe insieme, prima, seconda e terza parentesi
			System.out.println ("La stringa contiene 10 cifre");
		} else {
			System.out.println ("La stringa non contiene 10 cifre");
		}
		
		
		regexAllGroups("(<[^>]+>)|(&\\w+;)|([^<&]+)","<body>prova di &nbsp; <b>testo</b> &nbsp; html</body>");
		
		System.out.println("\n\nOra do dei nomi ai gruppi:\n"
				+ "gruppo \"<[^>]+>\" ELEMENT\n"
				+ "gruppo \"&\\w+;\" ENTITY\n"
				+ "gruppo \"[^<&]+\" Text"); 
		regexAllGroups("(?<ELEMENT><[^>]+>)|(?<ENTITY>&\\w+;)|(?<Text>[^<&]+)","<body>prova di &nbsp; <b>testo</b> &nbsp; html</body>");
		
		System.out.println("\nHo questa \"aa09945\", uso \"(?<=aa)([0-9]+)\"\n"
				+ "(?<=aa) vuol dire che devo trovare una parola che inizia con \"aa\" ma non viene considerato nel matched\n"
				+ "([0-9]+) ci devono essere almeno una cifra\n"
				+ "(?<!aa) non ci deve essere all'inizio\n"
				+ "(?=aa) deve essere alla fine\n"
				+ "(?!aa) non ci deve essere alla fine");
		regexAllGroups("(?<=aa)([0-9]+)","aa09945q");
		regexAllGroups("(?<=aa)([0-9]+)","ab09945q");
		System.out.println("\nSe lo tolgo ?<= ottengo:");
		regexAllGroups("(aa)([0-9]+)","aa09945q");
		
		
		/* Input da linea di comando in Java */		
		Scanner scanner = new Scanner(System.in);
		
		System.out.println("Inserisci un valore da tastiera:");
		String s = scanner.nextLine();
		System.out.println ("Il valore inserito è:"+s);
		String s1 = scanner.nextLine();
		System.out.println ("Il secondo valore inserito è:"+s1);	
		scanner.close();
		
	}

}
