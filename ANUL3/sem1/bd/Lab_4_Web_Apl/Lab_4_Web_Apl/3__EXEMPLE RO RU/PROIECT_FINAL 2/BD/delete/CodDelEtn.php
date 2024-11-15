<?php
	include_once '../conect.php';


	$id = $_POST['Id'];

	$sql = "DELETE FROM popetnii WHERE popetnii.idPopetnie = '$id'";
	mysqli_query($conn,$sql);
	
	header("refresh:0.5; url=DelEtn.php");	

?>