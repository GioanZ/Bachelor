<html>
<head>
<title>Programmazione</title>
</head>

<body>
<h3>Inserimento nuovo corso</h3>
<form method="get" action="inseriscicorso.php">

<p>Dati del nuovo corso da inserire<br>

<table>
  <tr>
    <td> Codice: </td>
    <td> <input type="text" size="10" maxlength="10" name="codc"> </td>
  </tr>
  <tr>
    <td> Nome: </td>
    <td> <input type="text" size="50" maxlength="50" name="nome"> </td>
  </tr>
  <tr>
    <td> Tipo: </td>
    <td> <input type="text" size="50" maxlength="50" name="tipo"> </td>
  </tr>
  <tr>
    <td> Livello: </td>
    <td> <input type="text" size="10" maxlength="10" name="livello"> </td>
  </tr>
</table>

<br>
<input type="submit" value="Inserisci">

</form>
</body>
</html>
