<!DOCTYPE html>
<html>
<link rel = "stylesheet" href = "https://www.w3schools.com/w3css/4/w3.css"> 
<body>

<h1>Inserisci un nuovo corso</h1>

<form action = "5_back.php">

    <label for = "course_code">Codice Corso:</label><br>
    <input type = "text" id = "course_code" name = "course_code" placeholder = "e.g. CT100"><br><br>

    <label for = "course_name">Nome Corso:</label><br>
    <input type = "text" id = "course_name" name = "course_name" placeholder = "e.g. Aerobica per Bambini"><br><br>

    <label for = "course_type">Tipo Corso:</label><br>
    <input type = "text" id = "course_type" name = "course_type" placeholder = "e.g. Aerobica"><br><br>

    <label for = "course_level">Livello Corso:</label><br>
    <input type = "text" id = "course_level" name = "course_level" placeholder = "e.g. 1"><br><br>

    <input type = "submit" value = "Inserisci">
</form>


</body>
</html>
