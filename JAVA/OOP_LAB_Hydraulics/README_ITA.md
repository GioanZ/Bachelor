Simulazione Idraulica
=====================

Realizzare il sistema software per la descrizione e la simulazione di un sistema idraulico.  
Tutte le classi si trovano nel package **hydraulic**.

R1: Elementi e Tubi
-------------------

Un sistema idraulico è composto da elementi di vario tipo connessi tra loro (tramite tubi che però non sono modellati esplicitamente con questo software).

Un sistema idraulico è rappresentato da un oggetto di classe **HSystem**; questa classe permette di aggiungere nuovi elementi tramite il metodo **addElement()**, il quale riceve come parametro un oggetto **Element** e lo aggiunge ai componenti che formano il sistema idraulico.

Tramite il metodo **getElements()** è possibile ottenere un array contenente tutti e soli gli elementi presenti nel sistema, questo metodo restituisce un array di oggetti _Element_.

Tutti gli elementi hanno un nome che può essere letto tramite il metodo **getName()**.

R2: Elementi semplici
---------------------

Sono definiti tre tipi di elementi semplici: sorgente, rubinetto e scarico, che sono rispettivamente rappresentati dalle classi **Source**, **Tap** e **Sink**.

È possibile connettere l'uscita di un elemento all'ingresso di un altro tramite il metodo **connect()**; il metodo riceve come parametro l'elemento al cui ingresso deve essere connessa l'uscita dell'elemento sui cui è invocato: ad esempio, _a.connect(b);_ connette l'uscita di _a_ all'ingresso di _b_. Il metodo **connect()** se invocato su un oggetto _Sink_ non ha nessun effetto.

Dato un elemento semplice qualunque, è possibile sapere a quale altro elemento è connessa la sua uscita, tramite il metodo **getOutput()** che resituisce un oggetto di tipo _Element_.

R3: Elementi complessi
----------------------

Oltre agli elementi semplici, sopra descritti,è possibile utilizzare degli elementi complessi. L'elemento a T, rappresentato dalla classe **Split**, permette di suddividere l'ingresso in due flussi in uscita uguali tra loro. Per tale classe il metodo **connect()** riceve un ulteriore parametro, di tipo intero, che indica il numero dell'uscita a cui connettere l'elemento. Tale intero ha valore _0_ per la prima uscita e _1_ per la seconda.

Per sapere quali elementi sono connessi in uscita ad un elemento a T, è possibile utilizzare il metodo **getOutputs()** che restituisce un array con i due elementi connessi.

R4: Simulazione
---------------

Dato un sistema corretto, ovvero un albero che ha come radice una sorgente ed in cui ogni percorso termina con uno scarico, è possibile fare un calcolo delle portate e di come vengono ripartite nei vari elementi.

Il calcolo prevede due fasi: una prima fase (_setup_) i cui si definiscono i parametri dei diversi elementi del sistema e una seconda fase (_simulazione_) in cui si avvia la simulazione.

Durante la fase si setup è possibile:

*   definire la portata per una sorgente (_Source_) con il metodo **setFlow()**, che riceve come parametro un numero reale che rappresenta i metri cubi al secondo erogati dalla sorgente
    
*   impostare l'apertura dei rubinetti (_Tap_), tramite il metodo **setOpen()**, che riceve come parametro un _boolean_. Se un rubinetto è aperto la portata in uscita è uguale a quell in ingresso, altrimenti la portata in uscita è nulla (_0.0_).
    

Per i raccordi a T la portata in ingresso viene ripartita equamente tra le due uscite.

Il metodo **simulate()** della classe **HSystem**, effettua i calcoli di portata a partire da ogni sorgente e notifica, per ogni elemento: il nome e le portate in ingresso e in uscita. Questo metodo richiede come parametro un oggetto che implementa l'interfaccia **SimulationObserver**, che presenta un unico metodo.

Quando, durante la simulazione, sono noti i flussi in entrata ed in uscita per un elemento deve essere invocato il metodo **notifyFlow()** passando il tipo di elemento (nome della classe), il nome dell'elemento, ed i flussi in ingresso ed uscita; se uno dei flussi non è definito (ad es. per _Source_ e _Sink_) si usa la costante _NO\_FLOW_.

*   Suggerimento: dato un oggetto, per sapere se è un'istanza di una classe si può usare l'operatore `instanceof`. Es. _if(element instanceof Source)_
*   Attenzione: non è richiesto implementare l'interfaccia _SimulationObserver_ ma solamente usarla; per scopi di verifica viene fornito un esempio di implementazione (classe _PrintingObserver_) che semplicemente stampa su console le notifiche.


Simulazione Sistema Idraulico - **Estensione**
==============================================

Estendere all'interno della classe **HSystemExt** le [funzionalità già implementate](Requisiti.html) nella classe _HSystem_.

La nuova classe **HSystemExt** estende la classe _HSystem_.

R5. Multi-split
---------------

La classe **Multisplit** rappresenta un'estensione delle classe _Split_ che prevede più uscite. Il costruttore accetta, oltre al nome, il numero di uscite.

Il metodo **connect()** riceve due parametri: l'elemento da collegare ed il numero dell'uscita a cui collegarlo. Le uscite sono numerate a partire da _0_

Per sapere quali elementi sono connessi in uscita ad un multisplit, è possibile utilizzare il metodo **getOutputs()** che restituisce un array con gli elementi connessi. Se nessun elemento è connesso ad una certa uscita, la cella corrispondente dell'array è _null_.

In preparazione alla simulazione è possibile utilizzare il metodo **setProportions()** che accetta una serie di _double_ che definiscono la proporzione con cui ripartire il flusso in ingresso sulle uscite.

*   Si assuma che il numero di proporzioni passate al metodo sia pari al numero di uscite e che la loro somma sia pari a _1.0_.

R6. Visualizzazione
-------------------

Il metodo **layout()** della classe **HSystemExt** (attenzione: non **HSystem**) restituisce una stringa che contiene la disposizione degli element del sistema utilizzando caratteri ASCII e opportune spaziature.

Ogni elemento viene stampato nella forma _"\[name\]Type"_ dove _name_ è il nome dell'elemento e _Type_ è la classe dell'elemento. La connessione tra uscita di un elemento e ingresso di un altro è rappresentata dal simbolo _"->"_ mentre l'assenza di un elemento connesso in uscita è rappresentata da _"\*"_. Nel caso di più elementi connessi a valle di un elemento si usa il carattere _"+"_ e si riporta la prima connessione sulla stessa riga, e in righe successive si ripete _"+"_ (allineato verticalmente al primo) e poi si riportano le altre connessioni. Le righe che separano le connessioni multiple (almeno una, ma potrebbero essere più di una se a valle ci sono altri elementi con uscite multiple) si riporta il carattere _"|"_ allineato verticalmente a _"+"_.

Per esempio, un sistema composto da una _Source_ connessa a un _Tap_, che è connesso a uno _Split_ le cui uscite sono connesse a due _Sink_, avrebbe un layout simile al seguente:

\[Src\]Source -> \[R\]Tap -> \[T\]Split +-> \[sink A\]Sink
                                  |
                                  +-> \[sink B\]Sink 

*   Si tenga presente che il sistema potrebbe non essere completo, ovvero alcune uscite di elementi potrebbero non essere connesse ad alcun elemento.

R7. Eliminazione elementi
-------------------------

Il metodo **deleteElement()** della classe **HSystemExt** permette di eliminare un elemento precedentemente aggiunto al sistema; il metodo accetta come parametro il nome dell'elemento da eliminare.

Se l'elemento è uno _Split_ o un _Multisplit_ con più di una uscita connessa, non viene effettuata alcuna operazione ed il metodo restituisce _false_.

Altrimenti (_Split_ o _Multisplit_ con al più una uscita connessa oppure un altro tipo di elemento) l'elemento viene rimosso dal sistema e, se l'elemeto da eliminare è connesso ad altri elementi in ingresso e/o in uscita, occorre modificare modificare le connessioni di conseguenza in modo che l'elemento a monte sia connesso a quello a valle. In questo secondo caso il metodo restituisce _true_. Riprendendo l'esempio in [R6](#r6), il layout dopo l'eliminazione di _R_ deve essere il seguente:

\[Src\]Source -> \[T\]Split +-> \[sink A\]Sink
                        |
                        +-> \[sink B\]Sink

R8. Portata massima elementi ed allarmi
---------------------------------------

La nuova classe **ElementExt** estende la classe **Element** aggiungendo il metodo **setMaxFlow()**, che accetta come parametro un numero reale che rappresenta la portata massima di un elemento. Se un elemento riceve una portata in ingresso maggiore della portata massima, l'elemento rischia di rompersi. Per gli oggetti di classe **Source**, non avendo questi ultimi alcun ingresso, le chiamate al metodo **setMaxFlow()** non devono sortire alcun effetto.

La classe **HSystemExt** contiene un overload del metodo **simulate** che accetta come parametro il valore booleano **enableMaxFlowCheck**: se quest'ultimo è settato a vero, il metodo deve effettuare il controllo aggiuntivo sulla portata massima, notificando un errore se la portata in ingresso di un elemento è superiore alla sua portata massima. Il metodo **simulate** accetta in ingresso anche un oggetto che implementa la classe **SimulationObserverExt**, estensione dell'interfaccia **SimulationObserver**, che aggiunge a quest'ultima il metodo **notifyFlowError**, attraverso il quale è possibile notificare l'errore sulla portata massima, passando il tipo di elemento (nome della classe), il nome dell'elemento, il flusso in ingresso e la sua portata massima.

*   Hint: è consentito modificare le classi **Source**, **Split**, **Tap** e **Sink** in modo che estendano la classe **ElementExt** (dato che quest'ultima estende a sua volta **Element**).
