<?php
include 'db_connect.php';

$table = $_POST['table'] ?? 'primari';

$nume = isset($_POST['nume']) ? $mysqli->real_escape_string($_POST['nume']) : null;
$prenume = isset($_POST['prenume']) ? $mysqli->real_escape_string($_POST['prenume']) : null;
$localitate = isset($_POST['localitate']) ? $_POST['localitate'] : null;
$gen = isset($_POST['gen']) ? $_POST['gen'] : null;
$partid = isset($_POST['partid']) ? $_POST['partid'] : null;

if (!$nume || !$prenume || !$localitate || !$gen) {
    die("Eroare: Toate câmpurile sunt obligatorii.");
}

$functie = ($table === 'primari') ? 1 : 2;

if ($table === 'primari' && $partid) {
    $id_partid = $mysqli->query("SELECT id_partid FROM partide WHERE id_partid = '$partid'")->fetch_assoc()['id_partid'];
    if (!$id_partid) {
        die("Eroare: Partidul nu există.");
    }
}

if (isset($_POST['id']) && $_POST['id']) {
    if ($table === 'primari') { //primari
        $sql = "UPDATE primari 
                SET nume = '$nume', prenume = '$prenume', id_localitate = '$localitate', 
                    id_functie = '$functie', id_gen = '$gen', id_partid = '$id_partid' 
                WHERE id = " . $mysqli->real_escape_string($_POST['id']);
    } else { // consilieri
        $sql = "UPDATE consilieri 
                SET nume = '$nume', prenume = '$prenume', id_localitate = '$localitate', 
                    id_functie = '$functie', id_gen = '$gen', id_partid = '$partid' 
                WHERE id = " . $mysqli->real_escape_string($_POST['id']);
    }
} else { //primari
    if ($table === 'primari') {
        $sql = "INSERT INTO primari (nume, prenume, id_localitate, id_functie, id_gen, id_partid) 
                VALUES ('$nume', '$prenume', '$localitate', '$functie', '$gen', '$id_partid')";
    } else { // consilieri
        $sql = "INSERT INTO consilieri (nume, prenume, id_localitate, id_functie, id_gen, id_partid) 
                VALUES ('$nume', '$prenume', '$localitate', '$functie', '$gen', '$partid')";
    }
}

if (!$mysqli->query($sql)) {
    die("Eroare la executarea interogării: " . $mysqli->error);
}

header("Location: index.php?table=$table"); //redirect catre pagina principala
exit;
?>
