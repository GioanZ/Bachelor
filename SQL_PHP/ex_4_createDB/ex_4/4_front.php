<!DOCTYPE html>
<html>
<link rel = "stylesheet" href = "https://www.w3schools.com/w3css/4/w3.css">
<body>

<h1>Ricerca Corso</h1>

<form action = "4_back.php">

    <label for = "surname_instructor">Cognome Istruttore:</label><br>
    <select id = "surname_instructor" name = "surname_instructor" class = "w3-select">
    <option value = ''>Seleziona istruttore/istruttrice</option>
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
        <option value = ''>Seleziona giorno</option>
        <option value = 'Lunedì'>Lunedì</option>
        <option value = 'Martedì'>Martedì</option>
        <option value = 'Mercoledì'>Mercoledì</option>
        <option value = 'Giovedì'>Giovedì</option>
        <option value = 'Sabato'>Sabato</option>
        <option value = 'Domenica'>Domenica</option>
    </select>
    <br><br>
    <input type = "submit" value = "Cerca">
</form>


</body>
</html>
