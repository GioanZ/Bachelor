Rifugi di montagna
==================

Sviluppare un'applicazione che consenta di gestire le informazioni sui rifugi di montagna di una regione.  
L'applicazione deve permettere di inserire le informazioni su intervalli di altitudine, comuni e rifugi di montagna.  
Tutte le classi devono essere nel package "**mountainhuts**".

R1 - Intervalli di altitudine
-----------------------------

L'interazione con il sistema avviene tramite la classe **Region**. Il metodo **getName()** della classe **Region** ritorna il nome della regione specificato nel suo costruttore.

I rifugi sono classificati in base a delle fasce di altezza, che possono essere definite secondo le necessità. Per definire gli intervalli di altitudine disponibili si utilizza il metodo **setAltitudeRanges()** che riceve come parametro un vettore di strighe. Ogni stringa rappresenta un intervallo di altitudine utilizzando il formato "_\[minValue\]-\[maxValue\]_". Per esempio, l'intervallo "_0-1000_" rappresenta le altitudini da 0 a 1000 metri sul livello del mare, estremo superiore incluso ed estremo inferiore escluso. Si supponga che gli intervalli siano tra loro disgiunti.

Il metodo **getAltitudeRange()** riceve come parametro il valore di un'altitudine e ritorna la rappresentazione testuale dell'intervallo (tra quelli predefiniti) in cui tale altitudine è presente, estremo superiore incluso. Se non è disponibile alcun intervallo per tale altitudine, il metodo ritorna l'intervallo di default "_0-INF_".

R2 - Comuni e rifugi di montagna
--------------------------------

I comuni sono definiti utilizzando il metodo **createOrGetMunicipality()** che accetta come parametri la denominazione univoca del comune, la provincia e l'altitudine. Il metodo restistuisce un oggetto di classe **Municipality**. Se un comune con la stessa denominazione è stato creato in precedenza, il metodo ritorna il comune già disponibile, ignorando gli altri parametri.

I rifugi di montagna sono definiti utilizzando il metodo **createOrGetMountainHut()** che accetta come parametri la denominazione univoca del rifugio, la categoria, il numero di posti letto ed il comune in cui Ã¨ situato. Il metodo **createOrGetMountainHut()** accetta opzionalmente il parametro relativo all'altitudine del rifugio. Il metodo restistuisce un oggetto di classe **MountainHut**. Se un rifugio con la stessa denominazione è stato creato in precedenza, il metodo ritorna il rifugio già disponibile, ignorando gli altri parametri.

Le classi _Municipality_ e _MountainHut_ offrono gli ovvi metodi getter. Il metodo **getAltitude()** della classe _MountainHut_ restituisce un [_Optional_](https://docs.oracle.com/javase/8/docs/api/java/util/Optional.html) che è vuoto (_empty_) se l'altitudine del rifugio non è stata specificata.

È possibile ottenere le collezioni dei comuni e rifugi disponibili utilizzando i metodi **getMunicipalities()** e **getMountainHuts()**.

#### Suggerimenti

*   La classe [_Optional_](https://docs.oracle.com/javase/8/docs/api/java/util/Optional.html) viene utilizzata per segnalare esplicitamente che un valore può essere _null_. Il metodo _isPresent()_ indica se è presente un valore nell'optional.
    
    Per creare un _Optional_ a partire da una variable che potrebbe essere _null_ si può usare _Optional.ofNullable()_ che restituisce un _Optional_ contenente la variabile oppure un _Optional_ vuoto se la variabile è _null_.
    

R3 - Lettura da CSV
-------------------

È possibile, tramite il metodo statico **fromFile()**, creare un oggetto _Region_ a partire dal nome e dalle informazioni contenute in un file, passati come parametri. Le informazioni sono relative alle classi illustrate sopra. Il metodo deve popolare la classe regione creando gli oggetti comune e rifugio descritti nel file.

Le informazioni relative ai rifugi della regione sono memorizzati in un file con codifica [CSV](https://it.wikipedia.org/wiki/Comma-separated_values) che è strutturato in base alle seguenti colonne che contengono informazioni relative a comuni e rifugi di montagna:


  <table style="float:none;font-family:sans-serif;">
    <tr>
      <th>#</th>
      <th>Colonna</th>
      <th colspan="4">Informazioni relative alle classi</th>
    <tr>
      <th></th>
      <th></th>
      <th><b>Municipality</b></th>
      <th><b>MountainHut</b></th>
    </tr>
    <tr>
      <td>0</td>
      <th><i>Province</i></th>
      <td>&#10003;</td>
      <td></td>
    </tr>
    <tr>
      <td>1</td>
      <th><i>Municipality</i></th>
      <td>&#10003;</td>
      <td></td>
    </tr>
    <tr>
      <td>2</td>
      <th><i>MunicipalityAltitude</i></th>
      <td>&#10003;</td>
      <td></td>
    </tr>
    <tr>
      <td>3</td>
      <th><i>Name</i></th>
      <td></td>
      <td>&#10003;</td>
    </tr>
    <tr>
      <td>4</td>
      <th><i>Altitude</i></th>
      <td></td>
      <td>&#10003;</td>
    </tr>
    <tr>
      <td>5</td>
      <th><i>Category</i></th>
      <td></td>
      <td>&#10003;</td>
    </tr>
    <tr>
      <td>6</td>
      <th><i>BedsNumber</i></th>
      <td></td>
      <td>&#10003;</td>
    </tr>
  </table>
  

**Attenzione**: il file contiene una riga per ogni rifugio, quindi le informazioni relative ai comuni possono essere replicate più volte.

I campi del file CSV sono separati da un punto e virgola (_;_). La colonna relativa all'altitudine del rifugio può essere vuota se tale informazione non è disponibile.

I dati relativi ai rifugi della regione Piemonte sono disponibili nel file: _mountain\_huts.csv_ ( [\*](#note) ).

#### Suggerimenti

*   Per la lettura da file, si parta dal metodo **readData()** che legge le righe di un file e le inserisce in una lista. La prima riga del file contiene le intestazioni, mentre quelle successive contengono i dati veri e propri.

R4 - Interrogazioni
-------------------

Il metodo **countMunicipalitiesPerProvince()** restituisce una mappa contenente come chiave il nome di una provincia e come valore il numero dei comuni in tale provincia.

Il metodo **countMountainHutsPerMunicipalityPerProvince()** restituisce una mappa contenente come chiave il nome di una provincia e come valore un'altra mappa che fa corrispondere al nome di un comune il numero dei rifugi in esso presenti.

Il metodo **countMountainHutsPerAltitudeRange()** restituisce una mappa contenente come chiave gli intervalli di altitudine restituiti dal metodo _getAltitudeRanges()_ e come valore il numero dei rifugi con un'altitudine inclusa in tale intervallo. Se l'altitudine del rifugio non è disponibile, si consideri l'altitudine del comune corrispondente.

Il metodo **totalBedsNumberPerProvince()** restituisce una mappa contenente come chiave il nome di una provincia e come valore il numero totale dei posti letto disponibili nei rifugi situati in tale provincia.

Il metodo **maximumBedsNumberPerAltitudeRange()** restituisce una mappa contenente come chiave gli intervalli di altitudine restituiti dal metodo _getAltitudeRange()_ e come valore il numero massimo dei posti letto disponibili nei rifugi con un'altitudine inclusa in tale intervallo. Se l'altitudine del rifugio non è disponibile, si consideri l'altitudine del comune corrispondente.

Il metodo **municipalityNamesPerCountOfMountainHuts()** restituisce una mappa contenente come chiave il numero dei rifugi per comune e come valore una lista contenente i nomi dei comuni aventi tale numero di rifugi ordinata alfabeticamente.

*   Per svolgere le interrogazioni si consiglia di utilizzare gli Stream API che permettono di scrivere codice piÃ¹ compatto e piÃ¹ comprensibile, rispetto ad esplicite iterazioni su collezioni e mappe.

(\*): il file contiene una versione semplificata dei dati disponibili sul portale open data della regione, in particolare [https://www.dati.piemonte.it/#/catalogodetail/regpie\_ckan\_ckan2\_yucca\_sdp\_smartdatanet.it\_RifugiOpenDa\_2296](https://www.dati.piemonte.it/#/catalogodetail/regpie_ckan_ckan2_yucca_sdp_smartdatanet.it_RifugiOpenDa_2296)
