<?php
include 'db_connect.php';

$table = isset($_GET['table']) ? $_GET['table'] : 'primari';
$id = isset($_GET['id']) ? $_GET['id'] : null;

$localitati = $mysqli->query("SELECT id_localitate, nume_localitate FROM localitati");
$functii = $mysqli->query("SELECT id_functie, nume_functie FROM functii");
$genuri = $mysqli->query("SELECT id_gen, nume_gen FROM genuri");
$partide = $mysqli->query("SELECT id_partid, nume_partid FROM partide");

if ($id) {
    $sql = "SELECT 
                p.id AS id,
                p.nume AS nume,
                p.prenume AS prenume,
                l.nume_localitate AS localitate,
                f.nume_functie AS functie,
                gen.nume_gen AS gen,
                pa.nume_partid AS partid
            FROM $table p
            JOIN localitati l ON p.id_localitate = l.id_localitate
            JOIN functii f ON p.id_functie = f.id_functie
            JOIN genuri gen ON p.id_gen = gen.id_gen
            JOIN partide pa ON p.id_partid = pa.id_partid
            WHERE p.id = $id";

    $result = $mysqli->query($sql);
    $row = $result->fetch_assoc();
}
?>
<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?php echo $id ? 'Editează' : 'Adaugă'; ?> Primar</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>

<nav>
    <a href="index.php?table=primari">Primari</a>
    <a href="index.php?table=consilieri">Consilieri</a>
</nav>

<h1><?php echo $id ? 'Editează Consilier' : 'Adaugă Consilier'; ?></h1>

<form method="POST" action="save.php">
    <input type="hidden" name="id" value="<?php echo $id; ?>">

    <div class="form-group">
        <label for="nume">Nume:</label>
        <input type="text" name="nume" value="<?php echo isset($row['nume']) ? $row['nume'] : ''; ?>" required>
    </div>

    <div class="form-group">
        <label for="prenume">Prenume:</label>
        <input type="text" name="prenume" value="<?php echo isset($row['prenume']) ? $row['prenume'] : ''; ?>" required>
    </div>

    <div class="form-group">
        <label for="localitate">Localitate:</label>
        <select name="localitate" required>
            <?php while ($localitate = $localitati->fetch_assoc()) : ?>
                <option value="<?php echo $localitate['nume_localitate']; ?>" <?php echo (isset($row['localitate']) && $row['localitate'] == $localitate['nume_localitate']) ? 'selected' : ''; ?>>
                    <?php echo $localitate['nume_localitate']; ?>
                </option>
            <?php endwhile; ?>
        </select>
    </div>

    <div class="form-group">
        <label for="functie">Funcție:</label>
        <select name="functie" required>
            <?php while ($functie = $functii->fetch_assoc()) : ?>
                <option value="<?php echo $functie['nume_functie']; ?>" <?php echo (isset($row['functie']) && $row['functie'] == $functie['nume_functie']) ? 'selected' : ''; ?>>
                    <?php echo $functie['nume_functie']; ?>
                </option>
            <?php endwhile; ?>
        </select>
    </div>

    <div class="form-group">
        <label for="gen">Gen:</label>
        <select name="gen" required>
            <?php while ($gen = $genuri->fetch_assoc()) : ?>
                <option value="<?php echo $gen['nume_gen']; ?>" <?php echo (isset($row['gen']) && $row['gen'] == $gen['nume_gen']) ? 'selected' : ''; ?>>
                    <?php echo $gen['nume_gen']; ?>
                </option>
            <?php endwhile; ?>
        </select>
    </div>

    <div class="form-group">
        <label for="partid">Partid:</label>
        <select name="partid" required>
            <?php while ($partid = $partide->fetch_assoc()) : ?>
                <option value="<?php echo $partid['nume_partid']; ?>" <?php echo (isset($row['partid']) && $row['partid'] == $partid['nume_partid']) ? 'selected' : ''; ?>>
                    <?php echo $partid['nume_partid']; ?>
                </option>
            <?php endwhile; ?>
        </select>
    </div>

    <button type="submit">Salvează</button>
</form>
