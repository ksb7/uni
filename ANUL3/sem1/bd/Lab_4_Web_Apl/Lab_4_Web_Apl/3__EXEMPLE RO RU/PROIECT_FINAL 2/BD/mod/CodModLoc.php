<?php
	include_once '../conect.php';


	$name = $_POST['Name'];
	$carac = $_POST['mediu'];
	$id = $_POST['Id'];

	$sql = "UPDATE localitate
			SET Localitate = '$name', idMediu = '$carac' 
			WHERE idLocalitate = '$id' ";
	mysqli_query($conn,$sql);
	
	header("refresh:0.5; url=modlocalitate.php");   	

?>