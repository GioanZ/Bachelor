package university;

public class Insegnamento {
	
	private String titolo, docente;
	private int codice, qSt = 0, qVoto = 0;
	private Studente[] id = new Studente[University.MAX_ST_ISCRITTI];
	
	private int[]voti = new int[University.MAX_INS_FREQUENTATI];
	
	public Insegnamento(String titolo, String docente, int codice){
		this.titolo = titolo;
		this.docente = docente;
		this.codice = codice;
	}
	
	public int getCodice() {
		return codice;
	}

	public String getTitolo() {
		return titolo;
	}
	
	public String getDocente() {
		return docente;
	}
	
	public String getDati() {
		return codice + " " + titolo + " " + docente;
	}

	public void setSt(Studente id) {
		this.id[qSt++] = id;
	}
	
	public String stampaStudentiDelCorso() {
		String s = new String();
		for(int i = 0; i<qSt; i++) {
			s += id[i].getDati() + "\n";
		}
		
		return s;
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
}
