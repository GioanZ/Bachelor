<?php

/* Verify parameter name */
if (!isset($_REQUEST["name"]) || trim($_REQUEST["name"]) == ""){
    echo '<p> ERRORE: parametro nome mancante o vuoto. </p>';
    exit;
}

/* Verify parameters surname */
if (!isset($_REQUEST["surname"]) || trim($_REQUEST["surname"]) == ""){
    echo '<p> ERRORE: parametro cognome mancante o vuoto. </p>';
    exit;
}

$name = $_REQUEST["name"];
$surname = $_REQUEST["surname"];

echo '<p>' . $name . ' ' . $surname . ' è un istruttore/istruttrice.</p>';


?>