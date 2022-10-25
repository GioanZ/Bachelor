package mountainhuts;

public class Value {
	private String minValue;
	private String maxValue;
	
	public Value(String range){
		minValue = range.split("-")[0];
		maxValue = range.split("-")[1];
	}
	
	public String cercaIntervallo(Integer alt){
		if(Integer.parseInt(minValue) < alt) {													//come convertire una stringa in int Integer.parseInt(s)
			if(Integer.parseInt(maxValue) >= alt) {										
				return minValue + "-" + maxValue;
			}
		}
		
		return null;
	}
}
