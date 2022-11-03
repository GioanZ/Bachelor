# Gestione Ateneo

Progettare ed implementare un programma che possa gestire corsi, docenti e studenti di un ateneo. Tutte le classi devono appartenere al pacakge university. 
Il programma interagisce con i propri clienti attraverso la classe di facciata University. 

## R1. Ateneo

La classe principale è University che riceve, come parametro del costruttore, il nome dell'ateneo. 

Il nome dell'ateneo è leggibile tramite il metodo getter getName(). 

È possibile definire il nome del rettore di un ateneo tramite il metodo setRector() che riceve come parametri nome e cognome del rettore. 

Il metodo getter getRector() restituisce nome e cognome del rettore concatenati e separati da uno spazio (" "). 

## R2. Studenti

È possibile inserire le informazioni relative ad un nuovo studente tramite il metodo enroll() della classe University, che riceve come parametri il nome ed il cognome dello studente; il metodo restituisce il numero di matricola che è stato assegnato allo studente.
 I numeri di matricola vengono assegnati, in maniera progressiva per ciascun ateneo a partire dal numero 10000. Quindi il primi studente iscritto ad ogni ateneo avrÃ  matricola 10000 

Per ottenere le informazioni relative ad uno studente si utilizza il metodo student() che riceve come parametro la matricola e restituisce una stringa composta da numero di matricola, nome e cognome separati da spazi, es. "10000 Giuseppe Verdi". 

💡Si assuma che ciascun ateneo non possa contenere più di 1000 studenti. 

## R3. Insegnamenti

Per definire un nuovo insegnamento si utilizza il metodo activate() che riceve come parametri il titolo del corso e il nome del docente titolare. Il metodo restituisce un intero che corrisponde al codice del corso. I codici vengono assegnati progressivamente a partire da 10. 

Per conoscere le informazioni relative ad un corso si usa il metodo course() che riceve come parametro il codice del corso e resituisce una stringa contenente codice, titolo e titolare del corso, separati da virgole, es. "10,Programmazione a Oggetti,James Gosling". 

💡Si assuma che ciascun ateneo non possa attivare più di 50 insegnamenti. 

## R4. Iscritti agli insegnamenti

Gli studenti possono essere iscritti agli insegnamenti tramite il metodo register() che riceve come parametro la matricola dello studente ed il codice dell'insegnamento. 

Per ottenere l'elenco degli iscritti ad un insegnamento è disponibile il metodo listAttendees() che riceve come parametro il codice dell'insegnamento e restituisce una stringa contenente l'elenco degli studenti iscritti. 

Gli studenti compaiono uno per riga (le righe sono terminate da un a-capo "\n") secondo il formato descritto al punto R2. 

Data la matricola di uno studente, tramite il metodo studyPlan(), è possibile conoscere l'elenco degli insegnamenti a cui è iscritto, gli insegnamenti sono descritti come al punto precedente. 

💡Si assuma che ciascuno studente non possa essere iscritto a più di 25 insegnamenti e che un insegnamento non possa avere più di 100 iscritti. 

# Gestione Ateneo - Estensione
Estendere all'interno della classe UniversityExtle funzionalità già implementate nella classe University. 

La nuova classe UniversityExt estende la classe University. 

## R5. Esami

Gli studenti possono sostenere gli esami degli insegnamenti a cui sono iscritti. Il voto di un esame può essere registrato tramite il metodo exam() che riceve come parametri l'ID dello studente, il codice del corso ed il voto (un intero in 0-30). 

per ottenere la media dei voti di uno studente si usa il metodo studentAvg() che accetta come parametro l'ID dello studente. Se lo studente ha sostenuto almeno un esame il metodo restituisce uan stringa con il seguente formato "Student STUDENT_ID : AVG_GRADE". Altrimenti restituisce "Student STUDENT_ID hasn't taken any exams". 

È possibile otterene la media dei voti di tutti gli studenti che hanno sostenuto l'esame di un dato insegnamento tramite il metodo courseAvg(), che accetta come parametro il codice del corso. Il formato è il seguente "The average for the course COURSE_TITLE is: COURSE_AVG", se almeno uno studente ha sostenuto l'esame per l'insegnamento dato. Altrimenti il metodo restituisce "No student has taken the exam in COURSE_TITLE". 

💡Si può assumere che se uno studente sostiene un esame sia stato precedentemente iscritto all'insegnamento. 

## R6. Premi per gli studenti

L'ateneo ha deciso di premiare i migliori studenti per il loro lavoro. Il metodo topThreeStudents() è utilizzato per reperire le informazioni che aiutino la commissione che dovrà prendere la decisione. 

Il punteggio degli studenti è valutato sulla base della media degli esami sostenuti. Per tenere in considerazione anche il numero di esami sostenuti e non solo la media, viene assegnato un bonus aggiuntivo alla media: il numero degli esami sostenuti divviso il numero di insegnamenti a cui è iscritto lo studente, moltiplicato per 10 viene sommato all media. 

Il metodo restituisce una una stringa con le informazioni relative ai tre studenti con il punteggio più alto. Gli studenti vengono riportati uno per riga (le righe sono terminate dal caratteredi fine linea '\n') e ciascuna linea è formattata come segue: "STUDENT_FIRSTNAME STUDENT_LASTNAME : SCORE". 

💡Si assuma che non ci siano parimerito. 

## R7. Logger

Si aggiunga un log per le operazioni eseguite tramite la classe di facciata UniversityExt. Tali operazioni includono: 
* iscrizione di uno studente: es. "New student enrolled: 10000, Mario Rossi"

* attivazione di un nuovo insegnamento: es. "New course activated: 11, Object Oriented Programming James Gosling"

* iscrizione di uno studente ad un insegnamento: es. "Student 10004 signed up for course 11"

* assegnazione del voto per un esame: es. "Student 10001 took an exam in course 12 with grade 27"



💡per eseguire il logging, è disponibile un oggetto logger di classe java.util.logging.Logger all'interno della classe UniversityExt; 

💡si usi il metodo info() dell'oggetto logger per generare i messaggi; 

💡si noti che per default il logger stampa i messaggi sulla console. 
