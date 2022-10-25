<!DOCTYPE html>
<html>
<link rel = "stylesheet" href = "https://www.w3schools.com/w3css/4/w3.css">
<body>

<?php

/* Verify parameter course_code */
if (!isset($_REQUEST["course_code"]) || trim($_REQUEST["course_code"]) == ""){
    echo '<p> ERRORE: Codice corso mancante o vuoto. </p>';
    exit;
}

$course_code = $_REQUEST["course_code"];

/* Establish DB connection */
$conn = @mysqli_connect ( 'localhost', 'root', '', 'PALESTRA' );

if (mysqli_connect_errno()) {
	echo "Failed to connect to MySQL: " . mysqli_connect_error ();
}

/* String sanification for DB query */
$course_code = mysqli_real_escape_string($conn, $course_code);

/* Query construction */
$query = "SELECT CodC, Nome, Tipo, Livello
            FROM CORSI
            WHERE CodC = '$course_code'";

/* Query execution */
$result = mysqli_query ( $conn, $query );
if (!$result){
    die ( 'Query error: ' . mysqli_error ( $conn ) );
}

/* Check if course found */
if (mysqli_num_rows ( $result ) > 0) {
    echo "<h1>Dettagli corso $course_code</h1>";
    echo "<table class = 'w3-table-all w3-hoverable'>";

    /* Table header */
    echo "<thead><tr>";
    $i = 0;
    $field_names = [];
    while($i<mysqli_num_fields($result)) {
        $meta = mysqli_fetch_field($result);
        echo "<th>".$meta->name."</th>";
        array_push($field_names, $meta->name);
        $i++;
    }
    echo "</thead></tr>";

    /* Table content */
    while($row = mysqli_fetch_array($result)) {
        echo "<tr>";
        foreach ($field_names as $field){
            /* String sanification for HTML */
            $safe_html = htmlspecialchars($row[$field], ENT_QUOTES | ENT_SUBSTITUTE, 'utf-8');
            echo "<td>" . $safe_html . "</td>";
        }
        echo "</tr>";
    }
    echo "</table>";

} else {
    echo "<h1>Corso $course_code non trovato.</h1>";
}

?>

<hr>

<h3> Cerca un altro corso </h3>

<form action = "2_back.php">
  <label for = "course_code">Codice Corso:</label><br>
  <input type = "text" id = "course_code" name = "course_code" placeholder = "e.g. CT100">
  <br><br>
  <input type = "submit" value = "Cerca">
</form>

</body>
</html>
