Ambulatorio
===========

Realizzare un sistema per gestire i pazienti di un ambulatorio medico. Le classi sono contenute nel package **clinic**.

R1: Pazienti
------------

La classe principale del programma è **Clinic**.

I pazienti sono caratterizzati da nome, cognome, e dal codice fiscale (SSN). Nuovi pazienti possono essere aggiunti tramite il metodo **addPatient()**.

Le informazioni su un paziente possono essere recuperate tramite il metodo **getPatient()** che, dato un codice fiscale restituisce una stringa con il seguente formato _"<Last> <First> (<SSN>)"_.

Se il paziente non esiste viene generata l'eccezione **NoSuchPatient**.

R2: Dottori
-----------

I dottori sono caratterizzati da nome, cognome, SSN, numero di badge e dalla specializzazione (es. "cardiologo", "dentista"). È possibile aggiungere un nuovo dottore tramite il metodo **addDoctor()**.

Il metodo **getDoctor()**, dato il numero di badge restituisce una stringa con il seguente formato _"<Last> <First> (<SSN>) \[<ID>\]: <Specialization>"_.

Se il dottore non esiste viene generata l'eccezione **NoSuchDoctor**.

Si tenga presente che un dottore potrebbe essere paziente dello stesso ambulatorio.

R3: Registrazione dei pazienti
------------------------------

Quando sono accettati, i pazienti vengono assegnati a uno dei dottori dell'ambulatorio. Per questo si usa il metodo **assignPatientToDoctor()**, che accetta come parametri il codice fiscale del paziente ed il numero di badge del dottore. Se il dottore non esiste, viene generata l'eccezione **NoSuchDoctor**, mentre se il paziente non esiste viene generata l'eccezione **NoSuchPatient**.

Tramite il metodo **getAssignedDoctor()** che accetta il codice fiscale di un paziente è possibile ottenere il codice del dottore assegnato al paziente. Se il paziente non esiste viene lanciata un'eccezione _NoSuchPatient_; se il paziente non è stato assegnato ad alcun dottore viene lanciata un'eccezione _NoSuchDoctor_.

Il metodo **getAssignedPatients()** accetta il codice di un dottore e restituisce la collezione dei codici fiscali dei pazienti assegnati al dottore. Se il codice non corrisponde ad alcun dottore, viene lanciata un'eccazione _NoSuchDoctor_.

R4: Lettura
-----------

Il metodo **loadData()** della classe _Clinic_ accetta un Reader e legge le informazioni su pazienti e dottori.

Il file è organizzato per righe; ogni riga contiene informazioni relative a pazienti o a dottori.

Le righe contenenti informazioni sulle persone iniziano con la lettera "_P_" seguita da nome, cognome, e SSN. Le righe che descrivono i dottori iniziano con la lettera "_M_", seguita da numero di badge, nome, cognome, SSN e specialità.

Tutti gli elementi su una linea sono separati dal carattere "_;_", eventualmente circondato da spazi che devono essere ignorati.

In caso di errore nei contenuti del file, il metodo ignora la linea e passa a quella successiva.

In caso di errori di IO le eccezioni devono essere propagate al chiamante.

Il metodo restituisce il numero di righe correttamente lette

Una seconda versione del metodo **loadData()** accetta un secondo parametro di tipo **ErrorListener**. Questa interfaccia definisce il metodo **offendingLine()** che accetta un paramentro string. Durante la lettura, ogni volta che viene incontrata una linea errata (che deve essere scartate) il metodo _loadData()_ deve invocare _offendingLine()_ passando la linea.

R5: Statistiche
---------------

Il metodo **idleDoctors()** resituisce una collezione con tutti i dottori che non hanno pazienti, ordinata in ordine alfabetico (prima per cognome e poi per nome).

Il metodo **busyDoctors()** restituisce la collezione dei dottori che hanno un numero di pazienti superiore alla media.

Il metodo **doctorsByNumPatients()** restituisce una collezione di stringhe contenenti il nome del dottore ed il relativo numero di pazienti ordinati in maniera decrescente di numero.  
Le stringhe devono essere formattate come "_\### : ID SURNAME NAME_" dove _###_ rappresenta il numero di pazienti (stampato su tre caratteri).

Il metodo **countPatientsPerSpecialization()** conta il numero di pazienti per specializzazione (dei dottori). Gli elementi della lista di stringhe sono ordinati prima per numero decrescente di pazienti e poi in ordine alfabetico di specializzazione.  
Le stringhe sono strutturate come "_\### - SPECIALITY_" dove _###_ rappresenta il numero di pazienti (stampato su tre caratteri).

### Suggerimento:

*   Per formattare il numero di pazienti si può utilizzare il metodo [_String.format()_](https://oop.polito.it/api/java/lang/String.html#format-java.lang.String-java.lang.Object...-).  
    Ad esempio _String.format("%3d", i)_ stampa una variabile intera _i_ con una larghezza di tre caratteri.
