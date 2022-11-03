Dieta
=====

Sviluppare un'applicazione che consenta di gestire la dieta tramite il calcolo dei valori nutritivi.

L'applicazione deve permettere di definire le materie prime, di utilizzarle come ingredienti per delle ricette, di gestire prodotti confezionati e menù.

Tutte le classi devono trovarsi nel package "**diet**".

R1 - Materie Prime  

---------------------

Il sistema interagisce principalmente tramite la classe **Food**.

Per definire una materia prima, si utilizza il metodo **defineRawMaterial()** che riceve come parametri il nome, le kilo-calorie, le proteine, i carboidrati e i grassi, tutti riferiti a 100 grammi di materia prima. Si può assumere che il nome delle materie prima sia univoco.

Per avere informazioni sulle materie prime, si utilizza il metodo **rawMaterials()** che restituisce la collezione delle materie prime in ordine alfabetico. Per ottenere le informazioni su una specifica materia prima ci si avvale del metodo **getRawMaterial()** che riceve come parametro il nome e restituisce la materia prima corrispondente.

Gli elementi restituiti dai due metodi precedenti implementano l'interfaccia **NutritionalElement** che definisce i metodi **getName()**, **getCalories()**, **getProteins()**, **getCarbs()**, **getFat()**. Le calorie sono espresse in KCal, mentre proteine, carboidrati e grassi sono espressi in grammi.  
Inoltre l'interfaccia definisce il metodo booleano **per100g()** che indica se il valori nutritivi sono espressi per 100 grammi di elemento oppure esprimono un valore assoluto.  
Nel caso delle materie prime i valori nutritivi sono espressi sempre per 100 grammi.

R2 - Prodotti
-------------

È possibile considerare anche prodotti preconfezionati (ad esempio un cono gelato). I prodotti vengono definiti tramite il metodo **defineProduct()** della classe _Food_ che riceve come parametri il nome, le kilo-calorie totali, le proteine, i carboidrati e i grassi che esprimono i valori complessivi per il prodotto (ovvero non per 100 g). Si può assumere che il nome del prodotto sia univoco.

Per avere informazioni sui prodotti si utilizza il metodo **products()** della classe _Food_ che restituisce la collezione dei prodotti in ordine alfabetico. Per otterenere le informazioni su uno specifico prodotto ci si avvale del metodo **getProduct()** della classe _Food_ che riceve come parametro il nome e restituisce il prodotto corrispondente.

Gli elementi restituiti dai due metodi precedenti implementano l'interfaccia _NutritionalElement_ (descritta al punto precedente); i valori sono espressi per prodotto intero, perciò il metodo _per100g()_, in tal caso, restituisce _false_.

R3 - Ricette
------------

Le materie prime possono essere combinate come ingredienti di ricette. Per definire una ricetta viene utilizzato il metodo **createRecipe()** che riceve come parametro il nome della ricetta, che può essere considerato unico.

Le ricette sono rappresentate da oggetti di classe **Recipe** che permettono di aggiungere ingredienti tramite il metodo **addIngredient()** che riceve come parametri il nome di una materia prima e la sua quantità in grammi.

La classe _Recipe_ implementa l'interfaccia _NutritionalElement_ e i valori nutrizionali sono espressi per 100 grammi.

Per avere informazioni sulle ricetta si utilizza il metodo **recipes()** della classe _Food_ che restituisce la collezione delle ricetta in ordine alfabetico. Per ottenere le informazioni su una specifica ricetta ci si avvale del metodo **getRecipe()** che riceve come parametro il nome e restituisce la ricetta corrispondente. Entrambi i metodi restituiscono le ricette sotto forma di _NutritionalElement_.

Il metodo **toString()** della classe _Recipe_ restituisce una stringa che riporta gli ingredienti uno per per riga, con il formato _"Materiale : ###.#"_ dove _Materiale_ è il nome del materiale e _###.#_ è la quantità. Le righe sono tutte terminate dal carattere _'\\n'_ e gli ingredienti devono comparire nell'ordine in cui sono stati aggiunti alla ricetta.

*   **Attenzione**: la somma delle quantità (in grammi) degli ingredienti di una ricetta non necessariamente è pari a 100g, i valori nutrizionali della ricetta devono essere invece riferiti ad un'ideale porzione di 100g.

R4 - Menù
---------

Il menù è composto sia da porzioni di ricette sia da prodotti preconfezionati.

Un nuovo menù è creato tramite il metodo **createMenu()** che accetta come parametro il nome (unico) del menù.

I menù sono rappresentati dalla classe **Menu** che permette di aggiungere una porzione di una ricetta tramite il metodo **addRecipe()** che riceve come parametro il nome di una ricetta e la dimensione della porzione in grammi. Per aggiungere un prodotto preconfezionato, la classe _Menu_ offre il metodo **addProduct()** che riceve come parametro il nome del prodotto.

Inoltre la classe _Menu_ implementa l'interfaccia _NutritionalElement_; in questo caso i valori restituiti si riferiscono al totale del menu.

DietExt
=======

Requisiti Estesi
================

L'applicazione progettata per gestire una dieta grazie al calcolo dei valori nutrizionali è stata modificata per fornire servizi per ordinare e consegnare cibo takeaway.

L'applicazione permette di creare ristoranti, registrare utenti, inserire ordini, ecc.

Tutte le classi devono essere nel package "**diet**".

R5 - Ristorante
---------------

Le interazioni avvengono principalmente tramite la clase **Takeaway**.

Un oggetto **Restaurant** può essere creato fornendo un nome ed un riferimento all'oggetto _Food_ in modo che tutti gli ingredienti, i prodotti e le ricette possano essere definite per ciascun ristorante individualmente.

Un ristorante è identificato dal suo nome. Attraverso il metodo **setHours()** è possibile definire l'orario di servizio del ristorante. Il metodo accetta un vettore di stringhe (in numero pari di elementi) secondo il formato _"HH:MM"_, tale per cui le ore di chiusura seguono le ore di apertura (es., per un ristorante aperto dalle 8:15 alle 14:00 e dalle 19:00 alle 00:00, gli argomenti devono essere _"08:15", "14:00", "19:00", "00:00"_). Il metodo getter **getName()** restituisce il nome del ristorante. Un ristorante offre diversi menù che possono essere creati utilizzando il metodo **createMenu()** che ha per argomento il nome del menù e restituisce un oggetto _Menu_.

I ristoranti possono essere inseriti nel sistema utilizzando il metodo **addRestaurant()** della classe di facciata _Takeaway_. Il metodo **restaurants()** ritorna i nomi dei ristoranti inseriti.

R6 - Utenti
-----------

Un utente è definito fornendo il suo nome, cognome, email e numero di telefono al metodo **registerUser()** il quale ritorna un oggetto **User**. Sono disponibili dei metodi getter per tutti i campi (**getFirstName()**, **getLastName()**, **getEmail()**, **getPhone()**), mentre i metodi setter sono forniti solo per l'email ed il numero di telefono (**setEmail()**, **setPhone()**). La rappresentazione come stringa dell'oggetto _User_ è il cognome separato da uno spazio e seguito dal nome.

Per ottenere gli utenti disponibili è possibile utilizzare il metodo **users()** della classe _Takeaway_ che ritorna una collezione di utenti ordinati per cognome e, nel caso di cognomi uguali, per nome.

R7 - Ordini
-----------

Un utente registrato può effettuare un ordine in uno dei ristoranti disponibili. Per tale scopo il metodo **createOrder()** accetta come argomenti l'oggetto _User_ che effettua l'ordine, il nome del ristorante (_String_) e l'orario di consegna desiderato (con ore e minuti come numeri interi). Inoltre, se per un certo ordine l'orario di consegna è al di fuori dell'orario di servizio del ristorante, l'orario di consegna è impostato alla prima ora di apertura successiva (es., facendo un ordine per un ristorante con orario di servizio dalle 8:15 alle 14:00 e dalle 19:00 alle 00:00, e richiedendo una consegna per le 15:30, l'orario di consegna sarà impostato alle 19:00).

Un ordine può essere in uno dei seguenti stati: `ORDERED`, `READY` e `DELIVERED`, accessibile attraverso i metodi setter e getter **setStatus()** e **getStatus()** (`ORDERED` è lo stato di default). Inoltre, il tipo di pagamento di un ordine può essere: `PAID`, `CASH` o `CARD`, accessibile attraverso i metodi setter e getter **setPaymentMethod()** e **getPaymentMethod()** (`CASH` è il pagamento di default).

I menù possono essere aggiunti ad un ordine chiamando il metodo **addMenus** e specificando il nome del menù (come stringa) e la quantità (come numero intero).

Quando un ordine è stampato, deve essere formattato come segue:

"RESTAURANT\_NAME, USER\_FIRST\_NAME USER\_LAST\_NAME : DELIVERY(HH:MM):
	MENU\_NAME\_1->MENU\_QUANTITY\_1
	...
	MENU\_NAME\_k->MENU\_QUANTITY\_k
"

I menù sono ordinati per nome e sono riportati, uno per linea, preceduti da una tabulazione (_'\\t'_).

*   **Attenzione**: Se un certo menù è già stato aggiunto ad un ordine, l'usarlo di nuovo come argomento di **addMenus()** deve sovrascrivere la quantità definita in precedenza.

R8 - Informazioni
-----------------

Per ottenere alcune informazioni relative ai ristoranti può essere utilizzato il metodo **openedRestaurants()** il quale ha un argomento di tipo stringa nel formato "HH:MM" e ritorna una collezione di oggetti _Restaurant_ che sono aperti in un certo orario, ordinati alfabeticamente per nome. Un ristorante è aperto se c'è almeno un segmento di orario di servizio tale per cui l'orario richiesto è compreso nell'intervallo \[`aperto`, `chiuso`).

Le informazioni relative agli ordini di un ristorante possono essere ottenute attraverso il metodo **ordersWithStatus()** della classe Restaurant. Tale metodo ritorna una stringa ottenuta dalla concatenazione di tutti gli ordini che soddisfano il criterio.

Napoli, Judi Dench : (19:00):
	M6->1
Napoli, Ralph Fiennes : (19:00):
	M1->2
	M6->1

La lista è ordinata per nome del ristorante, nome dell'utente ed orario di consegna.
