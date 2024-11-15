<?php 
  //Conectarea la BD
$con=mysqli_connect("localhost","root","","contact") or die(mysqli_error());
  //Verificare daca butonul SUBMIT  a fost actionat ori nu  
if((isset($_POST['submit'])))
{
  //fetching and storing the form data in variables
$Name = $con->real_escape_string($_POST['name']);
$Email = $con->real_escape_string($_POST['email']);
$Phone = $con->real_escape_string($_POST['contact']);
$comments = $con->real_escape_string($_POST['text']);
  //query to insert the variable data into the database
$sql="INSERT INTO contactatus (name, email, phone, comments) VALUES ('".$Name."','".$Email."', '".$Phone."', '".$comments."')";
  //Execute the query and returning a message
if(!$result = $con->query($sql)){
die('Eroare: [' . $con->error . ']');
}
else
   echo "Va multumim! Va vom contacta in curind!!";
}
?>