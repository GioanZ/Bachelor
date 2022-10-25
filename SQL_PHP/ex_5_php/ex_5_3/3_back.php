<html>
<head>
<title>Inserimento corso</title>
</head>

<body>
<?php

if( !isset($_REQUEST["codc"]) or
  !isset($_REQUEST["nome"]) or
  !isset($_REQUEST["tipo"]) or
  !isset($_REQUEST["livello"])){
    echo "<div class = 'w3-red w3-text-white'>
      <h2>Errore di inserimento!</h2>
      <p>Errore: inserire tutti i dati richiesti</p>
      </div>";
    exit;
  }

$codc = $_REQUEST["codc"];
$nome = $_REQUEST["nome"];
$tipo = $_REQUEST["tipo"];
$livello = $_REQUEST["livello"];

if ($codc=="")
  echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Codice corso non valorizzato</p>
    </div>";

if ($nome=="")
  echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Nome corso non valorizzato</p>
    </div>";

if ($tipo=="")
  echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Tipo corso non valorizzato</p>
    </div>";

if ($livello=="")
  echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Livello corso non valorizzato</p>
    </div>";


if ($codc=="" || $nome=="" || $tipo=="" || $livello=="")
die();

if (!is_numeric($livello)){
  echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Il livello deve essere un valore intero
    compreso tra 1 e 4</p>
    </div>";
  exit;
}

if ($livello<1 || $livello>4){
  echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Il livello deve essere un valore intero
    compreso tra 1 e 4</p>
    </div>";
  exit;
}

$con = mysqli_connect('localhost','root','','palestra');

if (mysqli_connect_errno()){
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

mysqli_set_charset($con, 'utf8mb4');

if(mysqli_query($con,"INSERT INTO CORSI(CodC,Nome,Tipo,Livello)
VALUES('$codc', '$nome', '$tipo', '$livello');")){
  echo "<div class = 'w3-green w3-text-white'>
  <h2>Inserimento avvenuto!</h2>
  <p>Il corso $codc è stato inserito nel database.</p>
  </div>";
}
else {
  echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Non è stato possibile inserire i dati
    perchè si è verificato un errore:</p>
    </div>";
  echo mysqli_error($con);
  exit;
}

mysqli_close($con);
?>

</br>
  <form method="get" action="form1.php">
    <input type="submit" value="Effettua un altro inserimento">
  </form>

</body>
</html>
