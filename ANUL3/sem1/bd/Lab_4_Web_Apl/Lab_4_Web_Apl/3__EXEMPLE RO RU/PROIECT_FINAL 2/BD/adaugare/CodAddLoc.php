<?php
    include_once '../conect.php';


    $name = $_POST['Localitate'];
    $carac = $_POST['mediu'];

    $sql = "INSERT INTO localitate(Localitate,idMediu)
            VALUES ('$name','$carac')";
    mysqli_query($conn,$sql);
    
    header("refresh:0.5; url=adaugarelocalitate.php");     

?>
