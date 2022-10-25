<!DOCTYPE html>
<html>
<link rel = "stylesheet" href = "https://www.w3schools.com/w3css/4/w3.css">
<body>

<h1>Ricerca Corso</h1>

<form action = "3_back.php">
    <select id = "course_code" name = "course_code" class = "w3-select">
    <option value = ''>Seleziona un corso</option>
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
    <br>
    <br>
    <input type = "submit" value = "Cerca">
</form>


</body>
</html>
