package university;

public class Studente {
	
	private String first, last;
	private int matricola, qIns = 0, qVoto = 0;
	private Insegnamento[] code = new Insegnamento[University.MAX_INS_FREQUENTATI];
	
	private int[]voti = new int[University.MAX_INS_FREQUENTATI];
	
	public Studente(String first, String last, int matricola){
		this.first = first;
		this.last = last;
		this.matricola = matricola;
	}
	
	public int getId() {
		return matricola;
	}

	public String getFirst() {
		return first;
	}
	
	public String getLast() {
		return last;
	}
	
	//sarebbe @Override di toString()
	public String getDati() {
		return matricola + " " + first + " " + last;
	}
	
	public void setIns(Insegnamento code) {
		this.code[qIns++] = code;
	}
	
	public String stampaCorsiPerStudente() {
		StringBuffer sb = new StringBuffer();

		for(int i = 0; i<qIns; i++) {
			sb.append(code[i].getDati()).append("\n");
		}
		
		return sb.toString();
	}
	
	
	
	
	public void setVoto(int voto) {
		this.voti[qVoto++]=voto;
	}
	
	public float getVotoAvg() {
		float media = 0;
		
		if(qVoto == 0)
			return 0;
		
		for(int i=0;i<qVoto;i++) {
			media += voti[i];
		}
		media = media/qVoto;
		
		return media;
	}
	
	public int getNEsamiSost(){
		return qVoto;
	}
	
	public int getNEsamiFreq(){
		return qIns;
	}
	
	public float getScore(){
		return (float)getNEsamiSost()/(float)getNEsamiFreq() * 10 + getVotoAvg();
	}
}

