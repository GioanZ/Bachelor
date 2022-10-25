<html>
<head>
title>Programmazione</title>
<link rel = "stylesheet" href = "https://www.w3schools.com/w3css/4/w3.css">
</head>

<body>

<?php

if( !isset($_REQUEST["codfisc"]) or
  !isset($_REQUEST["giorno"]) or
  !isset($_REQUEST["orainizio"]) or
  !isset($_REQUEST["durata"]) or
  !isset($_REQUEST["codc"]) or
  !isset($_REQUEST["sala"])) {
    echo "<div class = 'w3-red w3-text-white'>
      <h2>Errore di inserimento!</h2>
      <p>Errore: inserire tutti i dati richiesti</p>
      </div>";
    exit;
  }

$codfisc = $_REQUEST["codfisc"];
$giorno = $_REQUEST["giorno"];

if($giorno!="Lunedì" and $giorno!="Martedì" and $giorno!="Mercoledì" and $giorno!="Giovedì" and $giorno!="Venerdì"){
  echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Il giorno specificato non è valido</p>
    </div>";
  exit;
}

$orainizio = $_REQUEST["orainizio"];
$durata = $_REQUEST["durata"];

if ($durata>60){
  echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Le lezioni non possono durare più di 60 minuti</p>
    </div>";
  exit;
}

$codc = $_REQUEST["codc"];
$sala = $_REQUEST["sala"];

$con = mysqli_connect('localhost','root','','palestra');

if (mysqli_connect_errno()){
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

mysqli_set_charset($con, 'utf8mb4');
mysqli_query($con,"SET autocommit=0;");
mysqli_query($con,"START TRANSACTION;");

$sql = "SELECT count(*)
        FROM programma
        where CodC='$codc' and Giorno='$giorno' and OraInizio='$orainizio'";

$result = mysqli_query($con,$sql);

if( !$result )
  die('Query error: ' . mysqli_error($con));

$row = mysqli_fetch_row($result);

if ($row[0]!=0) {
  echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Non è consentito inserire due lezioni per lo stesso corso nello stesso giorno e alla stessa ora</p>
    </div>";
  mysqli_query($con,"ROLLBACK;");
  }
else {
  $sql = "SELECT count(*)
          FROM programma
          where Sala='$sala' and Giorno='$giorno' and OraInizio='$orainizio'";

  $result = mysqli_query($con,$sql);

  if( !$result )
    die('Query error: ' . mysqli_error($con));

  $row = mysqli_fetch_row($result);
  if ($row[0]!=0) {
    echo "<div class = 'w3-red w3-text-white'>
      <h2>Errore di inserimento!</h2>
      <p>Non è consentito inserire due lezioni per la stessa sala nello stesso giorno e alla stessa ora</p>
      </div>";
    mysqli_query($con,"ROLLBACK;");
}

else{
  $sql = "SELECT count(*)
          FROM programma
          where CodFisc='$codfisc' and Giorno='$giorno' and OraInizio='$orainizio'";

  $result = mysqli_query($con,$sql);

  if( !$result )
    die('Query error: ' . mysqli_error($con));

  $row = mysqli_fetch_row($result);
  if ($row[0]!=0) {
    echo "<div class = 'w3-red w3-text-white'>
    <h2>Errore di inserimento!</h2>
    <p>Non è consentito inserire due lezioni per lo stesso insegnate nello stesso giorno e alla stessa ora</p>
    </div>";
    mysqli_query($con,"ROLLBACK;");
  }
  else{
    if(mysqli_query($con,"INSERT INTO Programma (CodFisc,Giorno,OraInizio,Durata,CodC,Sala) VALUES ('$codfisc','$giorno','$orainizio','$durata','$codc','$sala');")){
      mysqli_query($con,"COMMIT;");
      echo "<div class = 'w3-green w3-text-white'>
      <h2>Inserimento avvenuto!</h2>
      <p>La lezione è stata inserita nel programma dei corsi.</p>
      </div>";
      }
      else{
        echo "<div class = 'w3-red w3-text-white'>
          <h2>Errore di inserimento!</h2>
          <p>Non è stato possibile inserire i dati perchè si è verificato un errore</p>
          </div>";
        echo mysqli_error($con);
        mysqli_query($con,"ROLLBACK;");
      }
    }
  }
}

mysqli_close($con);

?>

</br>
  <form method="get" action="form2.php">
    <input type="submit" value="Effettua un altro inserimento">
  </form>

</body>
</html>
