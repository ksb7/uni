<?php
	include_once '../conect.php';


	$id = $_POST['Id'];

	$sql = "DELETE FROM localitate WHERE localitate.idLocalitate = '$id'";
	mysqli_query($conn,$sql);
	
	header("refresh:0.5; url=DelLoc.php");	

?>