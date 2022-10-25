<html>
<head>
<title>Programmazione</title>
</head>

<body>
<h3> Inserimento nuova programmazione/lezione </h3>
<form method="get" action="inserisciProgrammazione.php">
Programmazione della nuova lezione settimanale
<br>
<table>
  <tr>
    <td> Istruttore: </td>
    <td> <select name="codfisc">
      <?php
      $con = mysqli_connect('localhost','root','','palestra');

      if (mysqli_connect_errno()){
        echo "Failed to connect to MySQL: " . mysqli_connect_error();
      }

      mysqli_set_charset($con, 'utf8mb4');

      $sql = "SELECT CodFisc, Cognome, Nome
      FROM istruttore
      ORDER BY Cognome, Nome";

      $result = mysqli_query($con,$sql);

      if( !$result )
        die('Query error: ' . mysqli_error($con));


      if( mysqli_num_rows($result) > 0 ){
        while ($row = mysqli_fetch_row($result)) {
          echo "<option value=$row[0]>$row[1] $row[2] ($row[0])</option>";
        }
      }

      ?>
      </select>
    </td>
  </tr>

  <tr>
    <td> Giorno: </td>
    <td> <input type="text" size="10" maxlength="10" name="giorno"> </td>
  </tr>
  <tr>
    <td> Ora inizio: </td>
    <td> <input type="text" size="10" maxlength="10" name="orainizio"> </td>
  </tr>
  <tr>
    <td> Durata: </td>
    <td> <input type="text" size="10" maxlength="10" name="durata"> </td>
  </tr>
  <tr>
    <td> Corso: </td>
    <td>
      <select name="codc">
    <?php

    $con = mysqli_connect('localhost','root','','palestra');

    if (mysqli_connect_errno()){
      echo "Failed to connect to MySQL: " . mysqli_connect_error();
    }

    $sql = "SELECT CodC, Nome
            FROM corsi
            ORDER BY Nome";

    $result = mysqli_query($con,$sql);

    if( !$result )
      die('Query error: ' . mysqli_error($con));

    if( mysqli_num_rows($result) > 0 ){
      while ($row = mysqli_fetch_row($result)) {
        echo "<option value=$row[0]>$row[1] ($row[0])</option>";
      }
    }

    ?>
    </select>
    </td>
  </tr>

  <tr>
    <td> Sala: </td>
    <td> <input type="text" size="2" maxlength="2" name="sala"> </td>
  </tr>

</table>

<p> <input type="submit" value="Inserisci">
</form>
</body>
</html>
