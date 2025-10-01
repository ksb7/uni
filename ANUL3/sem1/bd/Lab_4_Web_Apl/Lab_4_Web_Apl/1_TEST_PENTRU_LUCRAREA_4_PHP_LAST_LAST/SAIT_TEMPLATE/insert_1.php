<?php
    require_once 'config_sql.php'; // script conectare server
	require_once 'connect_serv.php'; // script conectare server
	require_once 'connect_db.php'; // script conectare BD librarie
 // Efectuam operatii cu BD
	$sql = "INSERT INTO carti
          VALUES ('2-2222-2222-9', 'Eminescu',
          'Ghid Php', '1000', '3',2)";
	// deconectam BD
	// mysqli_close($link);
	if(mysqli_query($link, $sql))
	{
		echo "totul este ok in programul INSERT_carti_1.php";
		echo '<br />';
	} 
	else
	{
    echo "ERROR: nu pot executa Interogarea $sql. " . mysqli_error($link);
	}
	// deconectam BD daca este necesar
	// mysqli_close($link);
	?>
