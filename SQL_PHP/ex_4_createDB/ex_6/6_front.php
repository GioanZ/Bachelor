<!DOCTYPE html>
<html>
<link rel = "stylesheet" href = "https://www.w3schools.com/w3css/4/w3.css">
<body>

<h1>Inserisci Programmazione</h1>

<form action = "6_back.php">

    <label for = "cod_instructor">Codice Istruttore:</label><br>
    <select id = "cod_instructor" name = "cod_instructor" class = "w3-select">
    <option value = ''>Seleziona istruttore/istruttrice</option>
    <?php

        /* Establish DB connection */
        $conn = @mysqli_connect ( 'localhost', 'root', '', 'PALESTRA' );

        if (mysqli_connect_errno()) {
            echo "Failed to connect to MySQL: " . mysqli_connect_error ();
        }

        /* Query construction */
        $query = "SELECT CodFisc FROM ISTRUTTORE";

        /* Query execution */
        $result = mysqli_query ( $conn, $query );
        if (!$result){
            die ( 'Query error: ' . mysqli_error ( $conn ) );
        }

        /* Check if course found */
        if (mysqli_num_rows ( $result ) > 0) {
            while($row = mysqli_fetch_array($result)) {
                $cod_instructor = $row["CodFisc"];
                echo "<option value = '$cod_instructor'>$cod_instructor</option>";
            }
        }

    ?>
    </select>
    <br><br>

    <label for = "course_code">Codice Corso:</label><br>
    <select id = "course_code" name = "course_code" class = "w3-select">
    <option value = ''>Seleziona Corso</option>
    <?php

        /* Establish DB connection */
        $conn = @mysqli_connect ( 'localhost', 'root', '', 'PALESTRA' );

        if (mysqli_connect_errno()) {
            echo "Failed to connect to MySQL: " . mysqli_connect_error ();
        }

        /* Query construction */
        $query = "SELECT CodC FROM CORSI";

        /* Query execution */
        $result = mysqli_query ( $conn, $query );
        if (!$result){
            die ( 'Query error: ' . mysqli_error ( $conn ) );
        }

        /* Check if course found */
        if (mysqli_num_rows ( $result ) > 0) {
            while($row = mysqli_fetch_array($result)) {
                $course_code = $row["CodC"];
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

    <label for = "starting_time">Ora di inizio:</label>
    <input type = "time" id = "starting_time" name = "starting_time"> <br><br>

    <label for = "duration">Durata:</label>
    <input type = "number" id = "duration" name = "duration" min = "1">  <br><br>

    <label for = "room">Sala:</label>
    <input type = "text" id = "room" name = "room">  <br><br>


    <input type = "submit" value = "Inserisci">
</form>


</body>
</html>
