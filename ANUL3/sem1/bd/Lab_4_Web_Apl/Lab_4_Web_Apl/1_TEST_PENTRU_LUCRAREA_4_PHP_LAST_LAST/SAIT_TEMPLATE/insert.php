<?php
    require_once 'config.sql.php'; // script conectare server
//	require_once 'connect_serv.php'; // script conectare server
//	require_once 'connect_db.php'; // script conectare BD librarie
// Efectuam operatii cu BD
	$sql = "INSERT INTO info_students (Nume_prenume, grupa, echipa)
          VALUES ('Mamaliga_mare', '#1',
          'Alba ca Zaoada')";
	// deconectam BD
	// mysqli_close($link);
	if(mysqli_query($conexiune, $sql))
	{
		echo "totul este ok studentul a fost inserat
		.php";
		echo '<br />';
	} 
	else
	{
    echo "ERROR: nu pot executa Interogarea $sql. " . mysqli_error($conexiune);
	}
	// deconectam BD daca este necesar
	// mysqli_close($link);
	?>
