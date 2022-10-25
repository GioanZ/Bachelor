<!DOCTYPE html>
<html>
<link rel = "stylesheet" href = "https://www.w3schools.com/w3css/4/w3.css"> 
<body>

<?php

/* Verify parameter course_code */
if (!isset($_REQUEST["course_code"]) || trim($_REQUEST["course_code"]) == ""){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Codice corso mancante o vuoto.</p>
    </div>";
    exit;
}

/* Verify parameter cod_instructor */
if (!isset($_REQUEST["cod_instructor"]) || trim($_REQUEST["cod_instructor"]) == ""){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Codice fiscale istruttore mancante o vuoto.</p>
    </div>";
    exit;
}

/* Verify parameter day */
if (!isset($_REQUEST["day"]) || trim($_REQUEST["day"]) == ""){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Giorno mancante o vuoto.</p>
    </div>";
    exit;
}

/* Verify parameter starting_time */
if (!isset($_REQUEST["starting_time"]) || trim($_REQUEST["starting_time"]) == ""){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Ora di inizio mancante o campo vuoto.</p>
    </div>";
    exit;
}

/* Verify parameter duration */
if (!isset($_REQUEST["duration"]) || trim($_REQUEST["duration"]) == ""){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Durata corso mancante o campo vuoto.</p>
    </div>";
    exit;
}

/* Verify parameter room */
if (!isset($_REQUEST["room"]) || trim($_REQUEST["room"]) == ""){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Sala mancante o campo vuoto.</p>
    </div>";
    exit;
}
$course_code    = $_REQUEST["course_code"];
$cod_instructor = $_REQUEST["cod_instructor"];
$day            = $_REQUEST["day"];
$starting_time  = $_REQUEST["starting_time"];
$duration       = $_REQUEST["duration"];
$room           = $_REQUEST["room"];

/* Establish DB connection */
$conn = @mysqli_connect ( 'localhost', 'root', '', 'PALESTRA' );

if (mysqli_connect_errno()) {
	echo "Failed to connect to MySQL: " . mysqli_connect_error ();
}

/* String sanification for DB query */
$course_code    = utf8_encode(utf8_decode( mysqli_real_escape_string($conn, $course_code) ));
$cod_instructor = utf8_encode(utf8_decode( mysqli_real_escape_string($conn, $cod_instructor) ));
$day            = utf8_encode(utf8_decode( mysqli_real_escape_string($conn, $day) ));
$day_sql        = utf8_decode( mysqli_real_escape_string($conn, $day) );
$starting_time  = utf8_encode(utf8_decode( mysqli_real_escape_string($conn, $starting_time) ));
$duration       = utf8_encode(utf8_decode( mysqli_real_escape_string($conn, $duration) ));
$room           = utf8_encode(utf8_decode( mysqli_real_escape_string($conn, $room) ));

/* Check Duration */
if (!is_numeric($duration)){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>La durata deve essere un valore numerico.</p>
    </div>";
    exit;
}

/* Check Day */
$week_array = ["Lunedì", "Martedì", "Mercoledì", "Giovedì", "Venerdì"];
if (!in_array($day, $week_array)){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Il giorno della settimana inserito non è corretto. </p>
    </div>";
    exit;
}


/* Check Duration */
if (!is_numeric($duration)){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>La durata deve essere un valore numerico.</p>
    </div>";
    exit;
}

$time = strtotime($starting_time);
$end_time = date("H:i", strtotime('+'.$duration.' minutes', $time));

/* Query construction */
$query = "SELECT *
            FROM PROGRAMMA
            WHERE Giorno = '$day_sql' AND
                (TIME(OraInizio) BETWEEN '$starting_time' AND '$end_time' OR
                TIME(ADDTIME(OraInizio, SEC_TO_TIME(Durata*60))) BETWEEN '$starting_time' AND '$end_time') AND
                (SALA = '$room' OR CodFisc = '$cod_instructor')
            ";

$result = mysqli_query ( $conn, $query );

/* Query execution */
if (!$result){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Inserimento non riuscito! ". mysqli_error ( $conn ) ." </p>
    </div>";
    exit;
} elseif (mysqli_num_rows ( $result ) > 0) {
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Inserimento non riuscito in quanto sovrapposto ad altri corsi.</p>
    </div>";
    exit;
}

/* Query construction */
$query = "INSERT INTO PROGRAMMA (CodFisc, Giorno, OraInizio, Durata, Sala, CodC)
            VALUES ('$cod_instructor', '$day_sql', '$starting_time', $duration, '$room', '$course_code')";

/* Query execution */
$result = mysqli_query ( $conn, $query );
if (!$result){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Inserimento $course_code non riuscito! ". mysqli_error ( $conn ) ." </p>
    </div>";
    exit;
} else {
    echo "<div class = 'w3-panel w3-green'>
        <h3>Congratulazioni!</h3>
        <p>Inserimento del corso $course_code riuscito.</p>
    </div>  ";
    exit;
}
?>

</body>
</html>
