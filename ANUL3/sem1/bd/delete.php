<?php
include 'db_connect.php';

$id = isset($_GET['id']) ? $_GET['id'] : null;

if ($id) {
    $sql = "DELETE FROM primari WHERE id = $id";
    
    if (mysqli_query($mysqli, $sql)) {
        header('Location: index.php?table=primari'); //redirectionare la pagina principala
        exit;
    } else {
        echo "Error: " . mysqli_error($mysqli);
    }
} else {
    echo "ID-ul nu a fost specificat.";
}
?>
