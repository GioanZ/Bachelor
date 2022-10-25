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

/* Verify parameter course_name */
if (!isset($_REQUEST["course_name"]) || trim($_REQUEST["course_name"]) == ""){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Nome corso mancante o vuoto.</p>
    </div>";
    exit;
}

/* Verify parameter course_type */
if (!isset($_REQUEST["course_type"]) || trim($_REQUEST["course_type"]) == ""){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Tipo corso mancante o vuoto.</p>
    </div>";
    exit;
}

/* Verify parameter course_level */
if (!isset($_REQUEST["course_level"]) || trim($_REQUEST["course_level"]) == ""){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Livello corso mancante o vuoto.</p>
    </div>";
    exit;
}

$course_code  = $_REQUEST["course_code"];
$course_name  = $_REQUEST["course_name"];
$course_type  = $_REQUEST["course_type"];
$course_level = $_REQUEST["course_level"];

/* Establish DB connection */
$conn = @mysqli_connect ( 'localhost', 'root', '', 'PALESTRA' );

if (mysqli_connect_errno()) {
	echo "Failed to connect to MySQL: " . mysqli_connect_error ();
}

/* String sanification for DB query */
$course_code =  utf8_decode( mysqli_real_escape_string($conn, $course_code)  );
$course_name =  utf8_decode( mysqli_real_escape_string($conn, $course_name)  );
$course_type =  utf8_decode( mysqli_real_escape_string($conn, $course_type)  );
$course_level = utf8_decode( mysqli_real_escape_string($conn, $course_level) );

/* Check Type */
if (!is_numeric($course_level)){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Il Livello del corso deve essere un valore numerico.</p>
    </div>";
    exit;
}

/* Check Type */
if ($course_level < 1 || $course_level > 4){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Il Livello del corso deve essere compreso tra 3 e 4.</p>
    </div>";
    exit;
}

/* Query construction */
$query = "SELECT * FROM CORSI WHERE CodC = '$course_code'";
$result = mysqli_query ( $conn, $query );

/* Query execution */
if (!$result){
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Inserimento $course_code non riuscito! ". mysqli_error ( $conn ) ." </p>
    </div>";
    exit;
} elseif (mysqli_num_rows ( $result ) > 0) {
    echo "<div class = 'w3-panel w3-red'>
        <h3>Errore!</h3>
        <p>Inserimento $course_code non riuscito in quanto già presente nel DB.</p>
    </div>";
    exit;
}


/* Query construction */
$query = "INSERT INTO CORSI (CodC, Nome, Tipo, Livello) VALUES ('$course_code', '$course_name', '$course_name', $course_level)";

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
