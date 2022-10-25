<!DOCTYPE html>
<html>
<link rel = "stylesheet" href = "https://www.w3schools.com/w3css/4/w3.css">
<body>

<?php

/* Verify parameter course_code */
if (!isset($_REQUEST["surname_instructor"]) || trim($_REQUEST["surname_instructor"]) == ""){
    echo '<p> ERRORE: Cognome mancante o vuoto. </p>';
    exit;
}

/* Verify parameter course_code */
if (!isset($_REQUEST["day"]) || trim($_REQUEST["day"]) == ""){
    echo '<p> ERRORE: Data mancante o vuota. </p>';
    exit;
}

$surname_instructor = $_REQUEST["surname_instructor"];
$day = $_REQUEST["day"];

/* Establish DB connection */
$conn = @mysqli_connect ( 'localhost', 'root', '', 'PALESTRA' );

if (mysqli_connect_errno()) {
	echo "Failed to connect to MySQL: " . mysqli_connect_error ();
}

/* String sanification for DB query */
$surname_instructor = utf8_decode( mysqli_real_escape_string($conn, $surname_instructor) );
$day = utf8_decode( mysqli_real_escape_string($conn, $day) );

/* Query construction */
$query = "SELECT Giorno as Giorno,
                    OraInizio as OraInizio,
                    ADDTIME(OraInizio, SEC_TO_TIME(Durata*60)) as OraFine,
                    Durata as Durata,
                    C.Nome as NomeCorso,
                    C.Tipo as TipoCorso,
                    C.Livello as LivelloCorso
            FROM PROGRAMMA AS P, ISTRUTTORE AS I, CORSI AS C
            WHERE P.CodFisc = I.CodFisc AND C.CodC=P.Codc
                AND I.Cognome = '$surname_instructor' AND P.Giorno = '$day'
            ORDER BY C.Livello ASC, C.Nome ASC";

/* Query execution */
$result = mysqli_query ( $conn, $query );
if (!$result){
    die ( 'Query error: ' . mysqli_error ( $conn ) );
}

/* Check if course found */
if (mysqli_num_rows ( $result ) > 0) {
    $day_viz = utf8_encode($day);
    echo "<h1>Dettagli per $surname_instructor, giorno $day_viz</h1>";
    echo "<table class='w3-table-all w3-hoverable'>";

    /* Table header */
    echo "<thead><tr>";

    echo "<th>Giorno</th>";
    echo "<th>Ora Inizio</th>";
    echo "<th>Ora Fine</th>";
    echo "<th>Durata</th>";
    echo "<th>Nome Corso</th>";
    echo "<th>Tipo Corso</th>";
    echo "<th>Livello Corso</th>";

    echo "</thead></tr>";


    /* Table content */
    while($row = mysqli_fetch_array($result)) {
        echo "<tr>";
        $final_time = date_parse($row["OraInizio"]);
        echo "<td>". htmlspecialchars(utf8_encode($row["Giorno"])) . "</td>";
        echo "<td>". htmlspecialchars($row["OraInizio"]) . "</td>";
        echo "<td>". htmlspecialchars($row["OraFine"]) . "</td>";
        echo "<td>". htmlspecialchars($row["Durata"]) . "</td>";
        echo "<td>". htmlspecialchars($row["NomeCorso"]) . "</td>";
        echo "<td>". htmlspecialchars($row["TipoCorso"]) . "</td>";
        echo "<td>". htmlspecialchars($row["LivelloCorso"]) . "</td>";

        echo "</tr>";
    }
    echo "</table>";

} else {
    echo "<h1>Nessun risultato trovato.</h1>";
}

?>

<hr>

<h3> Nuova ricerca </h3>

<form action="4_back.php">

    <label for = "surname_instructor">Cognome Istruttore:</label><br>
    <select id = "surname_instructor" name = "surname_instructor" class = "w3-select">
    <option value=''>Seleziona istruttore/istruttrice</option>
    <?php

        /* Establish DB connection */
        $conn = @mysqli_connect ( 'localhost', 'root', '', 'PALESTRA' );

        if (mysqli_connect_errno()) {
            echo "Failed to connect to MySQL: " . mysqli_connect_error ();
        }

        /* Query construction */
        $query = "SELECT Cognome FROM ISTRUTTORE";

        /* Query execution */
        $result = mysqli_query ( $conn, $query );
        if (!$result){
            die ( 'Query error: ' . mysqli_error ( $conn ) );
        }

        /* Check if course found */
        if (mysqli_num_rows ( $result ) > 0) {
            while($row = mysqli_fetch_array($result)) {
                $course_code = $row["Cognome"];
                echo "<option value = '$course_code'>$course_code</option>";
            }
        }

    ?>
    </select>
    <br><br>
    <label for = "day">Giorno:</label><br>
    <select id = "day" name = "day" class = "w3-select">
        <option value=''>Seleziona giorno</option>
        <option value='Lunedì'>Lunedì</option>
        <option value='Martedì'>Martedì</option>
        <option value='Mercoledì'>Mercoledì</option>
        <option value='Giovedì'>Giovedì</option>
        <option value='Sabato'>Sabato</option>
        <option value='Domenica'>Domenica</option>
    </select>
    <br><br>
    <input type = "submit" value = "Cerca">
</form>

</body>
</html>
